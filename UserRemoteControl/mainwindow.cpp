#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , energySerial(new QSerialPort(this))
    , energyTimer(new QTimer(this))
    , energyDataBuffer()
    , r(445.0)
    , angleOffset(0.05)
    , laserActive(false)
    , autoMode(false)
    , previousAutoMode(false)
    , previousSliderState(true)
{
    ui->setupUi(this);

    // Load bg image (radar)
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    pix = QPixmap(":/src/radar.png");
    scene->addPixmap(pix);

    // Set up QSerialPort
    arduino = new QSerialPort;
    arduino_is_available = false;
    radarSerial = "COM9";

    // Initialize needle at 0 degrees
    QPen blackpen(Qt::black);
    QBrush graybrush(Qt::gray);
    t_up = angleOffset;
    t_lo = -angleOffset;
    triangle.append(QPointF(r * qCos(t_up) + 505, -r * qSin(t_up) + 495));
    triangle.append(QPointF(505, 495));
    triangle.append(QPointF(r * qCos(t_lo) + 505, -r * qSin(t_lo) + 495));
    needle = scene->addPolygon(triangle, blackpen, graybrush);
    needle->setOpacity(0.30);

    // Check which port the Arduino is on
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
        if (serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()) {
            if (serialPortInfo.vendorIdentifier() == arduino_uno_vendorID) {
                if (serialPortInfo.productIdentifier() == arduino_uno_productID) {
                    radarSerial = serialPortInfo.portName();
                    arduino_is_available = true;
                    qDebug() << "Port available!";
                }
            }
        }
    }

    // Setup port if available
    if (arduino_is_available) {
        arduino->setPortName(radarSerial);
        arduino->open(QSerialPort::ReadWrite);
        arduino->setBaudRate(QSerialPort::Baud115200);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
    } else {
        QMessageBox::warning(this, "Port error", "Couldn't find Arduino");
    }

    autoMode = false;
    ui->button_auto->setText("Start Auto");

    autoTimer = new QTimer(this);
    connect(autoTimer, &QTimer::timeout, this, &MainWindow::updateServoAuto);

    laserActive = false;
    laserTimer = new QTimer(this);
    connect(laserTimer, &QTimer::timeout, this, &MainWindow::deactivateLaser);

    resumeTimer = new QTimer(this);
    connect(resumeTimer, &QTimer::timeout, this, &MainWindow::resumeOperation);

    // Setup data update timer
    dataUpdateTimer = new QTimer(this);
    connect(dataUpdateTimer, &QTimer::timeout, this, &MainWindow::updateHistoricalData);
    dataUpdateTimer->start(2000);  // Update every 2 seconds

    // Setup current time display
    QTimer *timeTimer = new QTimer(this);
    connect(timeTimer, &QTimer::timeout, this, &MainWindow::updateCurrentTime);
    timeTimer->start(1000);  // Update every second


    /* // Setup energy serial port
    energySerial->setPortName("COM9");
    energySerial->setBaudRate(QSerialPort::Baud115200);
    energySerial->setDataBits(QSerialPort::Data8);
    energySerial->setParity(QSerialPort::NoParity);
    energySerial->setStopBits(QSerialPort::OneStop);
    energySerial->setFlowControl(QSerialPort::NoFlowControl);

    if (energySerial->open(QIODevice::ReadOnly)) {
        connect(energySerial, &QSerialPort::readyRead, this, &MainWindow::readEnergyData);
        qDebug() << "Energy serial port opened successfully.";
    } else {
        qDebug() << "Failed to open Energy serial port.";
    }

    energyTimer->start(2000); */
}

void MainWindow::readEnergyData() {
    QByteArray data = energySerial->readAll();
    energyDataBuffer.append(data);

    while (energyDataBuffer.contains('\n')) {
        int lineEnd = energyDataBuffer.indexOf('\n');
        QByteArray line = energyDataBuffer.left(lineEnd);
        energyDataBuffer = energyDataBuffer.mid(lineEnd + 1);

        processEnergyData(QString::fromUtf8(line));
    }
}

void MainWindow::readSerial() {
    QByteArray data = arduino->readAll();
    serialBuffer.append(QString::fromUtf8(data));

    while (serialBuffer.contains('\n')) {
        int lineEnd = serialBuffer.indexOf('\n');
        QString line = serialBuffer.left(lineEnd).trimmed();
        serialBuffer = serialBuffer.mid(lineEnd + 1);

        if (line.startsWith("B,")) {
            processEnergyData(line);
        } else if (line.contains(',')) {
            processRadarData(line);
        } else if (line == "LASER_ACTIVATED") {
            handleLaserStatus("LASER_ACTIVATED");
        } else if (line == "LASER_DEACTIVATED") {
            handleLaserStatus("LASER_DEACTIVATED");
        }
    }
}

void MainWindow::processRadarData(const QString &data) {
    QStringList parts = data.split(',');
    if (parts.size() == 2) {
        float angle = parts[0].toFloat();
        float distance = parts[1].toFloat();

        updateDetectionPoint(angle, distance);

        // Update labels
        ui->angleLabel->setText(QString("%1°").arg(angle, 0, 'f', 1));
        ui->rangeLabel->setText(QString("%1 cm").arg(distance, 0, 'f', 1));

        // Update status based on distance
        if (distance >= LASER_ACTIVATION_MIN_RANGE && distance <= LASER_ACTIVATION_MAX_RANGE) {
            ui->detectionStatusLabel->setText("Object Detected (Laser Range)");
            ui->detectionStatusLabel->setStyleSheet("color: red;");
            if (!laserActive) {
                handleLaserActivation();
            }
        } else {
            ui->detectionStatusLabel->setText(distance > LASER_ACTIVATION_MAX_RANGE && distance <= MAX_DETECTION_RANGE ? "Object Detected" : "No Object");
            ui->detectionStatusLabel->setStyleSheet(distance > LASER_ACTIVATION_MAX_RANGE && distance <= MAX_DETECTION_RANGE ? "color: orange;" : "color: green;");
        }
    }
}

void MainWindow::updateCurrentTime() {
    QDateTime currentTime = QDateTime::currentDateTime();
    ui->currentTimeLabel_3->setText(currentTime.toString("hh:mm:ss"));
}

void MainWindow::processEnergyData(const QString &data) {
    QStringList parts = data.split(',');
    if (parts.size() == 6) {
        float busVoltage = parts[1].toFloat();
        float shuntVoltage = parts[2].toFloat();
        float loadVoltage = parts[3].toFloat();
        float current = parts[4].toFloat();
        float power = parts[5].toFloat();

        // Update real-time labels
        ui->busVoltageLabel->setText(QString::number(busVoltage, 'f', 2) + " V");
        ui->shuntVoltageLabel->setText(QString::number(shuntVoltage, 'f', 2) + " mV");
        ui->loadVoltageLabel->setText(QString::number(loadVoltage, 'f', 2) + " V");
        ui->currentLabel->setText(QString::number(current, 'f', 2) + " mA");
        ui->powerLabel->setText(QString::number(power, 'f', 2) + " mW");

        // Add to historical data
        QDateTime currentTime = QDateTime::currentDateTime();
        QString timeString = currentTime.toString("hh:mm:ss");
        QString historicalEntry = QString("%1,%2,%3,%4,%5,%6").arg(timeString)
                                      .arg(busVoltage)
                                      .arg(shuntVoltage)
                                      .arg(loadVoltage)
                                      .arg(current)
                                      .arg(power);
        historicalData.prepend(historicalEntry);
        if (historicalData.size() > 10) {
            historicalData.removeLast();
        }
    }
}

void MainWindow::updateHistoricalData() {
    for (int i = 10; i > 1; --i) {
        QLabel* timeLabel = findChild<QLabel*>(QString("historicalTimeLabel%1_2").arg(i));
        QLabel* busVoltageLabel = findChild<QLabel*>(QString("historicalBusVoltageLabel%1_2").arg(i));
        QLabel* shuntVoltageLabel = findChild<QLabel*>(QString("historicalShuntVoltageLabel%1_2").arg(i));
        QLabel* loadVoltageLabel = findChild<QLabel*>(QString("historicalLoadVoltageLabel%1_2").arg(i));
        QLabel* currentLabel = findChild<QLabel*>(QString("historicalCurrentLabel%1_2").arg(i));
        QLabel* powerLabel = findChild<QLabel*>(QString("historicalPowerLabel%1_2").arg(i));

        QLabel* prevTimeLabel = findChild<QLabel*>(QString("historicalTimeLabel%1_2").arg(i-1));
        QLabel* prevBusVoltageLabel = findChild<QLabel*>(QString("historicalBusVoltageLabel%1_2").arg(i-1));
        QLabel* prevShuntVoltageLabel = findChild<QLabel*>(QString("historicalShuntVoltageLabel%1_2").arg(i-1));
        QLabel* prevLoadVoltageLabel = findChild<QLabel*>(QString("historicalLoadVoltageLabel%1_2").arg(i-1));
        QLabel* prevCurrentLabel = findChild<QLabel*>(QString("historicalCurrentLabel%1_2").arg(i-1));
        QLabel* prevPowerLabel = findChild<QLabel*>(QString("historicalPowerLabel%1_2").arg(i-1));

        if (timeLabel && busVoltageLabel && shuntVoltageLabel && loadVoltageLabel && currentLabel && powerLabel &&
            prevTimeLabel && prevBusVoltageLabel && prevShuntVoltageLabel && prevLoadVoltageLabel && prevCurrentLabel && prevPowerLabel) {
            timeLabel->setText(prevTimeLabel->text());
            busVoltageLabel->setText(prevBusVoltageLabel->text());
            shuntVoltageLabel->setText(prevShuntVoltageLabel->text());
            loadVoltageLabel->setText(prevLoadVoltageLabel->text());
            currentLabel->setText(prevCurrentLabel->text());
            powerLabel->setText(prevPowerLabel->text());
        }
    }

    if (!historicalData.isEmpty()) {
        QStringList data = historicalData.first().split(',');
        if (data.size() == 6) {
            QLabel* timeLabel = findChild<QLabel*>("historicalTimeLabel1_2");
            QLabel* busVoltageLabel = findChild<QLabel*>("historicalBusVoltageLabel1_2");
            QLabel* shuntVoltageLabel = findChild<QLabel*>("historicalShuntVoltageLabel1_2");
            QLabel* loadVoltageLabel = findChild<QLabel*>("historicalLoadVoltageLabel1_2");
            QLabel* currentLabel = findChild<QLabel*>("historicalCurrentLabel1_2");
            QLabel* powerLabel = findChild<QLabel*>("historicalPowerLabel1_2");

            if (timeLabel && busVoltageLabel && shuntVoltageLabel && loadVoltageLabel && currentLabel && powerLabel) {
                timeLabel->setText(data[0]);
                busVoltageLabel->setText(data[1] + " V");
                shuntVoltageLabel->setText(data[2] + " mV");
                loadVoltageLabel->setText(data[3] + " V");
                currentLabel->setText(data[4] + " mA");
                powerLabel->setText(data[5] + " mW");
            }
        }
    }
}

void MainWindow::setSliderEnabled(bool enabled) {
    ui->verticalSlider->setEnabled(enabled);
    for (QPushButton* button : {ui->button0, ui->button45, ui->button90, ui->button135, ui->button180}) {
        button->setEnabled(enabled);
    }
}

void MainWindow::handleLaserStatus(const QString &status) {
    if (status == "LASER_ACTIVATED") {
        laserActive = true;
        updateLaserStatus("Laser: On");
        laserTimer->start(2000);
        if (autoMode) {
            autoTimer->stop();
        }
    } else if (status == "LASER_DEACTIVATED") {
        laserActive = false;
        updateLaserStatus("Laser: Off");
        laserTimer->stop();
        if (autoMode) {
            autoTimer->start(50);
        }
    }
}

void MainWindow::deactivateLaser() {
    laserActive = false;
    updateLaserStatus("Laser: Off");
    arduino->write("LASER_OFF\n");
    laserTimer->stop();
    resumeTimer->start(0);  // Timer to resume normal operation immediately
}

void MainWindow::handleLaserActivation() {
    laserActive = true;
    updateLaserStatus("Laser: On");
    arduino->write("LASER_ON\n");
    laserTimer->start(2000);
}

void MainWindow::resumeOperation() {
    resumeTimer->stop();
    if (autoMode) {
        arduino->write("AUTO\n");
    } else {
        arduino->write("MANUAL\n");
    }
}

void MainWindow::updateLaserStatus(const QString &status) {
    ui->textEdit->setPlainText(status);
}

void MainWindow::updateServo(QString command) {
    if (arduino->isWritable()) {
        arduino->write(command.toUtf8());
    } else {
        qDebug() << "Couldn't write to serial!";
    }
}

void MainWindow::updateServoAuto() {
    if (!laserActive) {
        static int angle = 0;
        static bool increasing = true;
        static const int stepSize = 2;

        if (increasing) {
            angle += stepSize;
            if (angle >= 180) {
                angle = 180;
                increasing = false;
            }
        } else {
            angle -= stepSize;
            if (angle <= 0) {
                angle = 0;
                increasing = true;
            }
        }

        updateServo(QString::number(angle) + "\n");
        ui->verticalSlider->setValue(angle);
    }
}

void MainWindow::updateDetectionPoint(float angle, float distance) {
    qDebug() << "Updating detection point at angle:" << angle << "distance:" << distance;
    if (distance > 0 && distance <= 200) {
        float radAngle = qDegreesToRadians(angle);

        // Scale the distance to fit within the radar display
        float scaledDistance = (distance / 200.0) * 445.0; // 445 is the radius of our radar display

        float x = scaledDistance * qCos(radAngle);
        float y = scaledDistance * qSin(radAngle);

        QGraphicsRectItem* point = scene->addRect(505 + x, 495 - y, 3, 3, QPen(Qt::red), QBrush(Qt::red));
        detectionPoints.append(point);

        clearOldDetectionPoints();
    }

    // Update needle position (always update, even if no object detected)
    float radAngle = qDegreesToRadians(angle);
    float t_up = radAngle + 0.05;
    float t_lo = radAngle - 0.05;
    QPolygonF newTriangle;
    newTriangle.append(QPointF(445.0 * qCos(t_up) + 505, -445.0 * qSin(t_up) + 495));
    newTriangle.append(QPointF(505, 495));
    newTriangle.append(QPointF(445.0 * qCos(t_lo) + 505, -445.0 * qSin(t_lo) + 495));
    needle->setPolygon(newTriangle);
}

void MainWindow::clearOldDetectionPoints() {
    while (detectionPoints.size() > 50) {
        QGraphicsRectItem* point = detectionPoints.takeFirst();
        scene->removeItem(point);
        delete point;
    }
}

void MainWindow::on_button0_clicked() {
    if (!autoMode) {
        updateServo("0\n");
        ui->verticalSlider->setValue(0);
    }
}

void MainWindow::on_button45_clicked() {
    if (!autoMode) {
        updateServo("45\n");
        ui->verticalSlider->setValue(45);
    }
}

void MainWindow::on_button90_clicked() {
    if (!autoMode) {
        updateServo("90\n");
        ui->verticalSlider->setValue(90);
    }
}

void MainWindow::on_button135_clicked() {
    if (!autoMode) {
        updateServo("135\n");
        ui->verticalSlider->setValue(135);
    }
}

void MainWindow::on_button180_clicked() {
    if (!autoMode) {
        updateServo("180\n");
        ui->verticalSlider->setValue(180);
    }
}

void MainWindow::on_verticalSlider_valueChanged(int value) {
    if (!autoMode && !laserActive) {
        updateServo(QString::number(value) + "\n");
    }
}

void MainWindow::on_button_auto_clicked() {
    autoMode = !autoMode;

    if (autoMode) {
        autoTimer->start(50);
        ui->button_auto->setText("Stop Auto");
        setSliderEnabled(false);
        arduino->write("AUTO\n");
    } else {
        autoTimer->stop();
        ui->button_auto->setText("Start Auto");
        setSliderEnabled(true);
        arduino->write("MANUAL\n");
    }
}

MainWindow::~MainWindow() {
    if (arduino->isOpen()) {
        arduino->close();
    }
    if (serial->isOpen()) {
        serial->close();
    }
    if (energySerial->isOpen()) {
        energySerial->close();
    }
    delete ui;
}

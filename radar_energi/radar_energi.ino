#include <Servo.h>
#include <Wire.h>
#include <Adafruit_INA219.h>

// Servo
Servo myservo;

// HC-SR04 ultrasonic sensor
const int trigPin = 9;
const int echoPin = 10;

// Laser
const int laserPin = 12;

// INA219
Adafruit_INA219 ina219;

long duration;
float distance;
int servoSetting;
bool servoIncreasing = true;

const float MAX_DETECTION_RANGE = 200.0; // Maximum detection range in cm
const float LASER_ACTIVATION_RANGE = 50.0; // Laser activation range in cm

void setup() {
  Serial.begin(115200);
  Serial.println("Radar and Battery Monitor");

  myservo.attach(11);
  myservo.write(0);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(laserPin, OUTPUT);
  digitalWrite(laserPin, LOW);

  if (!ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) { delay(10); }
  } else {
    Serial.println("INA219 chip found");
  }
  ina219.setCalibration_32V_2A();
}

bool laserActive = false;
unsigned long laserStartTime = 0;
bool autoMode = false;
bool servoStopped = false;

void loop() {
  getDistance();
  readSerialCommand();
  outputDistance();

  if (distance <= LASER_ACTIVATION_RANGE && !laserActive) {
    activateLaser();
  } else if (laserActive && (distance > LASER_ACTIVATION_RANGE || millis() - laserStartTime >= 2000)) {
    deactivateLaser();
  }

  if (!laserActive) {
    if (autoMode) {
      updateServoAuto();
    }
  }

  sendBatteryData();
  delay(50);
}

void activateLaser() {
  laserActive = true;
  laserStartTime = millis();
  digitalWrite(laserPin, HIGH);
  Serial.println("LASER_ACTIVATED");
}

void deactivateLaser() {
  laserActive = false;
  digitalWrite(laserPin, LOW);
  Serial.println("LASER_DEACTIVATED");
  // Jika dalam mode otomatis, langsung lanjutkan pergerakan servo
  if (autoMode) {
    updateServoAuto();
  }
}

void updateServoAuto() {
  if (servoIncreasing) {
    servoSetting += 1;
    if (servoSetting >= 180) {
      servoSetting = 180;
      servoIncreasing = false;
    }
  } else {
    servoSetting -= 1;
    if (servoSetting <= 0) {
      servoSetting = 0;
      servoIncreasing = true;
    }
  }
  myservo.write(servoSetting);
}

void readSerialCommand() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "AUTO") {
      autoMode = true;
      laserActive = false;
      digitalWrite(laserPin, LOW);
    } else if (command == "MANUAL") {
      autoMode = false;
      laserActive = false;
      digitalWrite(laserPin, LOW);
    } else if (command == "LASER_ON") {
      activateLaser();
    } else if (command == "LASER_OFF") {
      deactivateLaser();
    } else {
      int angle = command.toInt();
      if (angle >= 0 && angle <= 180 && !autoMode) {
        myservo.write(angle);
        servoSetting = angle;
      }
    }
  }
}

void getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
  if (distance > MAX_DETECTION_RANGE) {
    distance = MAX_DETECTION_RANGE;
  }
}

void outputDistance() {
  Serial.print(servoSetting);
  Serial.print(",");
  Serial.println(distance);
}

void sendBatteryData() {
  float shuntvoltage = ina219.getShuntVoltage_mV();
  float busvoltage = ina219.getBusVoltage_V();
  float current_mA = ina219.getCurrent_mA();
  float power_mW = ina219.getPower_mW();
  float loadvoltage = busvoltage + (shuntvoltage / 1000);

  Serial.print("B,");
  Serial.print(busvoltage);
  Serial.print(",");
  Serial.print(shuntvoltage);
  Serial.print(",");
  Serial.print(loadvoltage);
  Serial.print(",");
  Serial.print(current_mA);
  Serial.print(",");
  Serial.println(power_mW);
}
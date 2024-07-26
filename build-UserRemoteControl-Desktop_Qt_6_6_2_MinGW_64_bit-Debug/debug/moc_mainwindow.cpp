/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../UserRemoteControl/mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "readBatteryData",
    "",
    "updateServo",
    "command",
    "readSerial",
    "processRadarData",
    "data",
    "processBatteryData",
    "updateHistoricalData",
    "on_button0_clicked",
    "on_button45_clicked",
    "on_button90_clicked",
    "on_button135_clicked",
    "on_button180_clicked",
    "on_verticalSlider_valueChanged",
    "value",
    "on_button_auto_clicked",
    "updateServoAuto",
    "clearOldDetectionPoints",
    "updateDetectionPoint",
    "angle",
    "distance",
    "handleLaserActivation",
    "deactivateLaser",
    "resumeOperation",
    "updateLaserStatus",
    "status",
    "setSliderEnabled",
    "enabled",
    "updateCurrentTime",
    "handleLaserStatus"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {
    uint offsetsAndSizes[64];
    char stringdata0[11];
    char stringdata1[16];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[8];
    char stringdata5[11];
    char stringdata6[17];
    char stringdata7[5];
    char stringdata8[19];
    char stringdata9[21];
    char stringdata10[19];
    char stringdata11[20];
    char stringdata12[20];
    char stringdata13[21];
    char stringdata14[21];
    char stringdata15[31];
    char stringdata16[6];
    char stringdata17[23];
    char stringdata18[16];
    char stringdata19[24];
    char stringdata20[21];
    char stringdata21[6];
    char stringdata22[9];
    char stringdata23[22];
    char stringdata24[16];
    char stringdata25[16];
    char stringdata26[18];
    char stringdata27[7];
    char stringdata28[17];
    char stringdata29[8];
    char stringdata30[18];
    char stringdata31[18];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWindowENDCLASS_t qt_meta_stringdata_CLASSMainWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 15),  // "readBatteryData"
        QT_MOC_LITERAL(27, 0),  // ""
        QT_MOC_LITERAL(28, 11),  // "updateServo"
        QT_MOC_LITERAL(40, 7),  // "command"
        QT_MOC_LITERAL(48, 10),  // "readSerial"
        QT_MOC_LITERAL(59, 16),  // "processRadarData"
        QT_MOC_LITERAL(76, 4),  // "data"
        QT_MOC_LITERAL(81, 18),  // "processBatteryData"
        QT_MOC_LITERAL(100, 20),  // "updateHistoricalData"
        QT_MOC_LITERAL(121, 18),  // "on_button0_clicked"
        QT_MOC_LITERAL(140, 19),  // "on_button45_clicked"
        QT_MOC_LITERAL(160, 19),  // "on_button90_clicked"
        QT_MOC_LITERAL(180, 20),  // "on_button135_clicked"
        QT_MOC_LITERAL(201, 20),  // "on_button180_clicked"
        QT_MOC_LITERAL(222, 30),  // "on_verticalSlider_valueChanged"
        QT_MOC_LITERAL(253, 5),  // "value"
        QT_MOC_LITERAL(259, 22),  // "on_button_auto_clicked"
        QT_MOC_LITERAL(282, 15),  // "updateServoAuto"
        QT_MOC_LITERAL(298, 23),  // "clearOldDetectionPoints"
        QT_MOC_LITERAL(322, 20),  // "updateDetectionPoint"
        QT_MOC_LITERAL(343, 5),  // "angle"
        QT_MOC_LITERAL(349, 8),  // "distance"
        QT_MOC_LITERAL(358, 21),  // "handleLaserActivation"
        QT_MOC_LITERAL(380, 15),  // "deactivateLaser"
        QT_MOC_LITERAL(396, 15),  // "resumeOperation"
        QT_MOC_LITERAL(412, 17),  // "updateLaserStatus"
        QT_MOC_LITERAL(430, 6),  // "status"
        QT_MOC_LITERAL(437, 16),  // "setSliderEnabled"
        QT_MOC_LITERAL(454, 7),  // "enabled"
        QT_MOC_LITERAL(462, 17),  // "updateCurrentTime"
        QT_MOC_LITERAL(480, 17)   // "handleLaserStatus"
    },
    "MainWindow",
    "readBatteryData",
    "",
    "updateServo",
    "command",
    "readSerial",
    "processRadarData",
    "data",
    "processBatteryData",
    "updateHistoricalData",
    "on_button0_clicked",
    "on_button45_clicked",
    "on_button90_clicked",
    "on_button135_clicked",
    "on_button180_clicked",
    "on_verticalSlider_valueChanged",
    "value",
    "on_button_auto_clicked",
    "updateServoAuto",
    "clearOldDetectionPoints",
    "updateDetectionPoint",
    "angle",
    "distance",
    "handleLaserActivation",
    "deactivateLaser",
    "resumeOperation",
    "updateLaserStatus",
    "status",
    "setSliderEnabled",
    "enabled",
    "updateCurrentTime",
    "handleLaserStatus"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  152,    2, 0x08,    1 /* Private */,
       3,    1,  153,    2, 0x08,    2 /* Private */,
       5,    0,  156,    2, 0x08,    4 /* Private */,
       6,    1,  157,    2, 0x08,    5 /* Private */,
       8,    1,  160,    2, 0x08,    7 /* Private */,
       9,    0,  163,    2, 0x08,    9 /* Private */,
      10,    0,  164,    2, 0x08,   10 /* Private */,
      11,    0,  165,    2, 0x08,   11 /* Private */,
      12,    0,  166,    2, 0x08,   12 /* Private */,
      13,    0,  167,    2, 0x08,   13 /* Private */,
      14,    0,  168,    2, 0x08,   14 /* Private */,
      15,    1,  169,    2, 0x08,   15 /* Private */,
      17,    0,  172,    2, 0x08,   17 /* Private */,
      18,    0,  173,    2, 0x08,   18 /* Private */,
      19,    0,  174,    2, 0x08,   19 /* Private */,
      20,    2,  175,    2, 0x08,   20 /* Private */,
      23,    0,  180,    2, 0x08,   23 /* Private */,
      24,    0,  181,    2, 0x08,   24 /* Private */,
      25,    0,  182,    2, 0x08,   25 /* Private */,
      26,    1,  183,    2, 0x08,   26 /* Private */,
      28,    1,  186,    2, 0x08,   28 /* Private */,
      30,    0,  189,    2, 0x08,   30 /* Private */,
      31,    1,  190,    2, 0x08,   31 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,   21,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   27,
    QMetaType::Void, QMetaType::Bool,   29,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   27,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'readBatteryData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateServo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'readSerial'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'processRadarData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'processBatteryData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'updateHistoricalData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_button0_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_button45_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_button90_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_button135_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_button180_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_verticalSlider_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_button_auto_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateServoAuto'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clearOldDetectionPoints'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateDetectionPoint'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<float, std::false_type>,
        QtPrivate::TypeAndForceComplete<float, std::false_type>,
        // method 'handleLaserActivation'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deactivateLaser'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'resumeOperation'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateLaserStatus'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'setSliderEnabled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'updateCurrentTime'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleLaserStatus'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->readBatteryData(); break;
        case 1: _t->updateServo((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->readSerial(); break;
        case 3: _t->processRadarData((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->processBatteryData((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->updateHistoricalData(); break;
        case 6: _t->on_button0_clicked(); break;
        case 7: _t->on_button45_clicked(); break;
        case 8: _t->on_button90_clicked(); break;
        case 9: _t->on_button135_clicked(); break;
        case 10: _t->on_button180_clicked(); break;
        case 11: _t->on_verticalSlider_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->on_button_auto_clicked(); break;
        case 13: _t->updateServoAuto(); break;
        case 14: _t->clearOldDetectionPoints(); break;
        case 15: _t->updateDetectionPoint((*reinterpret_cast< std::add_pointer_t<float>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[2]))); break;
        case 16: _t->handleLaserActivation(); break;
        case 17: _t->deactivateLaser(); break;
        case 18: _t->resumeOperation(); break;
        case 19: _t->updateLaserStatus((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 20: _t->setSliderEnabled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 21: _t->updateCurrentTime(); break;
        case 22: _t->handleLaserStatus((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 23;
    }
    return _id;
}
QT_WARNING_POP

/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Git/Projects/DuplicateFinder/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[25];
    char stringdata0[424];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 13), // "StartHashing1"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 7), // "DirName"
QT_MOC_LITERAL(4, 34, 13), // "ExludeDirName"
QT_MOC_LITERAL(5, 48, 15), // "InsidersAllowed"
QT_MOC_LITERAL(6, 64, 13), // "StartHashing2"
QT_MOC_LITERAL(7, 78, 14), // "WorkerFinished"
QT_MOC_LITERAL(8, 93, 7), // "GetData"
QT_MOC_LITERAL(9, 101, 22), // "on_CheckButton_clicked"
QT_MOC_LITERAL(10, 124, 24), // "on_RefreshButton_clicked"
QT_MOC_LITERAL(11, 149, 31), // "on_ResultList_itemDoubleClicked"
QT_MOC_LITERAL(12, 181, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(13, 198, 4), // "item"
QT_MOC_LITERAL(14, 203, 26), // "on_UpperList_doubleClicked"
QT_MOC_LITERAL(15, 230, 5), // "index"
QT_MOC_LITERAL(16, 236, 26), // "on_LowerList_doubleClicked"
QT_MOC_LITERAL(17, 263, 21), // "on_SortButton_clicked"
QT_MOC_LITERAL(18, 285, 21), // "on_StopButton_clicked"
QT_MOC_LITERAL(19, 307, 26), // "on_UpperInsideDirs_toggled"
QT_MOC_LITERAL(20, 334, 7), // "checked"
QT_MOC_LITERAL(21, 342, 26), // "on_LowerInsideDirs_toggled"
QT_MOC_LITERAL(22, 369, 24), // "on_LowerLine_textChanged"
QT_MOC_LITERAL(23, 394, 4), // "arg1"
QT_MOC_LITERAL(24, 399, 24) // "on_UpperLine_textChanged"

    },
    "MainWindow\0StartHashing1\0\0DirName\0"
    "ExludeDirName\0InsidersAllowed\0"
    "StartHashing2\0WorkerFinished\0GetData\0"
    "on_CheckButton_clicked\0on_RefreshButton_clicked\0"
    "on_ResultList_itemDoubleClicked\0"
    "QListWidgetItem*\0item\0on_UpperList_doubleClicked\0"
    "index\0on_LowerList_doubleClicked\0"
    "on_SortButton_clicked\0on_StopButton_clicked\0"
    "on_UpperInsideDirs_toggled\0checked\0"
    "on_LowerInsideDirs_toggled\0"
    "on_LowerLine_textChanged\0arg1\0"
    "on_UpperLine_textChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   89,    2, 0x06 /* Public */,
       6,    3,   96,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,  103,    2, 0x08 /* Private */,
       8,    2,  104,    2, 0x08 /* Private */,
       9,    0,  109,    2, 0x08 /* Private */,
      10,    0,  110,    2, 0x08 /* Private */,
      11,    1,  111,    2, 0x08 /* Private */,
      14,    1,  114,    2, 0x08 /* Private */,
      16,    1,  117,    2, 0x08 /* Private */,
      17,    0,  120,    2, 0x08 /* Private */,
      18,    0,  121,    2, 0x08 /* Private */,
      19,    1,  122,    2, 0x08 /* Private */,
      21,    1,  125,    2, 0x08 /* Private */,
      22,    1,  128,    2, 0x08 /* Private */,
      24,    1,  131,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool,    3,    4,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool,    3,    4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, QMetaType::QModelIndex,   15,
    QMetaType::Void, QMetaType::QModelIndex,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::QString,   23,
    QMetaType::Void, QMetaType::QString,   23,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->StartHashing1((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const bool(*)>(_a[3]))); break;
        case 1: _t->StartHashing2((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const bool(*)>(_a[3]))); break;
        case 2: _t->WorkerFinished(); break;
        case 3: _t->GetData((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->on_CheckButton_clicked(); break;
        case 5: _t->on_RefreshButton_clicked(); break;
        case 6: _t->on_ResultList_itemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 7: _t->on_UpperList_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 8: _t->on_LowerList_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 9: _t->on_SortButton_clicked(); break;
        case 10: _t->on_StopButton_clicked(); break;
        case 11: _t->on_UpperInsideDirs_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->on_LowerInsideDirs_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->on_LowerLine_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->on_UpperLine_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (MainWindow::*_t)(const QString & , const QString & , const bool & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::StartHashing1)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(const QString & , const QString & , const bool & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::StartHashing2)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::StartHashing1(const QString & _t1, const QString & _t2, const bool & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::StartHashing2(const QString & _t1, const QString & _t2, const bool & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LookingForDuplicates/mainwindow.h"
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
    QByteArrayData data[23];
    char stringdata0[389];
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
QT_MOC_LITERAL(7, 78, 19), // "SendInsiderDirsFlag"
QT_MOC_LITERAL(8, 98, 14), // "WorkerFinished"
QT_MOC_LITERAL(9, 113, 22), // "on_CheckButton_clicked"
QT_MOC_LITERAL(10, 136, 24), // "on_RefreshButton_clicked"
QT_MOC_LITERAL(11, 161, 31), // "on_ResultList_itemDoubleClicked"
QT_MOC_LITERAL(12, 193, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(13, 210, 4), // "item"
QT_MOC_LITERAL(14, 215, 26), // "on_UpperList_doubleClicked"
QT_MOC_LITERAL(15, 242, 5), // "index"
QT_MOC_LITERAL(16, 248, 26), // "on_LowerList_doubleClicked"
QT_MOC_LITERAL(17, 275, 7), // "GetData"
QT_MOC_LITERAL(18, 283, 21), // "on_SortButton_clicked"
QT_MOC_LITERAL(19, 305, 21), // "on_StopButton_clicked"
QT_MOC_LITERAL(20, 327, 26), // "on_UpperInsideDirs_toggled"
QT_MOC_LITERAL(21, 354, 7), // "checked"
QT_MOC_LITERAL(22, 362, 26) // "on_LowerInsideDirs_toggled"

    },
    "MainWindow\0StartHashing1\0\0DirName\0"
    "ExludeDirName\0InsidersAllowed\0"
    "StartHashing2\0SendInsiderDirsFlag\0"
    "WorkerFinished\0on_CheckButton_clicked\0"
    "on_RefreshButton_clicked\0"
    "on_ResultList_itemDoubleClicked\0"
    "QListWidgetItem*\0item\0on_UpperList_doubleClicked\0"
    "index\0on_LowerList_doubleClicked\0"
    "GetData\0on_SortButton_clicked\0"
    "on_StopButton_clicked\0on_UpperInsideDirs_toggled\0"
    "checked\0on_LowerInsideDirs_toggled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   84,    2, 0x06 /* Public */,
       6,    3,   91,    2, 0x06 /* Public */,
       7,    0,   98,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   99,    2, 0x08 /* Private */,
       9,    0,  100,    2, 0x08 /* Private */,
      10,    0,  101,    2, 0x08 /* Private */,
      11,    1,  102,    2, 0x08 /* Private */,
      14,    1,  105,    2, 0x08 /* Private */,
      16,    1,  108,    2, 0x08 /* Private */,
      17,    2,  111,    2, 0x08 /* Private */,
      18,    0,  116,    2, 0x08 /* Private */,
      19,    0,  117,    2, 0x08 /* Private */,
      20,    1,  118,    2, 0x08 /* Private */,
      22,    1,  121,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool,    3,    4,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool,    3,    4,    5,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, QMetaType::QModelIndex,   15,
    QMetaType::Void, QMetaType::QModelIndex,   15,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   21,
    QMetaType::Void, QMetaType::Bool,   21,

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
        case 2: _t->SendInsiderDirsFlag(); break;
        case 3: _t->WorkerFinished(); break;
        case 4: _t->on_CheckButton_clicked(); break;
        case 5: _t->on_RefreshButton_clicked(); break;
        case 6: _t->on_ResultList_itemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 7: _t->on_UpperList_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 8: _t->on_LowerList_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 9: _t->GetData((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 10: _t->on_SortButton_clicked(); break;
        case 11: _t->on_StopButton_clicked(); break;
        case 12: _t->on_UpperInsideDirs_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->on_LowerInsideDirs_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
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
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::SendInsiderDirsFlag)) {
                *result = 2;
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
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
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

// SIGNAL 2
void MainWindow::SendInsiderDirsFlag()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

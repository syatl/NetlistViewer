/****************************************************************************
** Meta object code from reading C++ file 'CellViewer.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/CellViewer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CellViewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Netlist__CellViewer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x0a,
      36,   20,   20,   20, 0x0a,
      47,   20,   20,   20, 0x0a,
      58,   20,   20,   20, 0x0a,
      73,   20,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Netlist__CellViewer[] = {
    "Netlist::CellViewer\0\0setCell(Cell*)\0"
    "saveCell()\0openCell()\0showCellsLib()\0"
    "showInstancesWidget()\0"
};

void Netlist::CellViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CellViewer *_t = static_cast<CellViewer *>(_o);
        switch (_id) {
        case 0: _t->setCell((*reinterpret_cast< Cell*(*)>(_a[1]))); break;
        case 1: _t->saveCell(); break;
        case 2: _t->openCell(); break;
        case 3: _t->showCellsLib(); break;
        case 4: _t->showInstancesWidget(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Netlist::CellViewer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Netlist::CellViewer::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Netlist__CellViewer,
      qt_meta_data_Netlist__CellViewer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Netlist::CellViewer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Netlist::CellViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Netlist::CellViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Netlist__CellViewer))
        return static_cast<void*>(const_cast< CellViewer*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Netlist::CellViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

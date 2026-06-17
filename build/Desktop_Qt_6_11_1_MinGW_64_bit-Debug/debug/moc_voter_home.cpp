/****************************************************************************
** Meta object code from reading C++ file 'voter_home.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../voter_home.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'voter_home.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.1. It"
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
struct qt_meta_tag_ZN15VoterHomeWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto VoterHomeWindow::qt_create_metaobjectdata<qt_meta_tag_ZN15VoterHomeWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "VoterHomeWindow",
        "logout",
        ""
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'logout'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<VoterHomeWindow, qt_meta_tag_ZN15VoterHomeWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject VoterHomeWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15VoterHomeWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15VoterHomeWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15VoterHomeWindowE_t>.metaTypes,
    nullptr
} };

void VoterHomeWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<VoterHomeWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->logout(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *VoterHomeWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VoterHomeWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15VoterHomeWindowE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int VoterHomeWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP

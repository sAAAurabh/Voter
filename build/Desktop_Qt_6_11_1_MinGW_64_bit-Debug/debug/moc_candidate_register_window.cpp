/****************************************************************************
** Meta object code from reading C++ file 'candidate_register_window.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../candidate_register_window.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'candidate_register_window.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN23CandidateRegisterWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto CandidateRegisterWindow::qt_create_metaobjectdata<qt_meta_tag_ZN23CandidateRegisterWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "CandidateRegisterWindow",
        "register_user",
        "",
        "close_register",
        "clear_fields",
        "upload_photo"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'register_user'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'close_register'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'clear_fields'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'upload_photo'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<CandidateRegisterWindow, qt_meta_tag_ZN23CandidateRegisterWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject CandidateRegisterWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN23CandidateRegisterWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN23CandidateRegisterWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN23CandidateRegisterWindowE_t>.metaTypes,
    nullptr
} };

void CandidateRegisterWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<CandidateRegisterWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->register_user(); break;
        case 1: _t->close_register(); break;
        case 2: _t->clear_fields(); break;
        case 3: _t->upload_photo(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *CandidateRegisterWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CandidateRegisterWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN23CandidateRegisterWindowE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CandidateRegisterWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP

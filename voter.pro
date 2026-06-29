QT += widgets
QT += sql

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    candidate.cpp \
    candidate_home.cpp \
    candidate_login_window.cpp \
    candidate_register_window.cpp \
    database.cpp \
    main.cpp \
<<<<<<< HEAD
    main_window.cpp \
=======
    roleselection.cpp \
>>>>>>> 66122f6f8cb9dcfdb07fdedad9498476192afe7b
    voter.cpp \
    voter_home.cpp \
    voter_login_window.cpp \
    voter_register_window.cpp \
    voting_page.cpp \
    widget.cpp \
    manifesto_edit_window.cpp \
    view_candidates_window.cpp

HEADERS += \
    admin.h \
    candidate.h \
    candidate_home.h \
    candidate_login_window.h \
    candidate_register_window.h \
    database.h \
    main_window.h \
    picosh.h \
    roleselection.h \
    voter.h \
    voter_home.h \
    voter_login_window.h \
    voter_register_window.h \
    voting_page.h \
    widget.h \
    manifesto_edit_window.h \
    view_candidates_window.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    candidate \
    manifesto \
    voter

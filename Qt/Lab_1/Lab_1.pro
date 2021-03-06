#-------------------------------------------------
#
# Project created by QtCreator 2019-03-03T11:53:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab_1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    windowadmin.cpp \
    windowdriver.cpp \
    registration.cpp \
    person.cpp \
    admin.cpp \
    driver.cpp \
    database.cpp \
    departurejournal.cpp \
    writejournal.cpp \
    wiewjournaluser.cpp \
    changepass.cpp \
    newauto.cpp \
    mydepartures.cpp

HEADERS += \
        mainwindow.h \
    windowadmin.h \
    windowdriver.h \
    registration.h \
    person.h \
    admin.h \
    driver.h \
    database.h \
    departurejournal.h \
    writejournal.h \
    wiewjournaluser.h \
    changepass.h \
    newauto.h \
    mydepartures.h

FORMS += \
        mainwindow.ui \
    windowadmin.ui \
    windowdriver.ui \
    registration.ui \
    departurejournal.ui \
    writejournal.ui \
    wiewjournaluser.ui \
    changepass.ui \
    newauto.ui \
    mydepartures.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

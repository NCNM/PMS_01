#-------------------------------------------------
#
# Project created by QtCreator 2016-04-01T15:08:04
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PMS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dashboardwindow.cpp \
    healthcarewindow.cpp \
    diningwindow.cpp \
    rehabform.cpp \
    entryreleaseform.cpp \
    managementwindow.cpp \
    loginwindow.cpp \
    database.cpp

HEADERS  += mainwindow.h \
    dashboardwindow.h \
    healthcarewindow.h \
    diningwindow.h \
    rehabform.h \
    entryreleaseform.h \
    managementwindow.h \
    loginwindow.h \
    database.h

FORMS    += mainwindow.ui \
    dashboardwindow.ui \
    healthcarewindow.ui \
    diningwindow.ui \
    rehabform.ui \
    entryreleaseform.ui \
    managementwindow.ui \
    loginwindow.ui

RESOURCES += \
    pms_resources.qrc

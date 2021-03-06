#-------------------------------------------------
#
# Project created by QtCreator 2018-12-08T18:33:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = optics_simulator
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

CONFIG += c++14

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    qcustomplot.cpp \
    lens.cpp \
    lensviewer.cpp \
    laseradder.cpp

HEADERS += \
        mainwindow.h \
    point2d.h \
    point2d_test.h \
    point2d_series.h \
    point2d_series_test.h \
    matrix.h \
    matrix_test.h \
    scalar_field.h \
    scalar_field_test.h \
    vector_field.h \
    vector_field_test.h \
    lens.h \
    lens_test.h \
    ior_field.h \
    ior_field_test.h \
    laser.h \
    laser_test.h \
    qcustomplot.h \
    lensviewer.h \
    laseradder.h \
    laser_device.h

FORMS += \
        mainwindow.ui \
    lensviewer.ui \
    laseradder.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += qwt

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/adcqwtplot.cpp \
    src/adcremotectrl.cpp \
    src/adcudpreceiver.cpp \
    src/dataprocessor.cpp \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    include/adcqwtplot.h \
    include/adcremotectrl.h \
    include/adcudpreceiver.h \
    include/dataprocessor.h \
    include/mainwindow.h

FORMS += \
    mainwindow.ui

OBJECTS_DIR = build
MOC_DIR = autogen
UI_DIR = autogen

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -L "$$_PRO_FILE_PWD_/3rdparty/fftw3/" -lfftw3
LIBS +=  "$$_PRO_FILE_PWD_/3rdparty/qwt/libqwt.so"
INCLUDEPATH += "include"
INCLUDEPATH += "$$_PRO_FILE_PWD_/3rdparty/qwt/"
INCLUDEPATH += "$$_PRO_FILE_PWD_/3rdparty/fftw3/"

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


INCLUDEPATH += "E:\ComputerVision\Laborator\opencv\opencv\build\include"
LIBS += "E:\ComputerVision\Laborator\opencv\opencv\build\x64\vc15\lib\opencv_world412.lib"
DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

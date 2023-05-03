#-------------------------------------------------
#
# Project created by QtCreator 2022-01-05T18:15:58
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mapgen
TEMPLATE = app
QMAKE_LFLAGS += -no-pie
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

RESOURCES += resources.qrc


# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += ./include

SOURCES += \
        src/main.cpp \
        src/dialog.cpp \
    	src/handle.cpp \
    	src/obstacle.cpp \
    	src/obstaclebase.cpp \
    	src/exporter.cpp \
    	src/gate.cpp \
    	src/misc.cpp \
    	src/robot.cpp

HEADERS += \
        include/dialog.h \
    	include/handle.h \
    	include/obstacle.h \
    	include/obstaclebase.h \
    	include/exporter.h \
    	include/gate.h \
    	include/misc.h \
    	include/robot.h

FORMS += \
        dialog.ui

#-------------------------------------------------
#
# Project created by QtCreator 2012-10-24T22:26:09
#
#-------------------------------------------------

QMAKE_CXXFLAGS += -std=c++0x

QT       += core gui

TARGET = dic_sim
TEMPLATE = app

INCLUDEPATH += include

RESOURCES += \
    resource.qrc

OTHER_FILES += \
    icd.l \
    icd.y

SOURCES += \
    src/wire.cpp \
    src/togglebutton.cpp \
    src/quickunion.cpp \
    src/powerbutton.cpp \
    src/mainwindow.cpp \
    src/main.cpp \
    src/led.cpp \
    src/icviewer.cpp \
    src/icparser.cpp \
    src/iclexer.cpp \
    src/icdialog.cpp \
    src/ic.cpp \
    src/console.cpp \
    src/circuit.cpp \
    src/cell.cpp \
    src/breadboard.cpp \
    src/block.cpp

HEADERS += \
    include/wire.h \
    include/utility.h \
    include/togglebutton.h \
    include/state.h \
    include/quickunion.h \
    include/powerbutton.h \
    include/mainwindow.h \
    include/led.h \
    include/icviewer.h \
    include/icparser.h \
    include/iclexer.h \
    include/icdialog.h \
    include/ic.h \
    include/console.h \
    include/circuit.h \
    include/cell.h \
    include/breadboard.h \
    include/blockdata.h \
    include/block.h \
    include/constants.h

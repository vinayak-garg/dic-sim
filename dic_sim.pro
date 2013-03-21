#-------------------------------------------------
#
# Project created by QtCreator 2012-10-24T22:26:09
#
#-------------------------------------------------

QMAKE_CXXFLAGS += -std=c++0x

QT       += core gui

TARGET = dic_sim
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    console.cpp \
    breadboard.cpp \
    cell.cpp \
    wire.cpp \
    led.cpp \
    powerbutton.cpp \
    togglebutton.cpp \
    ic.cpp \
    icparser.cpp \
    iclexer.cpp \
    icviewer.cpp \
    icdialog.cpp \
    circuit.cpp \
    block.cpp \
    quickunion.cpp

HEADERS  += mainwindow.h \
    console.h \
    breadboard.h \
    cell.h \
    wire.h \
    led.h \
    utility.h \
    powerbutton.h \
    togglebutton.h \
    ic.h \
    iclexer.h \
    icparser.h \
    icviewer.h \
    icdialog.h \
    circuit.h \
    blockdata.h \
    block.h \
    quickunion.h \
    state.h

RESOURCES += \
    resource.qrc

OTHER_FILES += \
    icd.l \
    icd.y

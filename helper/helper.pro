include(../globals.pri)

TEMPLATE = app
TARGET = ambiancechanger-helper

QT = core gui

SOURCES +=  main.cpp

target.path = $${BINDIR}
INSTALLS += target

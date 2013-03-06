#TARGET = ambiancechanger

#SOURCES += main.cpp

#HEADERS +=

#desktop.files = ambiancechanger.desktop
#qml.files = *.qml pages cover main.qml

## Please do not modify the following line.
#include(sailfishapplication/sailfishapplication.pri)

#OTHER_FILES = rpm/ambiancechanger.yaml


TEMPLATE = subdirs
SUBDIRS = gui helper

TEMPLATE = app
TARGET = ambiancechanger-helper

QT = core gui

SOURCES += \
    main.cpp

TARGETPATH = /opt/sdk/bin
target.path = $$TARGETPATH
INSTALLS += target

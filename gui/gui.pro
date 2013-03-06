TEMPLATE = app
TARGET = ambiancechanger

QT += core gui declarative

SOURCES +=  sailfishapplication.cpp \
            main.cpp \
    suhelper.cpp \
    testhelper.cpp \
    helperlauncher.cpp
HEADERS +=  sailfishapplication.h \
    suhelper.h \
    testhelper.h \
    helperlauncher.h

OTHER_FILES +=  main.qml \
    AmbianceChangerPage.qml \
    TestPage.qml

TARGETPATH = /opt/sdk/bin
target.path = $$TARGETPATH

DEPLOYMENT_PATH = /opt/sdk/share/$$TARGET
qml.path = $$DEPLOYMENT_PATH
qml.files = $${OTHER_FILES}
desktop.path = /opt/sdk/share/applications

contains(CONFIG, desktop) {
    DEFINES *= DESKTOP
    QT += opengl
}

INSTALLS += target qml desktop

DEFINES += DEPLOYMENT_PATH=\"\\\"\"$${DEPLOYMENT_PATH}/\"\\\"\"

CONFIG += link_pkgconfig
packagesExist(qdeclarative-boostable) {
    message("Building with qdeclarative-boostable support")
    DEFINES += HAS_BOOSTER
    PKGCONFIG += qdeclarative-boostable
} else {
    warning("qdeclarative-boostable not available; startup times will be slower")
}





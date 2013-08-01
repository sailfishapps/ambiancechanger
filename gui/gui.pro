include(../globals.pri)

TEMPLATE = app
TARGET = ambiancechanger

QT += core gui quick qml

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
                TestPage.qml \
                AmbianceChangerPage.qml

target.path = $${BINDIR}

qml.path = $${SHAREDIR}
qml.files = $${OTHER_FILES}
desktop.files = ambiancechanger.desktop
desktop.path = $${APPLICATIONSDIR}

contains(CONFIG, desktop) {
    DEFINES *= DESKTOP
    QT += opengl
}

INSTALLS += target qml
!CONFIG(sdk): INSTALLS += desktop

DEFINES += DEPLOYMENT_PATH=\"\\\"\"$${SHAREDIR}/\"\\\"\"

CONFIG += link_pkgconfig
packagesExist(qdeclarative-boostable) {
    message("Building with qdeclarative-boostable support")
    DEFINES += HAS_BOOSTER
    PKGCONFIG += qdeclarative-boostable
} else {
    warning("qdeclarative-boostable not available; startup times will be slower")
}





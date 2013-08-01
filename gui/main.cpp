
#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtQml/qqml.h>

#include "sailfishapplication.h"
#include "testhelper.h"
#include "helperlauncher.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> app(Sailfish::createApplication(argc, argv));
    qmlRegisterType<TestHelper>("org.SfietKonstantin.ambiancechanger", 1, 0, "TestHelper");
    qmlRegisterType<HelperLauncher>("org.SfietKonstantin.ambiancechanger", 1, 0, "HelperLauncher");
    QScopedPointer<QQuickView> view(Sailfish::createView("main.qml"));
    Sailfish::showView(view.data());

    return app->exec();
}



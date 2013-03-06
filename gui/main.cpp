
#include <QtGui/QApplication>
#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/qdeclarative.h>

#include "sailfishapplication.h"
#include "testhelper.h"
#include "helperlauncher.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    qmlRegisterType<TestHelper>("org.SfietKonstantin.ambiancechanger", 1, 0, "TestHelper");
    qmlRegisterType<HelperLauncher>("org.SfietKonstantin.ambiancechanger", 1, 0, "HelperLauncher");
    QScopedPointer<QApplication> app(Sailfish::createApplication(argc, argv));
    QScopedPointer<QDeclarativeView> view(Sailfish::createUninitializedView());
    Sailfish::initializeView(view.data(), "main.qml");
    Sailfish::showView(view.data());

    return app->exec();
}



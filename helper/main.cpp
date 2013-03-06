#include <QtCore/QCoreApplication>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <QtCore/QProcess>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtGui/QImage>

static const char *WALLPAPER_NAME = "wallpaper.jpg";

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    QString firstArg = app.arguments().at(1);
    if (firstArg == "--ping") {
        qDebug() << "Pong !";
        return 0;
    } else if (firstArg == "--reboot") {
        QProcess::startDetached("systemctl isolate graphical.target");
//        QProcess::execute("reboot");
    } else if (firstArg == "--setbg") {
        QString secondArg = app.arguments().at(2);
        QDir themeDir = QDir("/usr/share/themes/jolla-ambient/meegotouch/images/");
        if (themeDir.exists(WALLPAPER_NAME)) {
            QFile::remove(themeDir.absoluteFilePath(WALLPAPER_NAME));
        }
        QImage image;
        if (!image.load(secondArg)) {
            qDebug() << "Failed to open image" << secondArg;
            return 1;
        }
        image.save(themeDir.absoluteFilePath(WALLPAPER_NAME), "JPG");
        qDebug() << "Background changed";
        return 0;

    }

//    return app.exec();
    return 0;
}

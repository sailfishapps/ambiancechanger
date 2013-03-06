#include "helperlauncher.h"
#include <QtCore/QProcess>
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>

HelperLauncher::HelperLauncher(QObject *parent) :
    QObject(parent)
{
}

bool HelperLauncher::setBackground(const QUrl &absolutePath)
{
    QDir dir (QCoreApplication::instance()->applicationDirPath());
    QString command = "sudo ";
    command.append(dir.absoluteFilePath("ambiancechanger-helper"));
    command.append(" --setbg ");
    command.append(absolutePath.toLocalFile());
    int code = QProcess::execute(command);
    return (code == 0);
}

void HelperLauncher::removeSettings()
{
    QString command = "gconftool-2 -u ";
    command.append("/desktop/jolla/background/portrait/home_picture_filename");
    QProcess::execute(command);

    command = "gconftool-2 -u ";
    command.append("/desktop/jolla/background/portrait/app_picture_filename");
    QProcess::execute(command);
}

void HelperLauncher::reboot()
{
    QDir dir (QCoreApplication::instance()->applicationDirPath());
    QString command = "sudo ";
    command.append(dir.absoluteFilePath("ambiancechanger-helper"));
    command.append(" --reboot");
    QProcess::execute(command);
}

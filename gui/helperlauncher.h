#ifndef HELPERLAUNCHER_H
#define HELPERLAUNCHER_H

#include <QtCore/QObject>
#include <QtCore/QUrl>

class HelperLauncher : public QObject
{
    Q_OBJECT
public:
    explicit HelperLauncher(QObject *parent = 0);
    Q_INVOKABLE static bool setBackground(const QUrl &absolutePath);
signals:

public slots:
    static void removeSettings();
    static void reboot();
};

#endif // HELPERLAUNCHER_H

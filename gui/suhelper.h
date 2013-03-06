#ifndef SUHELPER_H
#define SUHELPER_H

#include <QtCore/QObject>

class QProcess;
class QTimer;
class SuHelper: public QObject
{
    Q_OBJECT
public:
    explicit SuHelper(QObject *parent = 0);
public slots:
    void startSu();
private:
    QProcess *m_process;
    QTimer *m_timer;
    int m_step;
private slots:
//    void slotTimeout();
//    void slotFinished(int code);
//    void slotReadyRead();
};

#endif // SUHELPER_H

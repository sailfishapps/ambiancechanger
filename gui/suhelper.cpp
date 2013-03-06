#include "suhelper.h"
#include <QtCore/QProcess>
#include <QtCore/QTimer>
#include <QtCore/QDebug>

SuHelper::SuHelper(QObject *parent):
    QObject(parent)
{
    m_process = 0;
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    m_timer->setSingleShot(true);
    m_step = 0;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(slotTimeout()));
}

void SuHelper::startSu()
{
    if (m_process) {
        return;
    }

    m_process = new QProcess(this);
//    connect(m_process, SIGNAL(finished(int)), this, SLOT(slotFinished(int)));
//    connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(slotReadyRead()));
////    QStringList args;
////    args << "-s" << "su";
////    args << "echo" << "\"test\"";
////    m_process->start("/bin/bash -c \"su\"");
//    m_process->start("/bin/bash");
//    m_timer->start();
    m_process->start("/bin/sh");
    m_process->waitForStarted();
    m_process->write("su\n");
    m_process->waitForReadyRead(1000);
    m_process->write("nemo\n");
    m_process->waitForReadyRead(1000);
    qDebug() << m_process->readAllStandardOutput();
    m_process->write("users\n");
    m_process->waitForReadyRead(1000);
    qDebug() << m_process->readAllStandardOutput();
//    Q_FOREACH( QString cmd, QStringList() << "ls" << "date" << "echo test" )
//    {
//        m_process->write((cmd + "\n").toLocal8Bit());
//        m_process->waitForReadyRead();
//        qDebug() << m_process->readAllStandardOutput().split('\n');
//    }
//    m_process->write("exit\n");
//    m_process->waitForFinished();
}

//void SuHelper::slotTimeout()
//{
////    m_process->write("nemo");
//    switch (m_step) {
//    case 0:
//        m_process->write("su");
//        qDebug() << "Su sent";
//        m_timer->start();
//        break;
//    case 1:
//        m_process->write("nemo");
//        qDebug() << "PW sent";
//        m_timer->start();
//        break;
//    case 2:
//        m_process->write("pwd");
//        qDebug() << "PWD sent";
//        break;
//    }
//    m_step ++;
//}

//void SuHelper::slotFinished(int code)
//{
//    qDebug() << code << "Finished";
//}

//void SuHelper::slotReadyRead()
//{
////    qDebug() << m_process->readAllStandardOutput();
//    qDebug() << m_process->readAllStandardOutput();
//    qDebug() << m_process->readAllStandardError();
//}

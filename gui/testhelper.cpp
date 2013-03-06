#include "testhelper.h"
#include <QtCore/QDebug>
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>

TestHelper::TestHelper(QObject *parent) :
    QObject(parent)
{
    m_process = 0;
    m_sudoTest = NotAvailable;
    m_helperTest = NotAvailable;
    m_sudoHelperLaunchTest = NotAvailable;
}

TestHelper::Status TestHelper::sudoTest() const
{
    return m_sudoTest;
}


TestHelper::Status TestHelper::helperTest() const
{
    return m_helperTest;
}

TestHelper::Status TestHelper::sudoHelperLaunchTest() const
{
    return m_sudoHelperLaunchTest;
}


void TestHelper::testSudo()
{
    if (m_process) {
        return;
    }

    setSudoTest(Running);

    m_process = new QProcess(this);
    connect(m_process, SIGNAL(error(QProcess::ProcessError)),
            this, SLOT(slotTestSudoError(QProcess::ProcessError)));
    connect(m_process, SIGNAL(finished(int)),
            this, SLOT(slotTestSudoFinished(int)));
    m_process->start("sudo -V");
    qDebug() << "Test sudo started";
}

void TestHelper::testHelper()
{
    QDir dir (QCoreApplication::applicationDirPath());
    if (dir.exists("ambiancechanger-helper")) {
        setHelperTest(Success);
    } else {
        setHelperTest(Failure);
    }
}

void TestHelper::testSudoHelperLaunch()
{
    if (m_process) {
        return;
    }

    setSudoHelperLaunchTest(Running);
    QDir dir (QCoreApplication::applicationDirPath());
    QString command = "sudo ";
    command.append(dir.absoluteFilePath("ambiancechanger-helper"));
    command.append(" --ping");

    m_process = new QProcess(this);
    connect(m_process, SIGNAL(error(QProcess::ProcessError)),
            this, SLOT(slotTestSudoHelperLaunchError(QProcess::ProcessError)));
    connect(m_process, SIGNAL(finished(int)),
            this, SLOT(slotTestSudoHelperLaunchFinished(int)));
    m_process->start(command);
    qDebug() << "Test sudo helper launch started";
}

void TestHelper::slotTestSudoError(QProcess::ProcessError error)
{
    qDebug() << "Test sudo failed: error" << error;
    deleteProcess();
    setSudoTest(Failure);
}

void TestHelper::slotTestSudoFinished(int exitCode)
{
    Status status = Failure;
    if (exitCode != 0) {
        qDebug() << "Test sudo failed: exit code: " << exitCode;
    } else {
        qDebug() << "Test sudo successful";
        status = Success;
    }
    deleteProcess();
    setSudoTest(status);
}

void TestHelper::slotTestSudoHelperLaunchError(QProcess::ProcessError error)
{
    qDebug() << "Test sudo helper launch failed: error" << error;
    deleteProcess();
    setSudoHelperLaunchTest(Failure);
}

void TestHelper::slotTestSudoHelperLaunchFinished(int exitCode)
{
    Status status = Failure;
    if (exitCode != 0) {
        qDebug() << "Test sudo helper launch failed: exit code: " << exitCode;
    } else {
        qDebug() << "Test sudo helper launch successful";
        status = Success;
    }
    deleteProcess();
    setSudoHelperLaunchTest(status);
}

void TestHelper::deleteProcess()
{
    if (m_process) {
        m_process->waitForFinished();
        m_process->deleteLater();
        m_process = 0;
    }
}

void TestHelper::setSudoTest(Status status)
{
    if (m_sudoTest != status) {
        m_sudoTest = status;
        emit sudoTestChanged();
    }
}

void TestHelper::setHelperTest(Status status)
{
    if (m_helperTest != status) {
        m_helperTest = status;
        emit helperTestChanged();
    }
}

void TestHelper::setSudoHelperLaunchTest(Status status)
{
    if (m_sudoHelperLaunchTest != status) {
        m_sudoHelperLaunchTest = status;
        emit sudoHelperLaunchTestChanged();
    }
}

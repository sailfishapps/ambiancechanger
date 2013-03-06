#ifndef TESTHELPER_H
#define TESTHELPER_H

#include <QtCore/QObject>
#include <QtCore/QProcess>

class TestHelper : public QObject
{
    Q_OBJECT
    Q_ENUMS(Status)
    Q_PROPERTY(Status sudoTest READ sudoTest NOTIFY sudoTestChanged)
    Q_PROPERTY(Status helperTest READ helperTest NOTIFY helperTestChanged)
    Q_PROPERTY(Status sudoHelperLaunchTest READ sudoHelperLaunchTest
               NOTIFY sudoHelperLaunchTestChanged)
public:
    enum Status {
        NotAvailable, Running, Success, Failure
    };

    explicit TestHelper(QObject *parent = 0);
    Status sudoTest() const;
    Status helperTest() const;
    Status sudoHelperLaunchTest() const;
public slots:
    void testSudo();
    void testHelper();
    void testSudoHelperLaunch();
signals:
    void sudoTestChanged();
    void helperTestChanged();
    void sudoHelperLaunchTestChanged();
private slots:
    void slotTestSudoError(QProcess::ProcessError error);
    void slotTestSudoFinished(int exitCode);
    void slotTestSudoHelperLaunchError(QProcess::ProcessError error);
    void slotTestSudoHelperLaunchFinished(int exitCode);
private:
    void deleteProcess();
    void setSudoTest(Status status);
    void setHelperTest(Status status);
    void setSudoHelperLaunchTest(Status status);
    Status m_sudoTest;
    Status m_helperTest;
    Status m_sudoHelperLaunchTest;
    QProcess *m_process;
};

#endif // TESTHELPER_H

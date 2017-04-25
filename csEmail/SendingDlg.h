#ifndef SENDINGDLG_H
#define SENDINGDLG_H
#include "qt.h"
#include <QProgressBar>
#include <QTextBrowser>
#include <QTimer>
#include "MySmtp.h"
class SendingDlg : public QDialog
{
    Q_OBJECT
public:
    SendingDlg(MailData md, QWidget *parent = 0);
private:
    QTextBrowser *mTextBrowser;
    QProgressBar *mProgBar;
    QVBoxLayout  *mainLyt;
    MySmtp *mSmtp;
    MailData mMD;
    int v;
    QTimer *timer;
signals:
    void send2Box(MailData &md);
private slots:
    void protest(string str);
    void startSend();
};

#endif // SENDINGDLG_H

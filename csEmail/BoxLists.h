#ifndef BOXLISTS_H
#define BOXLISTS_H

#include "qt.h"
#include "MailList.h"
#include "MyPop.h"
#include <QTextBrowser>
#include <QProgressBar>
#include <QTimer>
class RecvList:public MailList{
    Q_OBJECT
public:
    RecvList(QWidget *parent = 0);
private:
    QAction *mReply;
    QAction *mTranSf;
signals:
    void reply(MailData md);
    void transfer(MailData md);
    void send2Dust(MailData &md);
public slots:
    void recvMail();
private slots:
    void getlmd(list<MailData> &lmd);
    void openMail();
    void deleMail();
    void contextMenuEvent(QContextMenuEvent *event);
};
class SendList:public MailList{
    Q_OBJECT
public:
    SendList(QWidget *parent = 0);
public slots:
    void appendMD(MailData &md);
private slots:
    void openMail();
    void deleMail();
    void contextMenuEvent(QContextMenuEvent *event);
};

class DrftList:public MailList{
    Q_OBJECT
public:
    DrftList(QWidget *parent = 0);
private:
    int mRow;
signals:
    void MDToSend(MailData &md);
public slots:
    void openDraft();
    void deleDraft();
    void draft2Send(MailData &md);
    void replaceDraft(MailData &md);
private:
    void contextMenuEvent(QContextMenuEvent *event);
};
class DustList:public MailList{
    Q_OBJECT
public:
    DustList(QWidget *parent = 0);
private slots:
    void openDust();
    void deleDust();
    void appendMail(MailData &md);
    void contextMenuEvent(QContextMenuEvent *event);
};


class Recving:public QDialog
{
    Q_OBJECT
public:
    Recving(list<MailData> &lmd, QWidget *parent = 0);
private:
    QVBoxLayout  *mainLyt;
    QTextBrowser *mTextBrowser;
    QProgressBar *mProgBar;
    MyPop *mPop;
    list<MailData> mlmd;
    int v;
    QTimer *timer;
signals:
    void sendlmd(list<MailData> &lmd);
    void send2Box(MailData &md);
private slots:
    void protest(string str);
    void startSend();
};

#endif // BOXLISTS_H

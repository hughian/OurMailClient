#ifndef BOXLISTS_H
#define BOXLISTS_H

#include "qt.h"
#include "MailList.h"
class RecvList:public MailList{
    Q_OBJECT
public:
    RecvList(QWidget *parent = 0);

public slots:
    void recvMail();
private slots:
    void openMail();
    void deleMail();
    void contextMenuEvent(QContextMenuEvent *event);
};
class SendList:public MailList{
    Q_OBJECT
public:
    SendList(QWidget *parent = 0);
public slots:
private slots:
    //void contextMenuEvent(QContextMenuEvent *event);
};

class DrftList:public MailList{
    Q_OBJECT
public:
    DrftList(QWidget *parent = 0);
private:
    int mRow;
public slots:
    void openDraft();
    void deleDraft();
    void replaceDraft(MailData &md);
private:
    void contextMenuEvent(QContextMenuEvent *event);
};
class DustList:public MailList{
    Q_OBJECT
public:
    DustList(QWidget *parent = 0);
private slots:
    //void contextMenuEvent(QContextMenuEvent *event);
};
#endif // BOXLISTS_H

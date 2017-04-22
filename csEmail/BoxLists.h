#ifndef BOXLISTS_H
#define BOXLISTS_H

#include "qt.h"
#include "MailList.h"
/*
 * 收件箱
 */
class RecvList:public MailList{
    Q_OBJECT
public:
    RecvList(QWidget *parent = 0);
public slots:
    void setRecv();
};
/*
 * 已发送
 */
class SendList:public MailList{
    Q_OBJECT
public:
    SendList(QWidget *parent = 0);
public slots:
    void setSend();
};
/*
 * 草稿箱
 */
class DrftList:public MailList{
    Q_OBJECT
public:
    DrftList(QWidget *parent = 0);
private:
    QAction *mDeleAll;
public slots:
    void setDraft();
    void openDraft();
    void deleDraft();
private:
    void contextMenuEvent(QContextMenuEvent *event);
};

/*
 * 垃圾箱
 */
class DustList:public MailList{
    Q_OBJECT
public:
    DustList(QWidget *parent = 0);
public slots:
    void setDust();
};
#endif // BOXLISTS_H

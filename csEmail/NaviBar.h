#ifndef NAVIBAR_H
#define NAVIBAR_H

#include "qt.h"

class ToolBtn:public QWidget{
    Q_OBJECT
public:
    ToolBtn(QString name,QString str,QWidget *parent = 0);
};

class NaviBar:public QWidget{
    Q_OBJECT
public:
    NaviBar(QWidget *parent = 0);
    NaviBar(int,QWidget *parent = 0);
    friend class QMainWin;
private:
    QToolButton *mWriteMail;
    QToolButton *mContacts;
    QToolButton *mRecvBox;
    QToolButton *mSendBox;
    QToolButton *mDraftBox;
    QToolButton *mDustBin;
    QToolButton *mSettings;
    QToolButton *mAbout;
};
#endif // NAVIBAR_H

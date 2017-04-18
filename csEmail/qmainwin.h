#ifndef QMAINWIN_H
#define QMAINWIN_H

#include "qt.h"
#include "uiclass.h"
class QMainWin : public QWidget
{
    Q_OBJECT
public:
    QMainWin(QWidget *parent = 0);
    ~QMainWin();
private:
    QLabel *mBoxLabel;
    QLayout *mainLyt;
    RecvList *mRecvTable;
    SendList *mSendTable;
    DrftList *mDrftTable;
    DustList *mDustTable;
    QStackedWidget *mStackWid;

private slots:
    void Write();
    void Recv();
    void Send();
    void Draft();
    void Dust();
    void Settings();
    void About();
    void setTitle(QString &mTitle);
};

#endif // QMAINWIN_H

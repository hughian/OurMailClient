#include "qmainwin.h"
#include "uiclass.h"
#include <QDebug>
QString mTitle("csEmail");
QMainWin::QMainWin(QWidget *parent)
    : QWidget(parent)
{
    QString str[8];
    mainLyt = new QHBoxLayout(this);
    //NavigationBar *pNaviBar = new NavigationBar(this);
    NaviBar *pNaviBar = new NaviBar(1,this);
    mainLyt -> addWidget(pNaviBar);

    MailList *recvTable = new MailList(RECV,this);
    MailList *sendTable = new MailList(SEND,this);
    MailList *drftTable = new MailList(DRAFT,this);
    MailList *dustTable = new MailList(DUST,this);
    //mainLyt -> addWidget(table);
    mStackWid = new QStackedWidget(this);
    mStackWid -> addWidget(recvTable);
    mStackWid -> addWidget(sendTable);
    mStackWid -> addWidget(drftTable);
    mStackWid -> addWidget(dustTable);
    mainLyt -> addWidget(mStackWid);

    connect(pNaviBar->mWriteMail,SIGNAL(clicked(bool)),this,SLOT(Write()));
    connect(pNaviBar->mRecvBox,SIGNAL(clicked(bool)),this,SLOT(Recv()));
    connect(pNaviBar->mSendBox,SIGNAL(clicked(bool)),this,SLOT(Send()));
    connect(pNaviBar->mDraftBox,SIGNAL(clicked(bool)),this,SLOT(Draft()));
    connect(pNaviBar->mDustBin,SIGNAL(clicked(bool)),this,SLOT(Dust()));
    connect(pNaviBar->mSettings,SIGNAL(clicked(bool)),this,SLOT(Settings()));
    connect(pNaviBar->mAbout,SIGNAL(clicked(bool)),this,SLOT(About()));

    readSetFile(this,str);
    setWindowIcon(QIcon(":/images/icons/csEmail.png"));
    setWindowTitle("csEmal - "+str[0]);
    resize(QSize(800,600));
}
void QMainWin::Write()
{
    WriteMailDlg Dlg;
    Dlg.exec();
}
void QMainWin::Recv()
{
    mStackWid -> setCurrentIndex(RECV);
}
void QMainWin::Send()
{
    mStackWid -> setCurrentIndex(SEND);
}
void QMainWin::Draft(){
    mStackWid -> setCurrentIndex(DRAFT);
}
void QMainWin::Dust(){
    mStackWid -> setCurrentIndex(DUST);
}
void QMainWin::Settings(){
    SettingsDlg Dlg;
    connect(&Dlg,SIGNAL(send(QString &)),this,SLOT(setTitle(QString &)));
    Dlg.exec();
}
void QMainWin::setTitle(QString &mTitle)
{
    setWindowTitle(mTitle);
}
void QMainWin::About(){
    AboutDlg Dlg;
    Dlg.exec();
}

QMainWin::~QMainWin()
{

}



#include "QMainWin.h"
#include "WriteMailDlg.h"
#include "Settings.h"
#include "AboutDlg.h"
QString setData[9];
QMainWin::QMainWin(QWidget *parent)
    : QWidget(parent)
{
    mBoxLabel  = new QLabel(QStringLiteral("收件箱"));
    mainLyt    = new QGridLayout(this);
    mNaviBar   = new NaviBar(this);
    mRecvTable = new RecvList(this);
    mSendTable = new SendList(this);
    mDrftTable = new DrftList(this);
    mDustTable = new DustList(this);
    mStackWid  = new QStackedWidget(this);

    mStackWid -> addWidget(mRecvTable);
    mStackWid -> addWidget(mSendTable);
    mStackWid -> addWidget(mDrftTable);
    mStackWid -> addWidget(mDustTable);

    mainLyt -> addWidget(mNaviBar,0,0,2,1);
    mainLyt -> addWidget(mBoxLabel,0,1,1,1,Qt::AlignCenter);
    mainLyt -> addWidget(mStackWid,1,1,1,1);

    connect(mNaviBar->mWriteMail,SIGNAL(clicked(bool)),this,SLOT(Write()));
    connect(mNaviBar->mRecvBox  ,SIGNAL(clicked(bool)),this,SLOT(Recv()));
    connect(mNaviBar->mSendBox  ,SIGNAL(clicked(bool)),this,SLOT(Send()));
    connect(mNaviBar->mDraftBox ,SIGNAL(clicked(bool)),this,SLOT(Draft()));
    connect(mNaviBar->mDustBin  ,SIGNAL(clicked(bool)),this,SLOT(Dust()));
    connect(mNaviBar->mSettings ,SIGNAL(clicked(bool)),this,SLOT(Settings()));
    connect(mNaviBar->mAbout	,SIGNAL(clicked(bool)),this,SLOT(About()));

    readSetFile(this,setData);
    QFont font = mBoxLabel -> font();
    font.setBold(true);
    mBoxLabel -> setFont(font);
    setWindowIcon(QIcon(":/images/icons/csEmail.png"));
    setWindowTitle("csEmal - "+setData[0]);
    resize(QSize(800,600));
}
void QMainWin::Write()
{
    WriteMailDlg *Dlg = new WriteMailDlg();
    Dlg -> exec();
    delete Dlg;
}
void QMainWin::Recv()
{
    mStackWid  -> setCurrentIndex(RECV);
    mRecvTable -> recvMail();
    mRecvTable -> setBox();  ///here are some questions needed to be dealt with
    mBoxLabel  -> setText(QStringLiteral("收件箱"));
}
void QMainWin::Send()
{
    mStackWid  -> setCurrentIndex(SEND);
    mSendTable -> setBox();
    mBoxLabel  -> setText(QStringLiteral("已发送"));
}
void QMainWin::Draft(){
    mStackWid  -> setCurrentIndex(DRAFT);
    mDrftTable -> setBox();
    mBoxLabel  -> setText(QStringLiteral("草稿箱"));
}
void QMainWin::Dust(){
    mStackWid  -> setCurrentIndex(DUST);
    mDustTable -> setBox();
    mBoxLabel  -> setText(QStringLiteral("垃圾箱"));
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



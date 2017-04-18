#include "qmainwin.h"
#include <QDebug>
QString setData[8];
QMainWin::QMainWin(QWidget *parent)
    : QWidget(parent)
{
    mBoxLabel = new QLabel(QStringLiteral("收件箱"));
    QFont font = mBoxLabel -> font();
    font.setBold(true);
    mBoxLabel -> setFont(font);
    QVBoxLayout *labelLyt = new QVBoxLayout();
    QHBoxLayout *lLyt     = new QHBoxLayout();
    mainLyt = new QHBoxLayout(this);

    //NavigationBar *pNaviBar = new NavigationBar(this);
    NaviBar *pNaviBar = new NaviBar(1,this);
    mainLyt -> addWidget(pNaviBar);

    mRecvTable = new RecvList(this);
    mSendTable = new SendList(this);
    mDrftTable = new DrftList(this);
    mDustTable = new DustList(this);
    //mainLyt -> addWidget(table);
    mStackWid = new QStackedWidget(this);
    mStackWid -> addWidget(mRecvTable);
    mStackWid -> addWidget(mSendTable);
    mStackWid -> addWidget(mDrftTable);
    mStackWid -> addWidget(mDustTable);
    lLyt -> addStretch(1);
    lLyt -> addWidget(mBoxLabel);
    lLyt -> addStretch(1);
    labelLyt -> addLayout(lLyt);
    labelLyt -> addWidget(mStackWid);
    QFrame *frame = new QFrame();
    frame -> setLayout(labelLyt);
    mainLyt -> addWidget(frame);

    connect(pNaviBar->mWriteMail,SIGNAL(clicked(bool)),this,SLOT(Write()));
    connect(pNaviBar->mRecvBox  ,SIGNAL(clicked(bool)),this,SLOT(Recv()));
    connect(pNaviBar->mSendBox  ,SIGNAL(clicked(bool)),this,SLOT(Send()));
    connect(pNaviBar->mDraftBox ,SIGNAL(clicked(bool)),this,SLOT(Draft()));
    connect(pNaviBar->mDustBin  ,SIGNAL(clicked(bool)),this,SLOT(Dust()));
    connect(pNaviBar->mSettings ,SIGNAL(clicked(bool)),this,SLOT(Settings()));
    connect(pNaviBar->mAbout	,SIGNAL(clicked(bool)),this,SLOT(About()));

    readSetFile(this,setData);
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
    mRecvTable -> setRecv();
    mBoxLabel  -> setText(QStringLiteral("收件箱"));
}
void QMainWin::Send()
{
    mStackWid  -> setCurrentIndex(SEND);
    mSendTable -> setSend();
    mBoxLabel  -> setText(QStringLiteral("已发送"));
}
void QMainWin::Draft(){
    mStackWid  -> setCurrentIndex(DRAFT);
    mDrftTable -> setDraft();
    mBoxLabel  -> setText(QStringLiteral("草稿箱"));
}
void QMainWin::Dust(){
    mStackWid  -> setCurrentIndex(DUST);
    mDustTable -> setDust();
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



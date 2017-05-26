#include "SendingDlg.h"
#include <QTimer>
#include <QCoreApplication>
extern QString setData[8];
SendingDlg::SendingDlg(MailData md,QWidget *parent):mMD(md),QDialog(parent)
{
    mTextBrowser = new QTextBrowser(this);
    mProgBar  = new QProgressBar(this);
    mainLyt   = new QVBoxLayout(this);
    mProgBar -> setRange(0,32);
    mProgBar -> setValue(2);
    mProgBar -> setTextVisible(false);
    mTextBrowser -> setReadOnly(true);
    mSmtp = new MySmtp(setData[sendSer].toStdString(),setData[sendPort].toInt(),setData[Account].toStdString(),setData[password].toStdString());
    mainLyt -> addWidget(mProgBar);
    mainLyt -> addWidget(mTextBrowser);
    timer = new QTimer(this);
    v = 2;
    connect(timer,SIGNAL(timeout()),this,SLOT(startSend()));
    connect(mSmtp,SIGNAL(sendStr(string)),this,SLOT(protest(string)));
    timer -> start(1000);
    setWindowIcon(QIcon(":/images/icons/send.png"));
    setWindowTitle(QStringLiteral("发送"));
    setWindowFlags(Qt::WindowCloseButtonHint);
    this -> resize(QSize(300,180));
}
void SendingDlg::startSend()
{
    timer -> stop();
    qDebug()<<"startSend";
    if( !mSmtp->Connect() || !mSmtp->ConfirmUser() || !mSmtp->SendMail(mMD))
    {
        mProgBar -> setStyleSheet("QProgressBar::chunk { background-color:red;}");
        QMessageBox::warning(this,QStringLiteral("发送邮件"),QStringLiteral("邮件发送失败"),QMessageBox::NoButton);
        reject();
        qDebug()<<"failSend";
    }
    else{
        mProgBar -> setValue(32);
        QMessageBox::information(this,QStringLiteral("发送邮件"),QStringLiteral("邮件发送成功"),QMessageBox::NoButton);
        accept();
        send2Box(mMD); //已经发送的右键存入草稿箱
        qDebug()<<"finishSend";
    }

}
void sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
void SendingDlg::protest(string str)
{
    qDebug()<<"protest call.";
    qDebug()<<(QString::fromUtf8(str.c_str()));
    qDebug()<<v;
    sleep(100);
    v++;
    mTextBrowser -> append(QString::fromLocal8Bit(str.c_str()));
    mProgBar -> setValue(v);
}

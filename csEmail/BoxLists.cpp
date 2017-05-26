#include "BoxLists.h"
#include "WriteMailDlg.h"
#include "MyPop.h"
#include "OpenMailDlg.h"
#include <list>
#include <QTextCodec>
extern QString setData[8];
/*
 *RecvList
 */
RecvList::RecvList(QWidget *parent):MailList(parent)
{
    QStringList header;
    header<<QStringLiteral("")<<QStringLiteral("发件人")<<QStringLiteral("主题")<<QStringLiteral("时间");
    mTable -> setHorizontalHeaderLabels(header);
    mDeleAll -> setText(QStringLiteral("清空收件箱"));
    mType  = RECV;
    mFileName = QString("recv.txt");
    mReply = new QAction();
    mTranSf = new QAction();
    connect(mOpen   ,SIGNAL(triggered(bool)),this,SLOT(openMail()));
    connect(mDelete ,SIGNAL(triggered(bool)),this,SLOT(deleMail()));
    connect(mDeleAll,SIGNAL(triggered(bool)),this,SLOT(clearBox()));
    connect(mTable,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(openMail()));
    this -> setBox();
}

void RecvList::recvMail()
{
    list<MailData> lmd;
//    MyPop pop(setData[recvSer].toStdString(),setData[recvPort].toInt(),setData[Account].toStdString(),setData[password].toStdString());
//    pop.Connect();
//    pop.ConfirmUser();
//    pop.GetAllMails(lmd,setData[deleteOp].toInt());
    Recving *Dlg = new Recving(lmd);
    connect(Dlg,SIGNAL(sendlmd(list<MailData>&)),this,SLOT(getlmd(list<MailData>&)));
    Dlg->exec();
//    mdl= QList<MailData>::fromStdList(lmd);
//    //printmdl(mdl);
//    if(mdl.size() == 0)
//        return;
//    this -> fillTable();
//    writeBoxFile(mFileName,mdl);
}
void RecvList::getlmd(list<MailData> &lmd)
{
    mdl= QList<MailData>::fromStdList(lmd);
    if(mdl.size() == 0)
        return;
    this -> fillTable();
    writeBoxFile(mFileName,mdl);

}
void RecvList::openMail()
{
    MyPop pop(setData[recvSer].toStdString(),setData[recvPort].toInt(),setData[Account].toStdString(),setData[password].toStdString());
    if(!pop.Connect())
    {
        QMessageBox::warning(this,QStringLiteral("连接故障"),QStringLiteral("请检查网络连接"),QMessageBox::Ok);
        return ;
    }
    int mRow = mTable -> currentRow();
    MailData md = mdl.at(mRow);
    OpenMailDlg dlg(md);
    dlg.exec();
}
void RecvList::deleMail()
{
//    int ret = QMessageBox::warning(this,QStringLiteral("删除"),QStringLiteral("是否同时删除邮件？"),QMessageBox::Yes|QMessageBox::No);
//    if(ret == QMessageBox::Yes)
//        qDebug()<<"删除邮件";
    int ret = QMessageBox::warning(this,QStringLiteral("删除"),QStringLiteral("确认删除邮件"),QMessageBox::Yes|QMessageBox::No);
    if(ret == QMessageBox::No)
        return;
    qDebug()<<"删除邮件";
    int mRow = mTable -> currentRow();
    MailData md = mdl.at(mRow);
    mdl.removeAt(mRow);
    send2Dust(md);
    fillTable();
    writeBoxFile(mFileName,mdl);
}
void RecvList::contextMenuEvent(QContextMenuEvent *event)
{
    mPopMenu -> resize(QSize(200,180));
    //由于QTableWidget被放入别的QWidget后，使用mTable -> mapFromGlobal(QCursor::pos())的办法无法捕捉最后一行item的右键信息
    //所以使用mTable -> viewport() 返回当前坐标的QWidget然后再mapFromGlobal()获取item信息。
    QPoint point = mTable -> viewport() -> mapFromGlobal(QCursor::pos());
    QTableWidgetItem *item = mTable -> itemAt(point);
    if(item != NULL){
        mPopMenu -> addAction(mOpen);
        mPopMenu -> addAction(mDelete);
        mPopMenu -> addAction(mDeleAll);

        mPopMenu -> exec(QCursor::pos());
        event -> accept();
    }
}

/*
 *SendList
 */
SendList::SendList(QWidget *parent):MailList(parent)
{
    QStringList header;
    header<<QStringLiteral("")<<QStringLiteral("收件人")<<QStringLiteral("主题")<<QStringLiteral("时间");
    mTable -> setHorizontalHeaderLabels(header);
    mDeleAll -> setText(QStringLiteral("清空发件箱"));
    mType = SEND;
    mFileName = QString("send.txt");
    connect(mOpen   ,SIGNAL(triggered(bool)),this,SLOT(openMail()));
    connect(mDelete ,SIGNAL(triggered(bool)),this,SLOT(deleMail()));
    connect(mDeleAll,SIGNAL(triggered(bool)),this,SLOT(clearBox()));
    connect(mTable  ,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(openMail()));
    this -> setBox();
}
void SendList::appendMD(MailData &md)
{
    mdl<<md;
    fillTable();
    appendBoxFile(mFileName,md);
}
void SendList::openMail()
{
    int mRow = mTable -> currentRow();
    MailData md = mdl.at(mRow);
    OpenMailDlg dlg(md);
    dlg.exec();
}
void SendList::deleMail()
{
    int mRow = mTable -> currentRow();
    mdl.removeAt(mRow);
    fillTable();
    writeBoxFile(mFileName,mdl);
}

void SendList::contextMenuEvent(QContextMenuEvent *event)
{
    mPopMenu -> resize(QSize(200,180));
    //由于QTableWidget被放入别的QWidget后，使用mTable -> mapFromGlobal(QCursor::pos())的办法无法捕捉最后一行item的右键信息
    //所以使用mTable -> viewport() 返回当前坐标的QWidget然后再mapFromGlobal()获取item信息。
    QPoint point = mTable -> viewport() -> mapFromGlobal(QCursor::pos());
    QTableWidgetItem *item = mTable -> itemAt(point);
    if(item != NULL){
        mPopMenu -> addAction(mOpen);
        mPopMenu -> addAction(mDelete);
        mPopMenu -> addAction(mDeleAll);

        mPopMenu -> exec(QCursor::pos());
        event -> accept();
    }
}
/*
 *DrftList
 */
DrftList::DrftList(QWidget *parent):MailList(parent)
{
    QStringList header;
    header<<QStringLiteral("")<<QStringLiteral("收件人")<<QStringLiteral("主题")<<QStringLiteral("时间");
    mTable -> setHorizontalHeaderLabels(header);
    mDeleAll -> setText(QStringLiteral("清空草稿箱"));
    mType = DRAFT;
    mFileName = QString("draft.txt");
    connect(mOpen  ,SIGNAL(triggered(bool)),this,SLOT(openDraft()));
    connect(mDelete,SIGNAL(triggered(bool)),this,SLOT(deleDraft()));
    connect(mDeleAll,SIGNAL(triggered(bool)),this,SLOT(clearBox()));
    connect(mTable,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(openDraft()));
    this -> setBox();
}
void DrftList::openDraft()
{
    qDebug()<<"open Draft";
    mRow = mTable -> currentRow();
    MailData md = mdl.at(mRow);
    WriteMailDlg *Dlg = new WriteMailDlg();
    connect(Dlg,SIGNAL(send2Draft(MailData&)),this,SLOT(replaceDraft(MailData&)));
    connect(Dlg,SIGNAL(send2Send(MailData&)),this,SLOT(draft2Send(MailData&)));
    qDebug()<<"contents.size():"<<md.contents.size();
    Dlg -> openDraft(md);
    Dlg -> exec();
    delete Dlg;
}
void DrftList::draft2Send(MailData &md)
{
    MDToSend(md);
}
void DrftList::replaceDraft(MailData &md)
{
    mdl.replace(mRow,md);
    writeBoxFile(mFileName,mdl);
    this -> setBox();
}
void DrftList::deleDraft()
{
    int row = mTable -> currentRow();
    mdl.removeAt(row);
    this -> fillTable();
    writeBoxFile(mFileName,mdl);
}

void DrftList::contextMenuEvent(QContextMenuEvent *event)
{
    mPopMenu -> resize(QSize(200,180));
    //由于QTableWidget被放入别的QWidget后，使用mTable -> mapFromGlobal(QCursor::pos())的办法无法捕捉最后一行item的右键信息
    //所以使用mTable -> viewport() 返回当前坐标的QWidget然后再mapFromGlobal()获取item信息。
    QPoint point = mTable -> viewport() -> mapFromGlobal(QCursor::pos());
    QTableWidgetItem *item = mTable -> itemAt(point);
    if(item != NULL){
        mPopMenu -> addAction(mOpen);
        mPopMenu -> addAction(mDelete);
        mPopMenu -> addAction(mDeleAll);

        mPopMenu -> exec(QCursor::pos());
        event -> accept();
    }
}

/*
 *DustList
 */
DustList::DustList(QWidget *parent):MailList(parent)
{
    QStringList header;
    header<<QStringLiteral("")<<QStringLiteral("收件人")<<QStringLiteral("主题")<<QStringLiteral("时间");
    mTable -> setHorizontalHeaderLabels(header);
    mType = DUST;
    mFileName = QString("dust.txt");
    mDeleAll -> setText(QStringLiteral("清空垃圾箱"));
    connect(mOpen  ,SIGNAL(triggered(bool)),this,SLOT(openDust()));
    connect(mDelete,SIGNAL(triggered(bool)),this,SLOT(deleDust()));
    connect(mDeleAll,SIGNAL(triggered(bool)),this,SLOT(clearBox()));
    connect(mTable,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(openDust()));
    this -> setBox();
    this -> setBox();
}
void DustList::appendMail(MailData &md)
{
    mdl<<md;
    fillTable();
    appendBoxFile(mFileName,md);
}

void DustList::openDust()
{
    int mRow = mTable -> currentRow();
    MailData md = mdl.at(mRow);
    OpenMailDlg dlg(md);
    dlg.exec();
}
void DustList::deleDust()
{
    int mRow = mTable -> currentRow();
    mdl.removeAt(mRow);
    fillTable();
    writeBoxFile(mFileName,mdl);
}

void DustList::contextMenuEvent(QContextMenuEvent *event)
{
    mPopMenu -> resize(QSize(200,180));
    //由于QTableWidget被放入别的QWidget后，使用mTable -> mapFromGlobal(QCursor::pos())的办法无法捕捉最后一行item的右键信息
    //所以使用mTable -> viewport() 返回当前坐标的QWidget然后再mapFromGlobal()获取item信息。
    QPoint point = mTable -> viewport() -> mapFromGlobal(QCursor::pos());
    QTableWidgetItem *item = mTable -> itemAt(point);
    if(item != NULL){
        mPopMenu -> addAction(mOpen);
        mPopMenu -> addAction(mDelete);
        mPopMenu -> addAction(mDeleAll);

        mPopMenu -> exec(QCursor::pos());
        event -> accept();
    }
}



Recving::Recving(list<MailData> &lmd, QWidget *parent):mlmd(lmd),QDialog(parent)
{
    mTextBrowser = new QTextBrowser(this);
    mProgBar  = new QProgressBar(this);
    mainLyt   = new QVBoxLayout(this);
    mProgBar -> setRange(0,32);
    mProgBar -> setValue(2);
    mProgBar -> setTextVisible(false);
    mTextBrowser -> setReadOnly(true);
    mPop = new MyPop(setData[recvSer].toStdString(),setData[recvPort].toInt(),setData[Account].toStdString(),setData[password].toStdString());
    mainLyt -> addWidget(mProgBar);
    mainLyt -> addWidget(mTextBrowser);
    timer = new QTimer(this);
    v = 2;
    connect(timer,SIGNAL(timeout()),this,SLOT(startSend()));
    connect(mPop,SIGNAL(sendStr(string)),this,SLOT(protest(string)));
    timer -> start(1000);
    setWindowIcon(QIcon(":/images/icons/send.png"));
    setWindowTitle(QStringLiteral("接收"));
    setWindowFlags(Qt::WindowCloseButtonHint);
    this -> resize(QSize(300,180));
}
void Recving::startSend()
{
    timer -> stop();
    qDebug()<<"startSend";
    if( !mPop->Connect() || !mPop->ConfirmUser() || !mPop->GetAllMails(mlmd,setData[8].toInt()))
    {
        mProgBar -> setStyleSheet("QProgressBar::chunk { background-color:red;}");
        QMessageBox::warning(this,QStringLiteral("发送邮件"),QStringLiteral("邮件发送失败"),QMessageBox::NoButton);
        reject();
        qDebug()<<"failSend";
    }
    else{
        sendlmd(mlmd);
        mProgBar -> setValue(32);
        QMessageBox::information(this,QStringLiteral("发送邮件"),QStringLiteral("邮件发送成功"),QMessageBox::NoButton);
        accept();
        qDebug()<<"finishSend";
    }

}
void Recving::protest(string str)
{
    qDebug()<<"protest call.";
    qDebug()<<(QString::fromUtf8(str.c_str()));
    qDebug()<<v;
    v++;
    mTextBrowser -> append(QString::fromLocal8Bit(str.c_str()));
    mProgBar -> setValue(v);
}

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
    connect(mOpen   ,SIGNAL(triggered(bool)),this,SLOT(openMail()));
    connect(mDelete ,SIGNAL(triggered(bool)),this,SLOT(deleMail()));
    connect(mDeleAll,SIGNAL(triggered(bool)),this,SLOT(clearBox()));
    connect(mTable,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(openMail()));
    this -> setBox();
}

void RecvList::recvMail()
{
    list<MailData> lmd;
    MyPop pop(setData[recvSer].toStdString(),setData[recvPort].toInt(),setData[Account].toStdString(),setData[password].toStdString());
    pop.Connect();
    pop.ConfirmUser();
    pop.GetAllMails(lmd,setData[deleteOp].toInt());
    //pop.GetMailContent()
    qDebug()<<lmd.size();
    QString str;
    for(list<MailData>::iterator it = lmd.begin();it != lmd.end();it++)
    {


        qDebug("%s*************************\n*****************************%s",it->time.c_str(),it->subject.c_str());
        str = QString::fromLocal8Bit(it->subject.c_str());
        qDebug()<<str;
    }
    qDebug()<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$";
    mdl= QList<MailData>::fromStdList(lmd);
    foreach (MailData md, mdl) {
        qDebug()<<QString::fromLocal8Bit(md.subject.c_str());
    }
    //printmdl(mdl);
    qDebug()<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$";
    this -> fillTable();
    writeBoxFile("recv.txt",mdl);
    foreach (MailData md, mdl) {
        qDebug()<<QString::fromLocal8Bit(md.subject.c_str());
    }
    //printmdl(mdl);

    qDebug()<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$";
    //openMail();
}

void RecvList::openMail()
{
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("gbk"));
    qDebug()<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$";
    foreach (MailData md, mdl) {
        qDebug()<<QString::fromLocal8Bit(md.subject.c_str());
    }
    qDebug()<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$";
    int mRow = mTable -> currentRow();
    MailData md = mdl.at(mRow);
    qDebug()<< QString::fromLocal8Bit(md.subject.c_str());
    qDebug()<<"wwwwwwwwwwwwwwwwwwwwwwww:"<<QString::fromStdString(md.subject);
    OpenMailDlg dlg(md);
    dlg.exec();
}
void RecvList::deleMail()
{

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
    mType = SEND;
    mFileName = QString("send.txt");
    this -> setBox();
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
    connect(Dlg,SIGNAL(send(MailData&)),this,SLOT(replaceDraft(MailData&)));
    qDebug()<<"contents.size():"<<md.contents.size();
    Dlg -> openDraft(md);
    Dlg -> exec();
    delete Dlg;
}
void DrftList::replaceDraft(MailData &md)
{
    mdl.replace(mRow,md);
    writeBoxFile("draft.txt",mdl);
    this -> setBox();
}
void DrftList::deleDraft()
{
    int row = mTable -> currentRow();
    mdl.removeAt(row);
    this -> fillTable();
    writeBoxFile("draft.txt",mdl);
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
    this -> setBox();
}

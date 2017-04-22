#include "BoxLists.h"
#include "WriteMailDlg.h"
RecvList::RecvList(QWidget *parent):MailList(parent)
{
    QStringList header;
    header<<QStringLiteral("")<<QStringLiteral("发件人")<<QStringLiteral("主题")<<QStringLiteral("时间");
    mTable -> setHorizontalHeaderLabels(header);
    this -> setRecv();
}

void RecvList::setRecv()
{
    this -> setBox(QString("recv.txt"));
}

SendList::SendList(QWidget *parent):MailList(parent)
{
    QStringList header;
    header<<QStringLiteral("")<<QStringLiteral("收件人")<<QStringLiteral("主题")<<QStringLiteral("时间");
    mTable -> setHorizontalHeaderLabels(header);
    this -> setSend();
}

void SendList::setSend()
{
    this -> setBox(QString("send.txt"));
}

//#######################
DrftList::DrftList(QWidget *parent):MailList(parent)
{
    QStringList header;
    header<<QStringLiteral("")<<QStringLiteral("收件人")<<QStringLiteral("主题")<<QStringLiteral("时间");
    mTable -> setHorizontalHeaderLabels(header);
    mDeleAll = new QAction(QStringLiteral("清空草稿箱"));
    this -> setDraft();
    connect(mOpen  ,SIGNAL(triggered(bool)),this,SLOT(openDraft()));
    connect(mDelete,SIGNAL(triggered(bool)),this,SLOT(deleDraft()));
    connect(mTable,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(openDraft()));
}
void DrftList::setDraft()
{
    this -> setBox(QString("draft.txt"));
}
void DrftList::openDraft()
{
    qDebug()<<"open Draft";
    int row = mTable -> currentRow();
    QStringList qsl = mQqsl.at(row);
    WriteMailDlg *Dlg = new WriteMailDlg();
    Dlg -> openDraft(qsl);
    Dlg -> exec();
    delete Dlg;
    //this -> deleDraft();
}
void DrftList::deleDraft()
{
    int row = mTable -> currentRow();
    mQqsl.removeAt(row);
    mTable -> clearContents();
    QStringList qsl;
    row = 0;
    for(QList<QStringList>::iterator it = mQqsl.begin();it != mQqsl.end();it++)
    {
        qsl = *it;
        mTable -> setRowCount(row+1);
        mTable -> setItem(row,1,new QTableWidgetItem(qsl.at(1)));
        mTable -> setItem(row,2,new QTableWidgetItem(qsl.at(3)));
        mTable -> setItem(row++,3,new QTableWidgetItem(qsl.at(5)));
    }
    writeBoxFile("draft.txt",mQqsl);
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

//###########################
DustList::DustList(QWidget *parent):MailList(parent)
{
    QStringList header;
    header<<QStringLiteral("")<<QStringLiteral("收件人")<<QStringLiteral("主题")<<QStringLiteral("时间");
    mTable -> setHorizontalHeaderLabels(header);
    this -> setDust();
}
void DustList::setDust()
{

}

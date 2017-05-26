#include "MailList.h"
#include <QHeaderView>
#include "qt.h"
MailList::MailList(QWidget *parent):QWidget(parent)
{
    mTable = new QTableWidget(this);
    mTable -> setColumnCount(4);
    mTable -> horizontalHeader() -> setDefaultSectionSize(150);
    mTable -> horizontalHeader() -> setSectionsMovable(false);
    mTable -> horizontalHeader() -> setSectionResizeMode(QHeaderView::Fixed);
    mTable -> horizontalHeader() -> resizeSection(0,30);
    mTable -> horizontalHeader() -> resizeSection(1,180);
    mTable -> horizontalHeader() -> resizeSection(2,180);
    mTable -> horizontalHeader() -> setDefaultAlignment(Qt::AlignCenter);
    mTable -> horizontalHeader() -> setSectionsClickable(false); //setClickable(bool) is obsoleted;
    mTable -> horizontalHeader() -> setStretchLastSection(true);
    mTable -> horizontalHeader() -> setHighlightSections(false);

    QFont font = mTable -> horizontalHeader() -> font();
    font.setBold(true);
    mTable -> horizontalHeader() -> setFont(font);
    mTable -> setShowGrid(false);
    //mTable -> setStyleSheet("selection-background-color:lightblue");
    QPalette pal;
    pal.setColor(QPalette::Base,QColor(242,242,242));
    pal.setColor(QPalette::AlternateBase,QColor(222,222,222));
    mTable -> setPalette(pal);
    mTable -> setAlternatingRowColors(true);
    mTable -> verticalHeader() -> setVisible(false);
    mTable -> setEditTriggers(QAbstractItemView::NoEditTriggers);
    mTable -> setSelectionBehavior(QAbstractItemView::SelectRows);
    mTable -> setSelectionMode(QAbstractItemView::SingleSelection);
    mTable -> setTabKeyNavigation(true);
    mTable -> setItemDelegate(new NoFocusDelegate());
    QTableWidgetItem *item = new QTableWidgetItem();
    item -> setIcon(QIcon(":/images/icons/unopen.png"));
    item -> setSizeHint(QSize(12,12));
    mTable -> setHorizontalHeaderItem(0,item);
    QVBoxLayout *mainLyt = new QVBoxLayout(this);
    mainLyt -> addWidget(mTable);
    this->initActions();
}
//void MailList::contextMenuEvent(QContextMenuEvent *event)
//{
//    mPopMenu -> resize(QSize(200,180));
//    //由于QTableWidget被放入别的QWidget后，使用mTable -> mapFromGlobal(QCursor::pos())的办法无法捕捉最后一行item的右键信息
//    //所以使用mTable -> viewport() 返回当前坐标的QWidget然后再mapFromGlobal()获取item信息。
//    QPoint point = mTable -> viewport() -> mapFromGlobal(QCursor::pos());
//    qDebug()<<mTable -> currentRow()<< point;
//    QTableWidgetItem *item = mTable -> itemAt(point);
//    qDebug()<<item;
//    if(item != NULL){
//        qDebug()<<"test";
//        mPopMenu -> addAction(mOpen);
//        mPopMenu -> addAction(mDelete);

//        mPopMenu -> exec(QCursor::pos());
//        event -> accept();
//    }

//}
void MailList::fillTable()
{
    QString str;
    MailData md;
    mTable -> clearContents();
    int row = 0;
    for(QList<MailData>::iterator it = mdl.begin();it != mdl.end();it++)
    {
        md = *it;
        mTable -> setRowCount(row+1);
        if(mType == RECV || mType == DUST)
            mTable -> setItem(row,1,new QTableWidgetItem(str.fromLocal8Bit(md.srcAddr.c_str())));
        else
            mTable -> setItem(row,1,new QTableWidgetItem(dstr2QString(md.dstAddr,false)));
        //
        mTable -> setItem(row,2,new QTableWidgetItem(str.fromLocal8Bit(md.subject.c_str())));
        mTable -> setItem(row++,3,new QTableWidgetItem(str.fromLocal8Bit(md.time.c_str())));
    }
}

void MailList::clearBox()
{
    int ret = QMessageBox::warning(this,QStringLiteral("清空"),QStringLiteral("确认删除所有？"),QMessageBox::Yes|QMessageBox::No);
    if(ret == QMessageBox::Yes)
    {
        mTable -> clearContents();
        mTable -> setRowCount(0);
        mdl.clear();
        writeBoxFile(mFileName,mdl);
    }
}

void MailList::mdl_del(int index)
{
    mdl.removeAt(index);
}
void MailList::mdl_insert(MailData &md)
{
    mdl.push_back(md);
}
void MailList::mdl_replace(int index, MailData &md)
{
    mdl.removeAt(index);
    //mdl.push_back(md);
    mdl.insert(index,md);
}
void MailList::setBox()
{
    readBoxFile(mFileName,mdl);
    fillTable();
    qDebug()<<"setBox"<<mFileName;
}
void MailList::initActions()
{
    mPopMenu = new QMenu(this);
    mOpen    = new QAction(QStringLiteral("打开"),this);
    mDelete  = new QAction(QStringLiteral("删除"),this);
    mDeleAll = new QAction(QStringLiteral("清空"));
}

void NoFocusDelegate::paint(QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex &index) const
{
    QStyleOptionViewItem itemOption(option);
    if (itemOption.state & QStyle::State_HasFocus)
        itemOption.state = itemOption.state ^ QStyle::State_HasFocus;
    QStyledItemDelegate::paint(painter, itemOption, index);
}

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
    this->initActions();
    QVBoxLayout *mainLyt = new QVBoxLayout(this);
    mainLyt -> addWidget(mTable);
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
void MailList::setBox(QString &filename)
{
    readBoxFile(filename,mQqsl);
    qDebug()<<mQqsl;
    int row = 0;
    QStringList qsl;
    mTable -> clearContents();
    for(QList<QStringList>::iterator it = mQqsl.begin();it != mQqsl.end();it++)
    {
        qsl = *it;
        mTable -> setRowCount(row+1);
        mTable -> setItem(row,1,new QTableWidgetItem(qsl.at(1)));
        mTable -> setItem(row,2,new QTableWidgetItem(qsl.at(3)));
        mTable -> setItem(row++,3,new QTableWidgetItem(qsl.at(5)));
    }
    qDebug()<<"setBox"<<filename;
}
void MailList::initActions()
{
    mPopMenu = new QMenu(this);
    mOpen    = new QAction(QStringLiteral("打开"),this);
    mDelete  = new QAction(QStringLiteral("删除"),this);
}

void NoFocusDelegate::paint(QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex &index) const
{
    QStyleOptionViewItem itemOption(option);
    if (itemOption.state & QStyle::State_HasFocus)
        itemOption.state = itemOption.state ^ QStyle::State_HasFocus;
    QStyledItemDelegate::paint(painter, itemOption, index);
}

#ifndef MAILLIST_H
#define MAILLIST_H
#include "qt"
#include "structdef.h"
#include <QStyledItemDelegate>
#include <QTableWidget>
class MailList:public QWidget{
    Q_OBJECT
public:
    MailList(QWidget *parent = 0);
    void setBox();
protected:
    QTableWidget *mTable;
    QList<MailData> mdl;
    QMenu   *mPopMenu;
    QAction *mDelete;
    QAction *mDeleAll;
    QAction *mOpen;
    QString mFileName;
    int  mType;//enum {RECV,SEND,DRAFT,DUST};
    void fillTable();
    void mdl_del(int index);
    void mdl_insert(MailData &md);
    void mdl_replace(int index,MailData &md);
protected slots:
    void clearBox();
private:
    void initActions();
    //void contextMenuEvent(QContextMenuEvent *event);
};



class NoFocusDelegate : public QStyledItemDelegate
{
protected:
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
};

#endif // MAILLIST_H

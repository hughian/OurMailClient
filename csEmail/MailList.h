#ifndef MAILLIST_H
#define MAILLIST_H
#include "qt"
#include <QStyledItemDelegate>
#include <QTableWidget>
class MailList:public QWidget{
    Q_OBJECT
public:
    MailList(QWidget *parent = 0);
protected:
    QTableWidget *mTable;
    QMenu *mPopMenu;
    QAction *mDelete;
    QAction *mOpen;
    QList<QStringList> mQqsl;
    void setBox(QString &filename);
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

#ifndef AUTOLINEEDIT_H
#define AUTOLINEEDIT_H
#include "qt.h"
#include <QListView>
#include <QStringListModel>
class AutoLineEdit : public QLineEdit
{
    Q_OBJECT
public:
//    AutoLineEdit(QWidget *parent = 0);
    AutoLineEdit(QStringList &words, QWidget *parent = 0);
public slots:
    void setCompleter(const QString &text);      // 动态的显示完成列表
    void completeText(const QModelIndex &index); // 点击完成列表中的项，使用此项自动完成输入的单词

protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);

private:
    QStringList mWords;       // 整个完成列表的单词
    QListView *mListView;     // 完成列表
    QStringListModel *model; // 完成列表的model
};

#endif // AUTOLINEEDIT_H

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
    void setCompleter(const QString &text);      // ��̬����ʾ����б�
    void completeText(const QModelIndex &index); // �������б��е��ʹ�ô����Զ��������ĵ���

protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);

private:
    QStringList mWords;       // ��������б�ĵ���
    QListView *mListView;     // ����б�
    QStringListModel *model; // ����б��model
};

#endif // AUTOLINEEDIT_H

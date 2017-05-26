#include "AutoLineEdit.h"
#include <QKeyEvent>

//AutoLineEdit::AutoLineEdit(QWidget *parent):QLineEdit(parent)
//{

//}
AutoLineEdit::AutoLineEdit(QStringList &words, QWidget *parent)
    : QLineEdit(parent), mWords(words)
{
    mListView = new QListView(this);
    model     = new QStringListModel(this);
    mListView->setWindowFlags(Qt::ToolTip);

    connect(this, SIGNAL(textChanged(const QString &)), this, SLOT(setCompleter(const QString &)));
    connect(mListView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(completeText(const QModelIndex &)));
}

void AutoLineEdit::focusOutEvent(QFocusEvent *event)
{
    //listView->hide();
    event -> accept();
}

void AutoLineEdit::keyPressEvent(QKeyEvent *event) {
    if (!mListView->isHidden()) {
        int key = event->key();
        int count = mListView->model()->rowCount();
        QModelIndex currentIndex = mListView->currentIndex();

        if (Qt::Key_Down == key) {
            // �����·����ʱ���ƶ����ѡ����һ������б��е���
            int row = currentIndex.row() + 1;
            if (row >= count) {
                row = 0;
            }

            QModelIndex index = mListView->model()->index(row, 0);
            mListView->setCurrentIndex(index);
        } else if (Qt::Key_Up == key) {
            // �����·����ʱ���ƶ����ѡ����һ������б��е���
            int row = currentIndex.row() - 1;
            if (row < 0) {
                row = count - 1;
            }

            QModelIndex index = mListView->model()->index(row, 0);
            mListView->setCurrentIndex(index);
        } else if (Qt::Key_Escape == key) {
            // ����Esc��ʱ����������б�
            mListView->hide();
        } else if (Qt::Key_Enter == key || Qt::Key_Return == key) {
            // ���»س���ʱ��ʹ������б���ѡ�е������������б�
            if (currentIndex.isValid()) {
                QString text = mListView->currentIndex().data().toString();
                setText(text);
            }

            mListView->hide();
        } else {
            // �����������������б���ʹ��QLineEdit�ļ��̰����¼�
            mListView->hide();
            QLineEdit::keyPressEvent(event);
        }
    } else {
        QLineEdit::keyPressEvent(event);
    }
}

void AutoLineEdit::setCompleter(const QString &text)
{
    if (text.isEmpty()) {
        mListView->hide();
        return;
    }
    if ((text.length() > 1) && (!mListView->isHidden())) {
        return;
    }
    // �������������б��е�ĳ�����ʰ���������ı��������Ҫ��ʾ������б���
    QStringList sl;
    foreach(QString word, mWords)
    {
        if (word.contains(text)) {
            sl << word;
        }
    }

    model->setStringList(sl);
    mListView->setModel(model);

    if (model->rowCount() == 0) {
        return;
    }

    // Position the text edit
    mListView->setMinimumWidth(width());
    mListView->setMaximumWidth(width());

    QPoint p(0, height());
    int x = mapToGlobal(p).x();
    int y = mapToGlobal(p).y() + 1;

    mListView->move(x, y);
    mListView->show();
}

void AutoLineEdit::completeText(const QModelIndex &index) {
    QString text = index.data().toString();
    setText(text);
    mListView->hide();
}

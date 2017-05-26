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
            // 按向下方向键时，移动光标选中下一个完成列表中的项
            int row = currentIndex.row() + 1;
            if (row >= count) {
                row = 0;
            }

            QModelIndex index = mListView->model()->index(row, 0);
            mListView->setCurrentIndex(index);
        } else if (Qt::Key_Up == key) {
            // 按向下方向键时，移动光标选中上一个完成列表中的项
            int row = currentIndex.row() - 1;
            if (row < 0) {
                row = count - 1;
            }

            QModelIndex index = mListView->model()->index(row, 0);
            mListView->setCurrentIndex(index);
        } else if (Qt::Key_Escape == key) {
            // 按下Esc键时，隐藏完成列表
            mListView->hide();
        } else if (Qt::Key_Enter == key || Qt::Key_Return == key) {
            // 按下回车键时，使用完成列表中选中的项，并隐藏完成列表
            if (currentIndex.isValid()) {
                QString text = mListView->currentIndex().data().toString();
                setText(text);
            }

            mListView->hide();
        } else {
            // 其他情况，隐藏完成列表，并使用QLineEdit的键盘按下事件
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
    // 如果完整的完成列表中的某个单词包含输入的文本，则加入要显示的完成列表串中
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

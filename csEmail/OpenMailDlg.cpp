#include "OpenMailDlg.h"

OpenMailDlg::OpenMailDlg(MailData &md,QWidget *parent):QDialog(parent)
{
    mFrom = new QLabel(QStringLiteral("发件人:"));
    mSubs = new QLabel(QStringLiteral("主题:"));
    mCtns = new QLabel(QStringLiteral("正文:"));
    mFromEdit = new QLineEdit();
    mSubsEdit = new QLineEdit();
    mCtnsEdit = new QTextEdit();
    mConfirm = new QPushButton(QStringLiteral("确定"));
    mainLyt  = new QGridLayout(this);

    mFromEdit -> setReadOnly(true);
    mSubsEdit -> setReadOnly(true);
    mCtnsEdit -> setReadOnly(true);
    mCtnsEdit -> setFocusPolicy(Qt::NoFocus);
    mFromEdit -> setText(QString::fromLocal8Bit(md.sender.c_str())+"<"+(QString::fromLocal8Bit(md.srcAddr.c_str())).trimmed()+">");
    mSubsEdit -> setText(QString::fromLocal8Bit(md.subject.data()));
    Contents ctns;
    QString str;
    for(deque<Contents>::iterator it = md.contents.begin();it != md.contents.end();it++)
    {
        ctns = *it;
        ctns.deContents(str);
        switch (ctns.type) {
        case 1:
            mCtnsEdit -> insertPlainText(str);
            break;
        case 2:
            //mCtnsEdit -> insertPlainText(str);
            //mCtnsEdit -> insertHtml(str);
            break;
        case 3:
            str = "<img src = "+ str + ">";
            mCtnsEdit -> append(str);
            break;
        case 4:
            QLabel *mAttach= new QLabel(QStringLiteral("附件：")+str);
            mainLyt -> addWidget(mAttach,4,2);
            qDebug()<<"附件"<<str;
            break;
        }
    }

    //mCtnsEdit -> setText(QString::fromLocal8Bit(md.contents.at(0).content.c_str()));

    mainLyt -> addWidget(mFrom,0,1,Qt::AlignLeft);
    mainLyt -> addWidget(mFromEdit,0,2);
    mainLyt -> addWidget(mSubs,1,1,Qt::AlignLeft);
    mainLyt -> addWidget(mSubsEdit,1,2);
    mainLyt -> addWidget(mCtns,2,1,Qt::AlignTop|Qt::AlignLeft);
    mainLyt -> addWidget(mCtnsEdit,2,2);
    mainLyt -> addWidget(mConfirm,3,2,Qt::AlignHCenter);
    mainLyt -> setRowStretch(0,1);
    mainLyt -> setRowStretch(1,2);
    mainLyt -> setRowStretch(2,14);
    mainLyt -> setRowStretch(3,1);
    mainLyt -> setContentsMargins(20,30,20,15);
    //mainLyt -> setRowStretch(4,1);
    setWindowIcon(QIcon(":/images/icons/opened.png"));
    connect(mConfirm,SIGNAL(clicked(bool)),this,SLOT(accept()));
    setWindowTitle(QStringLiteral("查看邮件"));
    setWindowFlags(Qt::WindowCloseButtonHint);
    resize(QSize(600,450));
}

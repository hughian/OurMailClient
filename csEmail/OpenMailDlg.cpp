#include "OpenMailDlg.h"

OpenMailDlg::OpenMailDlg(MailData &md,QWidget *parent):QDialog(parent)
{
    mFrom = new QLabel(QStringLiteral("发件人:"));
    mSubs = new QLabel(QStringLiteral("主题:"));
    mCtns = new QLabel(QStringLiteral("正文:"));
    mFromEdit = new QLineEdit();
    mSubsEdit = new QLineEdit();
    mCtnsEdit = new QTextEdit();
    mainLyt  = new QGridLayout(this);

    mFromEdit -> setDisabled(true);
    mSubsEdit -> setDisabled(true);
    mCtnsEdit -> setDisabled(true);

    mFromEdit -> setText(QString::fromLocal8Bit(md.srcAddr.c_str()));
    mSubsEdit -> setText(QString::fromLocal8Bit(md.subject.data()));
    mCtnsEdit -> setText(QString::fromLocal8Bit(md.contents.at(0).content.c_str()));
    mFromEdit -> setStyleSheet("QLineEdit:{background-color:RGB(255,255,255z);}");

    mainLyt -> addWidget(mFrom,0,1,Qt::AlignLeft);
    mainLyt -> addWidget(mFromEdit,0,2);
    mainLyt -> addWidget(mSubs,1,1,Qt::AlignLeft);
    mainLyt -> addWidget(mSubsEdit,1,2);
    mainLyt -> addWidget(mCtns,2,1,Qt::AlignTop|Qt::AlignLeft);
    mainLyt -> addWidget(mCtnsEdit,2,2);
    mainLyt -> setRowStretch(0,1);
    mainLyt -> setRowStretch(1,2);
    mainLyt -> setRowStretch(2,14);
    mainLyt -> setRowStretch(3,1);
    setWindowIcon(QIcon(":/images/icons/opened.png"));
    setWindowTitle(QStringLiteral("查看邮件"));
    setWindowFlags(Qt::WindowCloseButtonHint);
    resize(QSize(800,600));
}

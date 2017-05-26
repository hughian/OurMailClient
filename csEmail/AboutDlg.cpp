#include "AboutDlg.h"

AboutDlg::AboutDlg(QWidget *parent):QDialog(parent)
{
    mConfirm = new QPushButton(QStringLiteral("确定"));
    QToolButton *mbtn = new QToolButton();
    mbtn -> setStyleSheet("min-width:80px;min-height:80px;"
                          "border-image:url(:/images/icons/csEmail.png)");
    QLabel *mVerLabel = new QLabel(QStringLiteral("csEmail 1.116.1 Beta"));
    QLabel *mAboutLabel = new QLabel(QStringLiteral("作者：\tIyuge2 \t tel:15172502715\n"
                                                    "\t\t email:2421778006@qq.com  \n\n"
                                                    "\tHughian\t tel:15629070792\n"
                                                    "\t\t email:760156619@qq.com"));
    QGridLayout * mainLyt = new QGridLayout(this);
    mainLyt -> addWidget(mbtn,1,0,Qt::AlignCenter);
    mainLyt -> addWidget(mVerLabel,2,0,Qt::AlignTop|Qt::AlignHCenter);
    mainLyt -> addWidget(mAboutLabel,3,0,Qt::AlignCenter);
    mainLyt -> addWidget(mConfirm,5,0,Qt::AlignHCenter);
    mainLyt -> setRowStretch(0,1);
    mainLyt -> setRowStretch(1,4);
    mainLyt -> setRowStretch(2,1);
    mainLyt -> setRowStretch(3,4);
    mainLyt -> setRowStretch(4,1);
    mainLyt -> setRowStretch(5,1);
    mainLyt -> setRowStretch(6,1);

    connect(mConfirm,SIGNAL(clicked(bool)),this,SLOT(on_mConfirm_clicked()));
    setWindowIcon(QIcon(":/images/icons/about.png"));
    setWindowTitle(QStringLiteral("关于"));
    setWindowFlags(Qt::WindowCloseButtonHint);
    resize(QSize(400,300));
}

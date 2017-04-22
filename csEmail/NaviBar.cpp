#include "NaviBar.h"

ToolBtn::ToolBtn(QString name,QString str,QWidget *parent):QWidget(parent)
{
    QToolButton *mbtn = new QToolButton(this);
    QLabel *mlabel = new QLabel(this);
    mlabel -> setText(name);
    mbtn-> setStyleSheet(str);
    QHBoxLayout *LabelLyt = new QHBoxLayout();
    QVBoxLayout *mainLyt = new QVBoxLayout(this);
    mainLyt -> addWidget(mbtn);
    LabelLyt -> addSpacing(4);
    LabelLyt -> addWidget(mlabel);
    mainLyt -> addLayout(LabelLyt);
}
NaviBar::NaviBar(int a,QWidget *parent):QWidget(parent)
{
    setStyleSheet("QToolButton{min-width:40px;min-height:40px;} \
                   QToolButton:hover{border-style:solid;border:4px;}\
                   QTollButton:pressed{background:red;}");
    ToolBtn *mWriteMail = new ToolBtn(QStringLiteral("写　信"),"border-image:url(:/images/icons/write_2.png)",this);
    ToolBtn *mSettings  = new ToolBtn(QStringLiteral("设　置"),"border-image:url(:/images/icons/settings.png)",this);
    ToolBtn *mContacts  = new ToolBtn(QStringLiteral("联系人"),"border-image:url(:/images/icons/contacts.png)",this);
    ToolBtn *mRecvBox   = new ToolBtn(QStringLiteral("收件箱"),"border-image:url(:/images/icons/recv.png)",this);
    ToolBtn *mSendBox   = new ToolBtn(QStringLiteral("已发送"),"border-image:url(:/images/icons/send.png)",this);
    ToolBtn *mDraftBox  = new ToolBtn(QStringLiteral("草稿箱"),"border-image:url(:/images/icons/draftbox.png)",this);
    ToolBtn *mDustBin   = new ToolBtn(QStringLiteral("垃圾箱"),"border-image:url(:/images/icons/dustbin.png)",this);
    ToolBtn *mAbout     = new ToolBtn(QStringLiteral("关　于"),"border-image:url(:/images/icons/about.png)",this);
    QVBoxLayout *mainLyt = new QVBoxLayout(this);
    mainLyt -> addWidget(mWriteMail);
    mainLyt -> addWidget(mSettings);
    mainLyt -> addWidget(mContacts);
    mainLyt -> addWidget(mRecvBox);
    mainLyt -> addWidget(mSendBox);
    mainLyt -> addWidget(mDraftBox);
    mainLyt -> addWidget(mDustBin);
    mainLyt -> addWidget(mAbout);
}

NaviBar::NaviBar(QWidget *parent):QWidget(parent)
{
    QSize btnsize(50,50);
    mWriteMail = new QToolButton();
    mWriteMail-> setIcon(QIcon(":/images/icons/write_2.png"));
    mWriteMail-> setIconSize(btnsize);
    mWriteMail-> setText(QStringLiteral("写　信"));
    mWriteMail-> setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    mContacts = new QToolButton();
    mContacts -> setIcon(QIcon(":/images/icons/contacts.png"));
    mContacts -> setIconSize(btnsize);
    mContacts -> setText(QStringLiteral("联系人"));
    mContacts -> setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    mRecvBox  = new QToolButton();
    mRecvBox -> setIcon(QIcon(":/images/icons/recv.png"));
    mRecvBox -> setIconSize(btnsize);
    mRecvBox -> setText(QStringLiteral("收件箱"));
    mRecvBox -> setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    mSendBox  = new QToolButton();
    mSendBox -> setIcon(QIcon(":/images/icons/send.png"));
    mSendBox -> setIconSize(btnsize);
    mSendBox -> setText(QStringLiteral("已发送"));
    mSendBox -> setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    mDraftBox = new QToolButton();
    mDraftBox -> setIcon(QIcon(":/images/icons/draftbox.png"));
    mDraftBox -> setIconSize(btnsize);
    mDraftBox -> setText(QStringLiteral("草稿箱"));
    mDraftBox -> setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    mDustBin  = new QToolButton();
    mDustBin -> setIcon(QIcon(":/images/icons/dustbin.png"));
    mDustBin -> setIconSize(btnsize);
    mDustBin -> setText(QStringLiteral("垃圾箱"));
    mDustBin -> setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    mSettings = new QToolButton();
    mSettings  -> setIcon(QIcon(":/images/icons/settings.png"));
    mSettings  -> setIconSize(btnsize);
    mSettings  -> setText(QStringLiteral("设　置"));
    mSettings  -> setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    mAbout    = new QToolButton();
    mAbout -> setIcon(QIcon(":/images/icons/about.png"));
    mAbout -> setIconSize(btnsize);
    mAbout -> setText(QStringLiteral("关　于"));
    mAbout -> setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QVBoxLayout *mainLyt = new QVBoxLayout(this);
    mainLyt -> addWidget(mWriteMail);
    //mainLyt -> addWidget(mContacts);
    mainLyt -> addWidget(mRecvBox);
    mainLyt -> addWidget(mSendBox);
    mainLyt -> addWidget(mDraftBox);
    mainLyt -> addWidget(mDustBin);
    mainLyt -> addWidget(mSettings);
    mainLyt -> addWidget(mAbout);
}

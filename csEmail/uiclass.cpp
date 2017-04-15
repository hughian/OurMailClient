#include "uiclass.h"

NavigationBar::NavigationBar(QWidget *parent):
    QWidget(parent)
{
    mWriteMail = new QPushButton(QStringLiteral("写信"));
    mSettings  = new QPushButton(QStringLiteral("设置"));
    mContacts  = new QPushButton(QStringLiteral("联系人"));
    mRecvBox   = new QPushButton(QStringLiteral("收件箱"));
    mSendBox   = new QPushButton(QStringLiteral("发件箱"));
    mDraftBox  = new QPushButton(QStringLiteral("草稿箱"));
    mDustBin   = new QPushButton(QStringLiteral("垃圾箱"));

    QVBoxLayout *BtnLyt = new QVBoxLayout();
    QVBoxLayout *BoxLyt = new QVBoxLayout();
    BtnLyt -> addWidget(mWriteMail);
    BtnLyt -> addWidget(mSettings);
    BoxLyt -> addWidget(mContacts);
    BoxLyt -> addWidget(mRecvBox);
    BoxLyt -> addWidget(mSendBox);
    BoxLyt -> addWidget(mDraftBox);
    BoxLyt -> addWidget(mDustBin);
    QGroupBox *BtnGroup = new QGroupBox(this);
    QGroupBox *BoxGroup = new QGroupBox(this);
    BtnGroup -> setLayout(BtnLyt);
    BoxGroup -> setLayout(BoxLyt);
    QVBoxLayout *GroupLyt = new QVBoxLayout();
    GroupLyt -> addStretch(1);
    GroupLyt -> addWidget(BtnGroup);
    GroupLyt -> addStretch(1);
    GroupLyt -> addWidget(BoxGroup);
    GroupLyt -> addStretch(18);
    QGroupBox *mGroup = new QGroupBox(this);
    mGroup -> setLayout(GroupLyt);
    QGridLayout *mainLyt = new QGridLayout(this);
    mainLyt -> addWidget(mGroup);
    //setLayout(mainLyt);
}
NavigationBar::~NavigationBar()
{

}

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
NaviBar::NaviBar(QWidget *parent):QWidget(parent)
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

NaviBar::NaviBar(int a,QWidget *parent):QWidget(parent)
{
    mWriteMail = new QToolButton();
    mWriteMail-> setIcon(QIcon(":/images/icons/write_2.png"));
    mWriteMail-> setIconSize(QSize(40,40));
    mWriteMail-> setText(QStringLiteral("写　信"));
    mWriteMail-> setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    mContacts = new QToolButton();
    mContacts -> setIcon(QIcon(":/images/icons/contacts.png"));
    mContacts -> setIconSize(QSize(40,40));
    mContacts -> setText(QStringLiteral("联系人"));
    mContacts -> setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    mRecvBox  = new QToolButton();
    mRecvBox -> setIcon(QIcon(":/images/icons/recv.png"));
    mRecvBox -> setIconSize(QSize(40,40));
    mRecvBox -> setText(QStringLiteral("收件箱"));
    mRecvBox -> setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    mSendBox  = new QToolButton();
    mSendBox -> setIcon(QIcon(":/images/icons/send.png"));
    mSendBox -> setIconSize(QSize(40,40));
    mSendBox -> setText(QStringLiteral("已发送"));
    mSendBox -> setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    mDraftBox = new QToolButton();
    mDraftBox -> setIcon(QIcon(":/images/icons/draftbox.png"));
    mDraftBox -> setIconSize(QSize(40,40));
    mDraftBox -> setText(QStringLiteral("草稿箱"));
    mDraftBox -> setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    mDustBin  = new QToolButton();
    mDustBin -> setIcon(QIcon(":/images/icons/dustbin.png"));
    mDustBin -> setIconSize(QSize(40,40));
    mDustBin -> setText(QStringLiteral("垃圾箱"));
    mDustBin -> setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    mSettings = new QToolButton();
    mSettings  -> setIcon(QIcon(":/images/icons/settings.png"));
    mSettings  -> setIconSize(QSize(40,40));
    mSettings  -> setText(QStringLiteral("设　置"));
    mSettings  -> setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    mAbout    = new QToolButton();
    mAbout -> setIcon(QIcon(":/images/icons/about.png"));
    mAbout -> setIconSize(QSize(40,40));
    mAbout -> setText(QStringLiteral("关　于"));
    mAbout -> setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    QVBoxLayout *mainLyt = new QVBoxLayout(this);
    mainLyt -> addWidget(mWriteMail);
    mainLyt -> addWidget(mContacts);
    mainLyt -> addWidget(mRecvBox);
    mainLyt -> addWidget(mSendBox);
    mainLyt -> addWidget(mDraftBox);
    mainLyt -> addWidget(mDustBin);
    mainLyt -> addWidget(mSettings);
    mainLyt -> addWidget(mAbout);

}

MailList::MailList(int type,QWidget *parent):QWidget(parent)
{
    mTable = new QTableWidget(this);
    mTable -> setColumnCount(4);
    mTable -> horizontalHeader()->setDefaultSectionSize(150);
    mTable -> horizontalHeader()->setSectionsMovable(false);
    mTable -> horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    mTable -> horizontalHeader() ->resizeSection(0,30);
    mTable -> horizontalHeader() ->setDefaultAlignment(Qt::AlignCenter);
    mTable -> horizontalHeader() ->setSectionsClickable(false); //setClickable(bool) is obsoleted;

    QFont font = mTable -> horizontalHeader() -> font();
    font.setBold(true);
    mTable -> horizontalHeader() -> setFont(font);
    mTable -> horizontalHeader() -> setStretchLastSection(true);
    mTable -> setShowGrid(false);
    mTable -> verticalHeader() -> setVisible(false);
    mTable -> setEditTriggers(QAbstractItemView::NoEditTriggers);
    mTable -> setSelectionBehavior(QAbstractItemView::SelectRows);
    mTable -> setSelectionMode(QAbstractItemView::SingleSelection);

    QStringList header;
    QTableWidgetItem *item = new QTableWidgetItem();
    item -> setIcon(QIcon(":/images/icons/unopen.png"));
    item -> setSizeHint(QSize(12,12));
    mTable -> setHorizontalHeaderItem(0,item);
    switch (type) {
    case RECV:
        header<<QStringLiteral("")<<QStringLiteral("发件人")<<QStringLiteral("主题")<<QStringLiteral("时间");
        break;
    case SEND:
    case DRAFT:
        header<<QStringLiteral("")<<QStringLiteral("收件人")<<QStringLiteral("主题")<<QStringLiteral("时间");
        break;
    case DUST:
        header<<QStringLiteral("")<<QStringLiteral("人")<<QStringLiteral("主题")<<QStringLiteral("时间");
    default:
        break;
    }
    mTable -> setHorizontalHeaderLabels(header);

    mTable -> setRowCount(1);
    mTable -> setItem(0,0, new QTableWidgetItem("123"));
    QVBoxLayout *mainLyt = new QVBoxLayout(this);
    mainLyt -> addWidget(mTable);
}

WriteMailDlg::WriteMailDlg(QWidget *parent):QDialog(parent)
{
    mSave = new QPushButton(QStringLiteral("保存为草稿"));
    mSend = new QPushButton(QStringLiteral("发送"));
    mQuit = new QPushButton(QStringLiteral("取消"));
    mRecvEdit = new QLineEdit();
    mSubsEdit = new QLineEdit();
    mCtntEdit = new QTextEdit();

    QLabel *mRecvLabel = new QLabel(QStringLiteral("收件人"));
    QLabel *mTipsLabel = new QLabel(QStringLiteral("若多个收件人，收件人地址之间请用分号';'隔开.例如760156619@qq.com;Hughian@gmail.com"));
    QLabel *mSubsLabel = new QLabel(QStringLiteral("主题"));
    QLabel *mCtntLabel = new QLabel(QStringLiteral("正文"));
    QGridLayout *mainLyt = new QGridLayout(this);
    mainLyt -> addWidget(mRecvLabel,1,0);
    mainLyt -> addWidget(mRecvEdit ,1,1,1,4);
    mainLyt -> addWidget(mTipsLabel,2,1);
    mainLyt -> addWidget(mSubsLabel,3,0);
    mainLyt -> addWidget(mSubsEdit ,3,1);
    mainLyt -> addWidget(mCtntLabel,4,0);
    mainLyt -> addWidget(mCtntEdit,5,0,1,5);
    mainLyt -> addWidget(mSend,6,1,Qt::AlignCenter);
    mainLyt -> addWidget(mSave,6,2,Qt::AlignCenter);
    mainLyt -> addWidget(mQuit,6,3,Qt::AlignCenter);

    mainLyt -> setRowStretch(0,1);
    mainLyt -> setRowStretch(1,1);
    mainLyt -> setRowStretch(2,1);
    mainLyt -> setRowStretch(3,1);
    mainLyt -> setRowStretch(4,1);
    mainLyt -> setRowStretch(5,12);
    mainLyt -> setRowStretch(6,1);

    setWindowIcon(QIcon(":/images/icons/write_2.png"));
    setWindowTitle(QStringLiteral("写信"));
    setWindowFlags(Qt::WindowCloseButtonHint);
    resize(QSize(800,600));
}

SettingsDlg::SettingsDlg(QWidget *parent):QDialog(parent)
{
    QLabel *mUsrLabel = new QLabel(QStringLiteral("用户名：　　"));
    QLabel *mAdrLabel = new QLabel(QStringLiteral("邮件账户：　"));
    QLabel *mPopLabel = new QLabel(QStringLiteral("收件服务器："));
    QLabel *mMtpLabel = new QLabel(QStringLiteral("发送服务器："));
    QLabel *mRptLabel = new QLabel(QStringLiteral("　端口号："));
    QLabel *mSptLabel = new QLabel(QStringLiteral("　端口号："));
    QLabel *mActLabel = new QLabel(QStringLiteral("账户：　　　"));
    QLabel *mPswLabel = new QLabel(QStringLiteral("密码：　　　"));

    mUsrEdit = new QLineEdit();
    mAdrEdit = new QLineEdit();
    mPopEdit = new QLineEdit();
    mRptEdit = new QLineEdit();
    mMtpEdit = new QLineEdit();
    mSptEdit = new QLineEdit();
    mActEdit = new QLineEdit();
    mPswEdit = new QLineEdit();
    mPswEdit -> setEchoMode(QLineEdit::Password);

    QGroupBox *mUsrGroup = new QGroupBox(QStringLiteral("用户设置"));
    QGroupBox *mSerGroup = new QGroupBox(QStringLiteral("服务器设置"));
    QGroupBox *mActGroup = new QGroupBox(QStringLiteral("账户设置"));

    QGridLayout *mUsrLyt = new QGridLayout();
    QGridLayout *mSerLyt = new QGridLayout();
    QGridLayout *mActLyt = new QGridLayout();

    mUsrLyt -> addWidget(mUsrLabel,0,0);
    mUsrLyt -> addWidget(mUsrEdit,0,1);
    mUsrLyt -> addWidget(mAdrLabel,1,0);
    mUsrLyt -> addWidget(mAdrEdit,1,1);
    //
    mUsrLyt -> setColumnStretch(0,1);
    mUsrLyt -> setColumnStretch(1,7);
    mUsrLyt -> setRowStretch(0,1);
    mUsrLyt -> setRowStretch(1,1);
    //
    mUsrLyt -> setContentsMargins(60,20,120,20);
    mUsrGroup -> setLayout(mUsrLyt);

    mSerLyt -> addWidget(mPopLabel,0,0);
    mSerLyt -> addWidget(mPopEdit,0,1);
    mSerLyt -> addWidget(mRptLabel,0,2);
    mSerLyt -> addWidget(mRptEdit,0,3);
    mSerLyt -> addWidget(mMtpLabel,1,0);
    mSerLyt -> addWidget(mMtpEdit,1,1);
    mSerLyt -> addWidget(mSptLabel,1,2);
    mSerLyt -> addWidget(mSptEdit,1,3);
    //
    mSerLyt -> setColumnStretch(0,2);
    mSerLyt -> setColumnStretch(1,5);
    mSerLyt -> setColumnStretch(2,1);
    mSerLyt -> setColumnStretch(3,1);
    mSerLyt -> setRowStretch(0,1);
    mSerLyt -> setRowStretch(1,1);
    //
    mSerLyt -> setContentsMargins(60,20,100,20);
    mSerGroup -> setLayout(mSerLyt);

    mActLyt -> addWidget(mActLabel,0,0);
    mActLyt -> addWidget(mActEdit,0,1);
    mActLyt -> addWidget(mPswLabel,1,0);
    mActLyt -> addWidget(mPswEdit,1,1);
    //
    mActLyt -> setColumnStretch(0,1);
    mActLyt -> setColumnStretch(1,7);
    mActLyt -> setRowStretch(0,1);
    mActLyt -> setRowStretch(1,1);
    //
    mActLyt -> setContentsMargins(60,20,120,20);
    mActGroup -> setLayout(mActLyt);

    mConfirm = new QPushButton(QStringLiteral("确定"));
    mCancel  = new QPushButton(QStringLiteral("取消"));


    QHBoxLayout *mBtnLyt = new QHBoxLayout();
    mBtnLyt -> addStretch(13);
    mBtnLyt -> addWidget(mConfirm);
    mBtnLyt -> addWidget(mCancel);
    mBtnLyt -> addStretch(1);
    QFrame *mBtnFrame = new QFrame();
    mBtnFrame -> setLayout(mBtnLyt);

    QGridLayout *mainLyt = new QGridLayout(this);
    mainLyt -> addWidget(mUsrGroup,0,0);
    mainLyt -> addWidget(mSerGroup,1,0);
    mainLyt -> addWidget(mActGroup,2,0);
    mainLyt -> addWidget(mBtnFrame,3,0);

    connect(mConfirm,SIGNAL(clicked(bool)),this,SLOT(on_mConfirm_clicked()));
    connect(mCancel ,SIGNAL(clicked(bool)),this,SLOT(on_mCancel_clicked ()));
    setWindowIcon(QIcon(":/images/icons/settings.png"));
    setWindowTitle(QStringLiteral("设置"));
    setWindowFlags(Qt::WindowCloseButtonHint);
    resize(QSize(500,400));
    this->readFile();
}

bool SettingsDlg::readFile()
{
    QString str[8];
    QLineEdit * a[8]={mUsrEdit,mAdrEdit,mPopEdit,mRptEdit,mMtpEdit,mSptEdit,mActEdit,mPswEdit};
    int i=0;
    readSetFile(this,str);
    while(i<8){
        a[i] -> setText(str[i]);
        i++;
    }
    return true;
}
bool SettingsDlg::writeFile()
{
    QFile file("../csEmail/data/settings.txt");
    if(!file.open(QIODevice::WriteOnly)){
        QMessageBox::warning(this,QStringLiteral("警告"),QStringLiteral("无法打开文件settings.txt"),QMessageBox::Yes);
        return false;
    }
    QDataStream stream(&file);
    QString str;
    int i=0;
    QLineEdit * a[8]={mUsrEdit,mAdrEdit,mPopEdit,mRptEdit,mMtpEdit,mSptEdit,mActEdit,mPswEdit};
    while(i<8){
        str = a[i++]->text();
        stream << str;
    }
    file.close();
    QString mTitle = "csEmail - "+mUsrEdit->text();
    send(mTitle);
    return true;
}

void SettingsDlg::on_mConfirm_clicked()
{
    this->writeFile();
    accept();
}
void SettingsDlg::on_mCancel_clicked()
{
    accept();
}


AboutDlg::AboutDlg(QWidget *parent):QDialog(parent)
{
    mConfirm = new QPushButton(QStringLiteral("确定"));
    QToolButton *mbtn = new QToolButton();
    mbtn -> setStyleSheet("min-width:80px;min-height:80px;"
                          "border-image:url(:/images/icons/csEmail.png)");
    QLabel *mVerLabel = new QLabel(QStringLiteral("csEmail 1.116.1 Beta"));
    QLabel *mAboutLabel = new QLabel(QStringLiteral("作者：\tIyuge2 \t tel:15172502715\n"
                                                    "\t\t email:1223#gmail.com  \n\n"
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


#include "Settings.h"
extern QString setData[8];

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

    //mUsrEdit = new AutoLineEdit();
    mUsrEdit = new QLineEdit();
    mAdrEdit = new QLineEdit();
    mPopEdit = new QLineEdit();
    mRptEdit = new QLineEdit();
    mMtpEdit = new QLineEdit();
    mSptEdit = new QLineEdit();
    mActEdit = new QLineEdit();
    mPswEdit = new QLineEdit();
    mRptEdit -> setEnabled(false);
    mSptEdit -> setEnabled(false);
    mPswEdit -> setEchoMode(QLineEdit::Password);

    mComboBox = new QComboBox();
    mComboBox -> addItem(QStringLiteral("保留服务器端邮件"));
    mComboBox -> addItem(QStringLiteral("删除服务器端邮件"));

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
    mActLyt -> addWidget(mComboBox,2,1);
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
    QLineEdit * a[8]={mUsrEdit,mAdrEdit,mPopEdit,mRptEdit,mMtpEdit,mSptEdit,mActEdit,mPswEdit};
    int i=0;
    readSetFile(this,setData);
    while(i<8){
        a[i] -> setText(setData[i]);
        i++;
    }
    mComboBox -> setCurrentIndex(setData[deleteOp].toInt());
    return true;
}
bool SettingsDlg::writeFile()
{
    int i=0;
    QLineEdit * a[8]={mUsrEdit,mAdrEdit,mPopEdit,mRptEdit,mMtpEdit,mSptEdit,mActEdit,mPswEdit};
    while(i<8){
        setData[i] = a[i]->text();
        i++;
    }
    setData[i] = QString::number(mComboBox->currentIndex(),10);

    writeSetFile(this,setData);
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


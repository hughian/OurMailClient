#include "WriteMailDlg.h"
extern QString setData[8];
WriteMailDlg::WriteMailDlg(QWidget *parent):QDialog(parent)
{
    mSave = new QPushButton(QStringLiteral("保存为草稿"));
    mSend = new QPushButton(QStringLiteral("发送"));
    mQuit = new QPushButton(QStringLiteral("取消"));
    mRecvEdit = new QLineEdit();
    mSubsEdit = new QLineEdit();
    mCtntEdit = new QTextEdit();
    mDraftEdited = false;
    mDraftorMail = false; // default as mail
    QLabel *mRecvLabel = new QLabel(QStringLiteral("收件人"));
    QLabel *mTipsLabel = new QLabel(QStringLiteral("若多个收件人，收件人地址之间请用分号';'隔开.例如760156619@qq.com;Hughian@gmail.com"));
    QLabel *mSubsLabel = new QLabel(QStringLiteral("主题"));
    QLabel *mCtntLabel = new QLabel(QStringLiteral("正文"));
    QGridLayout *mainLyt = new QGridLayout(this);
    mainLyt -> addWidget(mRecvLabel,0,1);
    mainLyt -> addWidget(mRecvEdit ,0,2,1,4);
    mainLyt -> addWidget(mTipsLabel,1,2,1,4);
    mainLyt -> addWidget(mSubsLabel,2,1);
    mainLyt -> addWidget(mSubsEdit ,2,2,1,4);
    mainLyt -> addWidget(mCtntLabel,3,1,Qt::AlignTop);
    mainLyt -> addWidget(mCtntEdit ,3,2,1,4);
    mainLyt -> addWidget(mSend,4,3,Qt::AlignCenter);
    mainLyt -> addWidget(mSave,4,4,Qt::AlignRight);
    mainLyt -> addWidget(mQuit,4,5,Qt::AlignLeft);
    mainLyt -> setVerticalSpacing(10);
    mainLyt -> setColumnStretch(0,1);
    mainLyt -> setColumnStretch(1,1);
    mainLyt -> setColumnStretch(2,6);
    mainLyt -> setColumnStretch(3,12);
    mainLyt -> setColumnStretch(4,1);
    mainLyt -> setColumnStretch(5,1);
    mainLyt -> setColumnStretch(6,1);
    mainLyt -> setRowStretch(0,1);
    mainLyt -> setRowStretch(1,0);
    mainLyt -> setRowStretch(2,1);
    mainLyt -> setRowStretch(3,12);
    mainLyt -> setRowStretch(4,1);
    mainLyt -> setContentsMargins(0,30,0,15);

    connect(mSend,SIGNAL(clicked(bool)),this,SLOT(sendEmail()));
    connect(mSave,SIGNAL(clicked(bool)),this,SLOT(save()));
    connect(mQuit,SIGNAL(clicked(bool)),this,SLOT(close()));

    connect(mRecvEdit,SIGNAL(textEdited(QString)),this,SLOT(setFlag()));
    connect(mSubsEdit,SIGNAL(textEdited(QString)),this,SLOT(setFlag()));
    connect(mCtntEdit,SIGNAL(textChanged()),this,SLOT(setFlag()));
    setWindowIcon(QIcon(":/images/icons/write_2.png"));
    setWindowTitle(QStringLiteral("写信"));
    setWindowFlags(Qt::WindowCloseButtonHint);
    resize(QSize(800,600));
}
void WriteMailDlg::change()
{
    qDebug()<<"change";
}
void WriteMailDlg::edit()
{
    qDebug()<<"edit";
}
void WriteMailDlg::setFlag()
{
    if(mDraftorMail){
        if(mQsl.at(1)==mRecvEdit->text() && mQsl.at(3)==mSubsEdit->text() && mQsl.at(4)==mCtntEdit->toPlainText())
        {   mDraftEdited = false;   qDebug()<<"f";}
        else
        {   mDraftEdited = true;    qDebug()<<"t";}
    }
}
void WriteMailDlg::readEdits(MailData &md)
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QStringList qsl;
    QString str;
    md.srcAddr = setData[1].toStdString();
    md.sender  = setData[0].toStdString();
    md.subject = mSubsEdit->text().toStdString();
    //md.contents= mCtntEdit->toPlainText().toStdString();
    md.time  = currentTime.toString("yyyy-MM-dd hh:mm:ss").toStdString();
    qsl = mRecvEdit->text().split(";",QString::SkipEmptyParts);
    for(QStringList::Iterator it = qsl.begin();it != qsl.end();it++){
        str = *it;
        md.dstAddr.push_back(str.toStdString());
    }
}
void WriteMailDlg::openDraft(QStringList &qsl)
{
    mQsl = qsl;
    mRecvEdit->setText(qsl.at(1));
    mSubsEdit->setText(qsl.at(3));
    mCtntEdit->setText(qsl.at(4));
    mDraftorMail = true;
    mDraftEdited = false;
}
void WriteMailDlg::sendEmail()
{
    MailData md;
    this->readEdits(md);
    QStringList qsl;
    md.toQStringList(qsl);
    qDebug()<<qsl;
//    MsgBox *msg = new MsgBox();
//    msg->show();
    /*
     * here is where the messages will be send ;
     * call send() to mail the MailData md;
     * function send() to check the data completeness;
     */

    QMessageBox::information(this,QStringLiteral("发送邮件"),QStringLiteral("邮件发送成功"),QMessageBox::NoButton);
    accept();
}
void WriteMailDlg::saveDraft()
{
    QFile file("../csEmail/data/draft.txt");
    QStringList qsl;
    QString str;
    MailData md;
    if(!file.open(QIODevice::WriteOnly|QIODevice::Append))
    {
        QMessageBox::warning(this,QStringLiteral("警告"),QStringLiteral("无法打开文件draft.txt"),QMessageBox::Yes);
        accept();
    }
    QDataStream stream(&file);
    this -> readEdits(md);
    md.toQStringList(qsl);
    str = qsl.at(4);
    str.replace("\n","$#$");
    qsl.replace(4,str);
    qDebug()<<str;
    str = qsl.join("\n");
    stream<<str;
    file.close();
    QMessageBox::information(this,QStringLiteral("存草稿"),QStringLiteral("草稿保存成功"),QMessageBox::Ok);
}
void WriteMailDlg::save()
{

    bool editsEmpty = checkEdit();
    qDebug()<<"123"<<editsEmpty<<mDraftEdited<<mDraftorMail;
    if(!mDraftorMail && editsEmpty)
        QMessageBox::warning(this,QStringLiteral("信息为空"),QStringLiteral("未输入任何邮件信息！"),QMessageBox::NoButton);
    else if(!mDraftorMail && !editsEmpty){
        this -> saveDraft();
        accept();
    }
    else if(mDraftorMail && !mDraftEdited){
        //qDebug()<<"456"<<QStringLiteral("草稿没有编辑，不用处理");//草稿没有编辑，不用处理
        QMessageBox::warning(this,QStringLiteral("存草稿"),QStringLiteral("草稿保存成功"),QMessageBox::Ok);
        accept();
    }
    else{//草稿有编辑,是否被删空
        if(editsEmpty){
            if(QMessageBox::warning(this,QStringLiteral("信息为空"),QStringLiteral("是否丢弃原草稿！"),QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
            {
                //this->delte();
                accept();
            }else{
                accept();
            }
            qDebug()<<"789"<<QStringLiteral("删空，是否丢弃该草稿？");//删空，是否丢弃该草稿？
        }
        else{
            if(QMessageBox::warning(this,QStringLiteral("保存草稿"),QStringLiteral("是否覆盖原草稿！"),QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
            {
                //this->replace();
                accept();
            }
            qDebug()<<"000"<<QStringLiteral("草稿已经存在是否替换？");//草稿已经存在是否替换？
        }
    }
}
bool WriteMailDlg::checkEdit()
{
    if(mRecvEdit->text().size() == 0 && mSubsEdit->text().size() == 0 && mCtntEdit->toPlainText().size()==0)
        return true;
    else
        return false;
}

void WriteMailDlg::closeEvent(QCloseEvent *event)
{
    if(mDraftorMail && !mDraftEdited){
        accept();
    }
    else if(mDraftorMail && mDraftEdited)
    {
        this -> save();
        qDebug()<<QStringLiteral("草稿修改");
    }else{
        if(checkEdit())
            event -> accept();
        else{
            if(QMessageBox::warning(this,QStringLiteral("退出写信"),QStringLiteral("是否保存草稿？"),QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes)
            {
                this->saveDraft();
                event->accept();
            }
            else{
                event->accept();
            }
        }
    }
}

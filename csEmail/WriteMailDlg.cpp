#include "WriteMailDlg.h"
#include "SendingDlg.h"
#include "MySmtp.h"
#include "qt.h"
#include <QFileDialog>
#include <fstream>
#include <sstream>
extern QString setData[8];
WriteMailDlg::WriteMailDlg(QWidget *parent):QDialog(parent)
{
    mSave  = new QPushButton(QStringLiteral("保存为草稿"));
    mSend  = new QPushButton(QStringLiteral("发送"));
    mQuit  = new QPushButton(QStringLiteral("取消"));
    mAttach= new QPushButton(QStringLiteral("添加附件"));
    mPhoto = new QPushButton(QStringLiteral("照片"));
    mBcc   = new QPushButton(QStringLiteral("添加密送"));
    mCC    = new QPushButton(QStringLiteral("添加抄送"));
    mRecvEdit = new QLineEdit();
    mBccEdit  = new QLineEdit();
    mCCEdit   = new QLineEdit();
    mSubsEdit = new QLineEdit();
    mCtntEdit = new QTextEdit();
    mDraftEdited = false;
    mDraftorMail = false; // default as mail
    mRecvLabel = new QLabel(QStringLiteral("收件人"));
    mTipsLabel = new QLabel(QStringLiteral("若多个收件人，收件人地址之间请用分号';'隔开.例如760156619@qq.com;Hughian@gmail.com"));
    mSubsLabel = new QLabel(QStringLiteral("主题"));
    mCtntLabel = new QLabel(QStringLiteral("正文"));
    mBccLabel  = new QLabel(QStringLiteral("密送"));
    mCCLabel   = new QLabel(QStringLiteral("抄送"));
    mAttachLabel = new QLabel();
    //mCtntEdit -> append("<img src = E://right.png>");
    mAttach -> setFlat(true);
    mPhoto  -> setFlat(true);
    mBcc    -> setFlat(true);
    mCC     -> setFlat(true);
    //mAttach -> setFocusPolicy(Qt::NoFocus);
    mAttach -> setStyleSheet({"QPushButton{border:none;color:blue;}"
                              "QPushButton:hover{text-decoration: underline;}"
                              "QPushButton:pressed{}"});
    mPhoto  -> setStyleSheet({"QPushButton{border:none;color:blue;}"
                              "QPushButton:hover{text-decoration: underline;}"
                              "QPushButton:pressed{}"});
    mBcc    -> setStyleSheet({"QPushButton{border:none;color:blue;}"
                              "QPushButton:hover{text-decoration: underline;}"
                              "QPushButton:pressed{}"});
    mCC     -> setStyleSheet({"QPushButton{border:none;color:blue;}"
                              "QPushButton:hover{text-decoration: underline;}"
                              "QPushButton:pressed{}"});
    mSend   -> setDefault(true);
    mainLyt = new QGridLayout(this);
    ki = 0; mi = 0;
    kj = 0; mj = 0;
    bbci = false;
    bcci = false;
    bj = false;
    setLyt();
    connect(mSend,SIGNAL(clicked(bool)),this,SLOT(sendEmail()));
    connect(mSave,SIGNAL(clicked(bool)),this,SLOT(save()));
    connect(mQuit,SIGNAL(clicked(bool)),this,SLOT(close()));

    connect(mAttach,SIGNAL(clicked(bool)),this,SLOT(attachFile()));
    connect(mPhoto,SIGNAL(clicked(bool)),this,SLOT(addPic()));
    connect(mBcc,SIGNAL(clicked(bool)),this,SLOT(addBcc()));
    connect(mCC,SIGNAL(clicked(bool)),this,SLOT(addCC()));
    connect(mRecvEdit,SIGNAL(textEdited(QString)),this,SLOT(setFlag()));
    connect(mSubsEdit,SIGNAL(textEdited(QString)),this,SLOT(setFlag()));
    connect(mCtntEdit,SIGNAL(textChanged()),this,SLOT(setFlag()));
    setWindowIcon(QIcon(":/images/icons/write_2.png"));
    setWindowTitle(QStringLiteral("写信"));
    setWindowFlags(Qt::WindowCloseButtonHint);
    resize(QSize(800,600));
}
void WriteMailDlg::setLyt(int i,int j)
{
    mi = i;
    mj = j;
    switch (i) {
    case 0:
        break;
    case 1:
        ki++;
        mainLyt -> addWidget(mBccLabel ,ki,1,Qt::AlignLeft);
        mainLyt -> addWidget(mBccEdit ,ki,2,1,5);
        mBccLabel -> show();
        mBccEdit  -> show();
        mBcc->setText(QStringLiteral("取消密送"));
        //
        break;
    case 2:
        ki++;
        mainLyt -> addWidget(mCCLabel ,ki,1,Qt::AlignLeft);
        mainLyt -> addWidget(mCCEdit ,ki,2,1,5);
        mCCLabel -> show();
        mCCEdit  -> show();
        mCC->setText(QStringLiteral("取消抄送"));
        break;
    case 3:
        if(ki == 2)
        {
            mainLyt -> addWidget(mCCLabel ,1,1,Qt::AlignLeft);
            mainLyt -> addWidget(mCCEdit ,1,2,1,5);
            mCCLabel -> show();
            mCCEdit  -> show();
            mCC->setText(QStringLiteral("取消抄送"));
        }
        ki--;
        mainLyt -> removeWidget(mBccLabel);
        mainLyt -> removeWidget(mBccEdit);
        mBccLabel -> hide();
        mBccEdit  -> hide();
        mBccEdit  -> setText("");
        mBcc->setText(QStringLiteral("添加密送"));
        break;
    case 4:
        //mainLyt -> setRowStretch(ki,0);
        if(ki == 2)
        {
            mainLyt -> addWidget(mBccLabel ,1,1,Qt::AlignLeft);
            mainLyt -> addWidget(mBccEdit ,1,2,1,5);
            mBccLabel -> show();
            mBccEdit  -> show();
            mBcc->setText(QStringLiteral("取消密送"));
        }
        ki--;
        mainLyt -> removeWidget(mCCLabel);
        mainLyt -> removeWidget(mCCEdit);
        mCCLabel -> hide();
        mCCEdit  -> hide();
        mCCEdit  -> setText("");
        mCC->setText(QStringLiteral("添加抄送"));
        break;
    default:
        break;
    }
    switch (j) {
    case 0:
        break;
    case 1:
        if(battach){
            kj=1;
            battach = false;
        }
        mAttachLabel -> setText(fileName);
        mainLyt -> addWidget(mAttachLabel,3+ki+1,2,Qt::AlignRight);
            break;
//      default:
//          break;
    }

    //
    mainLyt -> addWidget(mRecvLabel,0,1,Qt::AlignLeft);
    mainLyt -> addWidget(mRecvEdit ,0,2,1,5);
    //

    mainLyt -> addWidget(mBcc      ,1+ki,2,Qt::AlignRight);
    mainLyt -> addWidget(mCC       ,1+ki,3,Qt::AlignLeft);
    mainLyt -> addWidget(mTipsLabel,1+ki,4,1,3,Qt::AlignLeft);
    //
    mainLyt -> addWidget(mSubsLabel,2+ki,1,Qt::AlignLeft);
    mainLyt -> addWidget(mSubsEdit ,2+ki,2,1,5);
    //
    mainLyt -> addWidget(mAttach   ,3+ki,2,Qt::AlignRight);
    mainLyt -> addWidget(mPhoto    ,3+ki,3,Qt::AlignLeft);
    //
    mainLyt -> addWidget(mCtntLabel,4+ki+kj,1,Qt::AlignTop|Qt::AlignLeft);
    mainLyt -> addWidget(mCtntEdit ,4+ki+kj,2,1,5);
    //
    mainLyt -> addWidget(mSend     ,5+ki+kj,4,Qt::AlignCenter);
    mainLyt -> addWidget(mSave     ,5+ki+kj,5,Qt::AlignRight);
    mainLyt -> addWidget(mQuit     ,5+ki+kj,6,Qt::AlignLeft);

    mainLyt -> setVerticalSpacing(10);
    mainLyt -> setColumnStretch(0,2);
    mainLyt -> setColumnStretch(1,1);
    mainLyt -> setColumnStretch(2,6);
    mainLyt -> setColumnStretch(3,12);
    mainLyt -> setColumnStretch(4,1);
    mainLyt -> setColumnStretch(5,1);
    mainLyt -> setColumnStretch(6,1);
    mainLyt -> setColumnStretch(7,2);
    mainLyt -> setRowStretch(0,1);
    for(int n=0;n<ki;n++)
    {
        mainLyt -> setRowStretch(1+n,1);
    }
    mainLyt -> setRowStretch(1+ki,1);
    mainLyt -> setRowStretch(2+ki,1);
    mainLyt -> setRowStretch(3+ki,1);
    for(int m=0;m<kj;m++)
    {
        mainLyt -> setRowStretch(4+ki+m,1);
    }
    mainLyt -> setRowStretch(4+ki+kj,12);
    mainLyt -> setRowStretch(5+ki+kj,1);
    for(int m=5+ki+kj;m<mainLyt->rowCount();m++)
    {
        mainLyt -> setRowStretch(m,0);
    }
    mainLyt -> setContentsMargins(0,30,0,15);
}

void WriteMailDlg::attachFile()
{
    QString fname;
    QString filepath = QFileDialog::getOpenFileName(this,QStringLiteral("添加附件"),".",\
            QStringLiteral("所有文件(*.*);;文本文件(*.txt);;HTML文件(*.html);;图片文件(*.jpeg *.jpg *.png)"));
    if(filepath != 0)
    {
        qDebug()<<filepath;
        QStringList qsl = filepath.split("/",QString::SkipEmptyParts);
        qDebug()<<qsl;
        fname = qsl.at(qsl.size()-1);
//        filepath.indexOf()
//        QFile file(filepath);
//        if(!file.open(QIODevice::ReadOnly))
//        {
//            QMessageBox::warning(this,QStringLiteral("警告"),QStringLiteral("无法打开文件\n")+filepath,QMessageBox::Yes);
//            return ;
//        }
        ifstream file;
        file.open(filepath.toLocal8Bit(),ios::binary|ios::in);
        if(!file){
            QMessageBox::warning(this,QStringLiteral("警告"),QStringLiteral("无法打开文件\n")+filepath,QMessageBox::Yes);
            return ;
        }
        stringstream  buf;
        buf << file.rdbuf();
        string content(buf.str());
        file.close();
        qDebug("%s",content.c_str());
        Contents ctns;
        ctns.type = 4;
        ctns.name = fname.toLocal8Bit();
        ctns.content = content;
        mCtnsDeque.push_back(ctns);
        fileName =fileName +"  "+ fname;
        battach = true;
        setLyt(mi,1);
    }
}
void WriteMailDlg::addPic()
{
    QString filepath = QFileDialog::getOpenFileName(this,QStringLiteral("添加附件"),".",\
            QStringLiteral("图片文件(*.jpeg *.jpg *.png)"));
    QStringList qsl = filepath.split("/",QString::SkipEmptyParts);
    fileName = qsl.at(qsl.size()-1);
    if(filepath != 0)
    {
        QString str = "<img src = "+filepath + ">";
        mCtntEdit -> append(str);
        ifstream file;
        file.open(filepath.toLocal8Bit(),ios::binary|ios::in);
        if(!file){
            QMessageBox::warning(this,QStringLiteral("警告"),QStringLiteral("无法打开文件\n")+filepath,QMessageBox::Yes);
            return ;
        }
        stringstream  buf;
        buf << file.rdbuf();
        string content(buf.str());
        Contents ctns;
        ctns.type = 3;
        ctns.name = fileName.toLocal8Bit();
        ctns.content = content;
        mCtnsDeque.push_back(ctns);
    }
}

void WriteMailDlg::addBcc()
{
    if(!bbci){
        setLyt(1,mj);
    }
    else{
        setLyt(3,mj);

    }
    bbci = !bbci;
}
void WriteMailDlg::addCC()
{
    if(!bcci){
        setLyt(2,mj);
    }
    else{
        setLyt(4,mj);
    }
    bcci = !bcci;
}
void WriteMailDlg::replaceSave()
{
    this -> readEdits();
    send2Draft(mMD);
}
void WriteMailDlg::setFlag()
{
    QString dstStr = dstr2QString(mMD.dstAddr,false);
    QString str;
    if(mDraftorMail){
        if(dstStr==mRecvEdit->text() && str.fromLocal8Bit(mMD.subject.c_str())==mSubsEdit->text() && cmpContents())
        {   mDraftEdited = false;}
        else
        {   mDraftEdited = true;}
    }
}

bool WriteMailDlg::cmpContents()
{
    Contents ctns;
    for(int i =0;i<mMD.contents.size();i++)
    {
        ctns = mMD.contents.at(i);
        switch (ctns.type) {
        case 1:
            if(QString::fromLocal8Bit(ctns.content.c_str()) != mCtntEdit -> toPlainText())
                return false;
            break;
        case 2:
            if(QString::fromLocal8Bit(ctns.content.c_str()) != mCtntEdit -> toHtml())
                return false;
            break;
        }
    }
    return true;
}

void WriteMailDlg::readEdits()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    Contents ctns;
    mMD.ID = "";
    mMD.srcAddr = setData[Account].toLocal8Bit();
    mMD.sender  = setData[usrName].toLocal8Bit();
    mMD.subject = mSubsEdit->text().toLocal8Bit();
    ctns.type = 1;  ////////
    ctns.name = ""; ////////
    ctns.content = mCtntEdit -> toPlainText().toStdString();
    mCtnsDeque.push_back(ctns);
    mMD.contents =  mCtnsDeque;
    mMD.time    = currentTime.toString("yyyy-MM-dd hh:mm:ss").toLocal8Bit();
    mMD.dstAddr=QString2dstr(mRecvEdit->text(),"a");
    deque<string> ds;
    string s;
    if(bbci){
        ds = QString2dstr(mBccEdit->text(),"c");
        while(!ds.empty()){
            s = ds.back();
            ds.pop_back();
            mMD.dstAddr.push_back(s);
        }
    }
    if(bcci){
        ds = QString2dstr(mCCEdit->text(),"b");
        while(!ds.empty()){
            s= ds.back();
            ds.pop_back();
            mMD.dstAddr.push_back(s);
        }
    }
    qDebug()<<dstr2QString(mMD.dstAddr,false);
}
void WriteMailDlg::openDraft(MailData &md)
{
    mMD = md;
    QString str;
    Contents ctns;
    mRecvEdit->setText(dstr2QString(md.dstAddr,false));
    mSubsEdit->setText(str.fromLocal8Bit(md.subject.c_str()));
    for(deque<Contents>::iterator it = md.contents.begin();it != md.contents.end();it++)
    {
        ctns = *it;
        switch (ctns.type) {
        case 1: //plian text
            mCtntEdit ->insertPlainText(str.fromLocal8Bit(ctns.content.c_str()));
            break;
        case 2: //html
            mCtntEdit ->insertHtml(str.fromLocal8Bit(ctns.content.c_str()));
            break;
        case 3: //image
            mCtntEdit -> append("< img src ="+QString::fromLocal8Bit(ctns.name.c_str()) + ">");
            break;
        case 4: //attach
            break;
        default:
            break;
        }
    }

    mDraftorMail = true;
    mDraftEdited = false;
}
void WriteMailDlg::sendEmail()
{
    this->readEdits();
    if(checkEdit())
    {
        QMessageBox::warning(this,QStringLiteral("信息为空"),QStringLiteral("未输入任何邮件信息！"),QMessageBox::NoButton);
        return;
    }
    /*
     * here is where the messages will be send;
     * SendingDlg.smtp send md to dstAddr;
     */
    SendingDlg dlg(mMD);

    if(dlg.exec() == QDialog::Accepted){
        send2Send(mMD);
        accept();
    }
}
void WriteMailDlg::saveDraft()
{
    this -> readEdits();
    appendBoxFile("draft.txt",mMD);
    QMessageBox::information(this,QStringLiteral("存草稿"),QStringLiteral("草稿保存成功"),QMessageBox::Ok);
}
void WriteMailDlg::save()
{

    bool editsEmpty = checkEdit();
    if(!mDraftorMail && editsEmpty)
        QMessageBox::warning(this,QStringLiteral("信息为空"),QStringLiteral("未输入任何邮件信息！"),QMessageBox::NoButton);
    else if(!mDraftorMail && !editsEmpty){
        this -> saveDraft();
        accept();
    }
    else if(mDraftorMail && !mDraftEdited){
        QMessageBox::warning(this,QStringLiteral("存草稿"),QStringLiteral("草稿保存成功"),QMessageBox::Ok);
        accept();
    }
    else{//草稿有编辑,是否被覆盖
        if(QMessageBox::warning(this,QStringLiteral("存草稿"),QStringLiteral("是否覆盖原草稿！"),QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
        {
            this->replaceSave();
            accept();
        }else{
            accept();
        }
    }
}
bool WriteMailDlg::checkEdit()
{
    if(mRecvEdit->text().size() == 0 && mSubsEdit->text().size() == 0 && mCtnsDeque.size()==0)
        return true;
    else
        return false;
}

void WriteMailDlg::closeEvent(QCloseEvent *event)
{
    if(mDraftorMail){
        accept();
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


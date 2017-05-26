#include "QMainWin.h"
#include <QApplication>
#include <QTextCodec>
#include <fstream>
#include <sstream>
QString filePath = "../csEmail/data";

int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("gbk");
    QTextCodec::setCodecForLocale(codec);
    QApplication a(argc, argv);
    QMainWin w;
    w.show();

    return a.exec();
}


bool readSetFile(QWidget *msgParent, QString str[],QList<QStringList> &qQsl)
{
    QStringList qsl;
    QString st;
    QFile file(filePath+"/settings.txt");
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::warning(msgParent,QStringLiteral("警告"),QStringLiteral("无法打开文件settings.txt"),QMessageBox::Yes);
        return false;
    }
    QDataStream stream(&file);
    int i;
    while (!stream.atEnd()) {
        i =0;
        while(i<9){
            stream >> st;
            qsl << st;
            i++;
        }
        qQsl << qsl;
    }

    i = 0;
    qsl = qQsl.at(0);
    while(i<9){
        str[i] = qsl.at(i);
        i++;
    }
    file.close();
    return true;
}

bool writeSetFile(QWidget *msgParent,QString str[],QList<QStringList> &qQsl)
{
    QFile file(filePath+"/settings.txt");
    if(!file.open(QIODevice::WriteOnly)){
        QMessageBox::warning(msgParent,QStringLiteral("警告"),QStringLiteral("无法打开文件settings.txt"),QMessageBox::Yes);
        return false;
    }
    QDataStream stream(&file);
    foreach (QStringList qsl, qQsl) {
        foreach (QString st, qsl) {
            stream << st;
        }
    }
    file.close();
    return true;
}

bool readBoxFile(QString filename,QList<MailData> &mdl)
{
    QFile file(filePath+"/"+filename);
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::warning(NULL,QStringLiteral("警告"),QStringLiteral("无法打开文件")+filename,QMessageBox::Yes);
        return false;
    }
    QDataStream stream(&file);
    mdl.clear();
    while(!stream.atEnd()){
        MailData md;
        md.read(stream);
        mdl << md;
    }
    file.close();
    //printmdl(mdl);
    return true;
}
bool writeBoxFile(QString filename, QList<MailData> &mdl)
{
    QFile file(filePath+"/"+filename);
    if(!file.open(QIODevice::WriteOnly)){
        QMessageBox::warning(NULL,QStringLiteral("警告"),QStringLiteral("无法打开文件")+filename,QMessageBox::Yes);
        return false;
    }
    QDataStream stream(&file);
    foreach (MailData md, mdl) {
        md.write(stream);
    }
    file.close();
    //printmdl(mdl);
    return true;
}

bool appendBoxFile(QString filename,MailData &md)
{
	QFile file(filePath+"/"+filename);
	if(!file.open(QIODevice::WriteOnly|QIODevice::Append))
	{
        QMessageBox::warning(NULL,QStringLiteral("警告"),QStringLiteral("无法打开文件")+filename,QMessageBox::Yes);
        return false;
	}
	QDataStream stream(&file);
	md.write(stream);
	file.close();
	return true;
}

void Contents::write(QDataStream &stream)
{
    QString str;
    stream << QString::number(type,10);
    stream << QString::fromLocal8Bit(name.c_str());
    stream << QString::fromLocal8Bit(content.c_str());
}
void Contents::read(QDataStream &stream)
{
    QString str;
    stream >> str;
    type = str.toInt();
    stream >> str;
    name = str.toLocal8Bit();
    stream >> str;
    content = str.toLocal8Bit();
}
void MailData::write(QDataStream &stream)
{
    QString str;
    Contents ctns;
    str = QString::fromLocal8Bit(ID.c_str());
    stream << QString::fromLocal8Bit(ID.c_str());
    str = QString::fromLocal8Bit(time.c_str());
    stream << QString::fromLocal8Bit(time.c_str());
    str = QString::fromLocal8Bit(srcAddr.c_str());
    stream << QString::fromLocal8Bit(srcAddr.c_str());
    str = dstr2QString(dstAddr,true);
    stream << dstr2QString(dstAddr,true);
    str = QString::fromLocal8Bit(sender.c_str());
    stream << QString::fromLocal8Bit(sender.c_str());
    str = QString::fromLocal8Bit(subject.c_str());
    stream << QString::fromLocal8Bit(subject.c_str());
    str = QString::number(contents.size(),10);
    stream << QString::number(contents.size(),10);
    qDebug()<<contents.size();
    for(deque<Contents>::iterator it = contents.begin();it != contents.end();it++)
    {
        ctns = *it;
        ctns.write(stream);
    }
}
void MailData::read(QDataStream &stream)
{
    QString str;
    Contents ctns;
    int size;
    stream >> str;
    ID = str.toLocal8Bit();
    stream >> str;
    time = str.toLocal8Bit();
    stream >> str;
    srcAddr = str.toLocal8Bit();
    stream >> str;
    dstAddr = QString2dstr(str);
    stream >> str;
    sender = str.toLocal8Bit();
    stream >> str;
    subject = str.toLocal8Bit();
    stream >> str;
    size = str.toInt();
    for(int i=0;i<size;i++)
    {
        ctns.read(stream);
        contents.push_back(ctns);
    }
}
void Contents::deContents(QString &str)
{
    ofstream file;
    QString pathName;
    switch (type) {
    case 1: //
        str = QString::fromLocal8Bit(content.c_str());
        break;
    case 2:
        str = QString::fromLocal8Bit(content.c_str());
        break;
    case 3:
        pathName = "../csEmail/FileRecv/"+QString::fromLocal8Bit(name.c_str());
        file.open(pathName.toLocal8Bit(),ios::binary|ios::out);
        if(!file){
            QMessageBox::warning(NULL,QStringLiteral("警告"),QStringLiteral("无法打开文件\n")+QString::fromLocal8Bit(name.c_str()),QMessageBox::Yes);
            return ;
        }
        file << content.c_str();
        file.close();
        str = "../csEmail/FileRecv/" + QString::fromLocal8Bit(name.c_str());
        break;
    case 4:
        str = QString::fromLocal8Bit(name.c_str());
        pathName = "../csEmail/FileRecv/"+QString::fromLocal8Bit(name.c_str());
        file.open(pathName.toLocal8Bit(),ios::binary|ios::out);
        if(!file){
            QMessageBox::warning(NULL,QStringLiteral("警告"),QStringLiteral("无法打开文件\n")+str,QMessageBox::Yes);
            return ;
        }
        file << content.c_str();
        file.close();
        break;
    default:
        break;
    }
}

QString dstr2QString(deque<string> &ds,bool sw) //sw = true 写入文件 sw = false 显示
{
    QStringList qsl;
    QString str;
    for(deque<string>::iterator it = ds.begin();it != ds.end();it++)
    {
        str = QString::fromStdString(*it);
        if(!sw)
            str = str.mid(1,str.size()-1);
        qsl << str;
    }
    str = qsl.join(";");
    return str;
}

deque<string> QString2dstr(QString &str,QString c)
{
    QStringList qsl = str.split(";",QString::SkipEmptyParts);
    QString tmp;
    deque<string> ds;
    for(QStringList::iterator it = qsl.begin();it != qsl.end();it++)
    {
        tmp = c + *it ;
        ds.push_back(tmp.toStdString());
    }
    return ds;
}


void printmdl(QList<MailData> &mdl)
{
    Contents ctns;
    foreach (MailData md, mdl) {
        qDebug("####################################");
        qDebug("ID:%s\ntime:%s\nsrcAddr:%s\nsender:%s",md.ID.c_str(),md.time.c_str(),md.srcAddr.c_str(),md.sender.c_str());
        qDebug()<<"dstAddr:"<<dstr2QString(md.dstAddr,false);
        qDebug()<<"subject:"<<QString::fromLocal8Bit(md.subject.c_str());
        qDebug()<<"content.size:"<<md.contents.size();
        for(deque<Contents>::iterator it = md.contents.begin();it != md.contents.end();it++)
        {
            ctns = *it;
            qDebug()<<"type:"<<it->type;
            qDebug("name:%s",ctns.name.c_str());
            qDebug()<<"contents:"<<QString::fromLocal8Bit(ctns.content.c_str());
        }
        qDebug("###################################");
    }
}


//bool Time::toQString(QString &str)
//{
//    str = QString::number(year,10)+"-"+QString::number(month,10)+"-"+QString::number(day,10) \
//            + " " + QString::number(hour,10) + ":" + QString::number(min,10) + ":" + QString::number(sec,10);
//    return true;
//}
//bool Time::fromQString(QString &str)
//{
//    QDateTime dateTime = QDateTime::fromString(str,"yyyy-MM-dd hh:mm:ss");
//    year = dateTime.date().year();
//    month= dateTime.date().month();
//    day  = dateTime.date().day();
//    hour = dateTime.time().hour();
//    min  = dateTime.time().minute();
//    sec  = dateTime.time().second();
//    return true;
//}


//QStringList Contents::toQStringList()
//{
//    QString str;
//    QStringList qsl;
//    str = QString::number(type,10);
//    qsl << str;
//    qsl << str.fromStdString(name);
//    qsl << str.fromStdString(content);
//    return qsl;
//}
//Contents &Contents::formQStringList(QStringList qsl)
//{
//    this->type = qsl.at(0).toInt();
//    this->name = qsl.at(1).toStdString();
//    this->content = qsl.at(2).toStdString();
//    return *this;
//}

//QList<QStringList> MailData::toQListQStringList()
//{
//    QList<QStringList> qQsl;
//    QStringList qsl,ltmp;
//    QString str;
//    Contents ctns;
//    qsl << str.fromStdString(time);
//    qsl << str.fromStdString(srcAddr);

//    for(deque<string>::iterator it = dstAddr.begin();it != dstAddr.end();it++)
//        ltmp << str.fromStdString(*it);
//    str = ltmp.join(";");
//    qsl << str;

//    qsl << str.fromStdString(sender);
//    qsl << str.fromStdString(subject);
//    qQsl << qsl;

//    //qsl << str.fromStdString(contents);
//    for(deque<Contents>::iterator it = contents.begin();it != contents.end();it++)
//    {
//        ctns = *it;
//        qQsl << ctns.toQStringList();
//    }
//    return qQsl;
//}

//MailData &MailData::fromQListQStringList(QList<QStringList> &qQsl)
//{
//    QStringList qsl;
//    QString str;
//    Contents ctns;
//    qsl = qQsl.at(0);
//    time = qsl.at(0).toStdString();
//    srcAddr = qsl.at(1).toStdString();
//    sender  = qsl.at(3).toStdString();
//    subject = qsl.at(4).toStdString();

//    str = qsl.at(2);
//    qsl = str.split(";",QString::SkipEmptyParts);
//    foreach (QString dst, qsl) {
//        dstAddr.push_back(dst.toStdString());
//    }

//    for(QList<QStringList>::iterator it = qQsl.begin()+1;it != qQsl.end();it++)
//    {
//        qsl = *it;
//        contents.push_back(ctns.formQStringList(qsl));
//    }
//    return *this;
//}

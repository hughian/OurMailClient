#include "QMainWin.h"
#include <QApplication>
QString filePath = "../csEmail/data";
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWin w;
    w.show();

    return a.exec();
}


bool readSetFile(QWidget *msgParent, QString str[])
{
    QFile file(filePath+"/settings.txt");
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::warning(msgParent,QStringLiteral("警告"),QStringLiteral("无法打开文件settings.txt"),QMessageBox::Yes);
        return false;
    }
    QDataStream stream(&file);
    int i=0;
    while(i<8){
        stream >> str[i++];
    }
    file.close();
    return true;
}
bool readBoxFile(QString filename,QList<QStringList> &Qqsl)
{
    QFile file(filePath+"/"+filename);
    QStringList qsl;
    QString str;
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::warning(NULL,QStringLiteral("警告"),QStringLiteral("无法打开文件")+filename,QMessageBox::Yes);
        return false;
    }
    QDataStream stream(&file);
    Qqsl.clear();
    while(!stream.atEnd()){
        stream >> str;
        qsl = str.split("\n");
        str = qsl.at(4);
        str.replace("$#$","\n");
        qsl.replace(4,str);
        Qqsl << qsl;
    }
    file.close();
    return true;
}
bool writeBoxFile(QString filename,QList<QStringList> &Qqsl)
{
    QFile file(filePath+"/"+filename);
    QStringList qsl;
    QString str;
    if(!file.open(QIODevice::WriteOnly)){
        QMessageBox::warning(NULL,QStringLiteral("警告"),QStringLiteral("无法打开文件")+filename,QMessageBox::Yes);
        return false;
    }
    QDataStream stream(&file);
    for(QList<QStringList>::iterator it = Qqsl.begin();it != Qqsl.end();it++)
    {
        qsl = *it;
        str = qsl.at(4);
        str.replace("\n","$#$");
        qsl.replace(4,str);
        str = qsl.join("\n");
        stream << str;
    }
    file.close();
    return true;
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
bool MailData::toQStringList(QStringList &qsl)
{
    QStringList ltmp;
    QString stmp;
    qsl << stmp.fromStdString(srcAddr);

    for(deque<string>::iterator it = dstAddr.begin();it != dstAddr.end();it++)
        ltmp << stmp.fromStdString(*it);
    stmp = ltmp.join(";");
    qsl << stmp;

    qsl << stmp.fromStdString(sender);
    qsl << stmp.fromStdString(subject);
    //qsl << stmp.fromStdString(contents);
    qsl << stmp.fromStdString(time);
    return true;
}

MailData& MailData::fromQStringList(QStringList &qsl)
{
    QStringList qsltmp;
    QString str;
    srcAddr = qsl.at(0).toStdString();
    qsltmp = qsl.at(1).split(";",QString::SkipEmptyParts);
    for(QStringList::iterator it = qsltmp.begin();it != qsl.end();it++){
        str = *it;
        dstAddr.push_back(str.toStdString());
    }
    sender = qsl.at(2).toStdString();
    subject = qsl.at(3).toStdString();
    //contents = qsl.at(4).toStdString();
    time  = qsl.at(5).toStdString();
    return *this;
}

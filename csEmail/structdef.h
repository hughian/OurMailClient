#ifndef STRUCTDEF_H
#define STRUCTDEF_H
#include <string>
#include <deque>
#include <QString>
#include <QStringList>
using namespace std;
//struct Time{
//    int year;
//    int month;
//    int day;
//    int hour;
//    int min;
//    int sec;
//    bool toQString(QString &);
//    bool fromQString(QString &);
//};

struct Contents
{
    /*内容类型
    * 1--text/plain //此类型没有内容名
    * 2--text/html
    * 3--image
    * 4--附件
    */
    int type;
    string name;    //内容名
    string content; //内容
    QStringList toQSList();
    Contents &formQSList(QStringList qsl);
};
struct MailData{
    string srcAddr;
    deque<string> dstAddr;
    string sender;
    string subject;
    deque<Contents> contents;// 邮件内容
    string time;
    bool   toQStringList(QStringList &);
    MailData&   fromQStringList(QStringList &);
};
#endif // STRUCTDEF_H

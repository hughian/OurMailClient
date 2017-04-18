#ifndef STRUCTDEF_H
#define STRUCTDEF_H
#include <string>
#include <deque>
#include <QString>
#include <QStringList>
using namespace std;
struct Time{
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
    bool toQString(QString &);
    bool fromQString(QString &);
};
struct MailData{
    string srcAddr;
    deque<string> dstAddr;
    string sender;
    string subject;
    string contents;
    Time   time;
    bool   toQStringList(QStringList &);
    MailData&   fromQStringList(QStringList &);
};
#endif // STRUCTDEF_H

#ifndef STRUCTDEF_H
#define STRUCTDEF_H
#include <string>
#include <deque>
using namespace std;
struct Time{
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
};
struct MailDate{
    string srcAddr;
    deque<string> dstAddr;
    string sender;
    string subject;
    string contents;
    Time   time;
};
#endif // STRUCTDEF_H

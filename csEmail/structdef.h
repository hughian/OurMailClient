#ifndef STRUCTDEF_H
#define STRUCTDEF_H
#include <string>
#include <deque>
#include <QDataStream>
using namespace std;
//
//struct Time
//{//年/月/日/时/分/秒
//	int year;
//	int month;
//	int day;
//	int hour;
//	int min;
//	int sec;
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
	/*内容名*/
	string name;
	/*内容*/
	string content;
    void write(QDataStream &stream);
    void read(QDataStream &stream);
};
struct MailData
{
	string ID;//邮件标识
	string srcAddr; //发送地址
	deque<string> dstAddr;/*目的地址列表,其中,首字符为判定字符,a--普通地址,b--抄送地址,c--密送地址*/
	string sender;// 发送者姓名
	string subject;// 邮件主题
	deque<Contents> contents;// 邮件内容
	string time;//邮件时间
    void write(QDataStream &stream);
    void read(QDataStream &stream);

};
QString dstr2QString(deque<string> &ds);
deque<string> QString2dstr(QString &str,int sw = 0);

#endif

/*
* author: iyuge2
* create-time: 2017/04/15 20:20
* update-time:
* function: define smtp header file
*/
#ifndef _MYPOP_H
#define _MYPOP_H
#include <string>
#include <list>
#include <string.h>
#include <winsock.h>
#include <windows.h>
#include <cstdio>
#include <iostream>
#include "MySocket.h"
#include "MyBase64.h"
#include "MyQuotedPrintable.h"
#include "structdef.h"

#pragma comment(lib,"ws2_32.lib")

using namespace std;

class MyPop:public MySocket
{
private:
	const string user;
	const string passwd;
	const string server;
	const int Port;
private:
	bool IsOk();
	bool Send(const string msg);/*发送信息*/
	bool Send(const char *buf);
//signals:
//	void sendStr(string m);
public:
	MyPop(const string server,const int port,const string user,const string passwd):MySocket(),
			user(user),passwd(passwd),server(server),Port(port){};
	virtual ~MyPop() {ReleaseSocket();};
	bool Connect();//连接服务器
	bool ConfirmUser();//确认用户
	bool GetAllMails(list<MailData>& svecMails,int deleteOp);//获取邮件,deleteOp==1(删除服务器邮件)
	bool DecodeMail(MailData &CurrentMail, const string revData);
	string UTF8_To_GBK(const string & str);//UTF8转GBK
	string GBK_To_UTF8(const string &str);//GBK转UTF8
	void Print(MailData serMail);
};
#endif

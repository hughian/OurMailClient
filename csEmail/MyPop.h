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
#include "MySocket.h"
#include "MyBase64.h"
#include "MyQuotedPrintable.h"
#include "structdef.h"

#pragma comment(lib,"ws2_32.lib")

using namespace std;

class MyPop:public MySocket
{
private:
	bool IsOk();
	void Print(MailData serMail);
public:
	MyPop():MySocket(){};
	virtual ~MyPop() {};
	bool Connect(const string Serv, const int Port);
	bool ConfirmUser(const string account, const string passwd);
	bool GetAllMails(list<MailData>& svecMails);
	bool DecodeMail(MailData &CurrentMail,const string revData);
	string UTF8_To_GBK(const string & str);
	string GBK_To_UTF8(const string &str);
};
#endif

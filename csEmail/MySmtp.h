/*
* author: iyuge2
* create-time: 2017/04/13 20:07
* update-time:
* function: define smtp header file
*/
#ifndef _MYSTMP_H
#define _MYSTMP_H

#include <string>
#include <deque>
#include <windows.h>
#include <winsock.h>
#include "MySocket.h"
#include "MyBase64.h"
#include "structdef.h"

#pragma comment(lib,"ws2_32.lib")

using namespace std;

class MySmtp:public MySocket
{
private:
	bool TellResponse(const char *ReturnCode);//判断返回码
public:
	MySmtp():MySocket() {};
	virtual ~MySmtp() {};
	bool Connect(const string Serv, const int Port);
	bool ConfirmUser(const string userName, const string password);//验证用户名和密码
	bool SendMail(const MailData sendMail);//发送邮件
	/*
	备注:SMTP协议的返回状态信息
		211 帮助返回系统状态
		214 帮助信息
		220 服务准备就绪
		221 关闭连接
		235 用户验证成功
		250 请求操作就绪
		251 用户不在本地，转寄到其他路径
		334 等待用户输入验证信息
		354 开始邮件输入
		421 服务不可用
		450 操作未执行，邮箱忙
		451 操作中止，本地错误
		452 操作未执行，存储空间不足
		500 命令不可识别或语言错误
		501 参数语法错误
		502 命令不支技
		503 命令顺序错误
		504 命令参数不支持
		535 验证失败
		550 操作未执行，邮箱不可用
		551 非本地用户
		552 中止存储空间不足
		553 操作未执行，邮箱名不正确
		554 传输失败
	*/
};

#endif


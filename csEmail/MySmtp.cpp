/*
* author: iyuge2
* create-time: 2017/04/13 20:25
* update-time:
* function: complete smtp class
*/
#include"MySmtp.h"
#include<iostream>

bool MySmtp::TellResponse(const char *ReturnCode)
{
	char Buf[256] = { 0 };
	if (recv(mySocket,Buf,1024,0) == SOCKET_ERROR)
		return FALSE;
	Sleep(50);
	std::cout << Buf << endl;
	return (ReturnCode[0] == Buf[0] &&
		ReturnCode[1] == Buf[1] &&
		ReturnCode[2] == Buf[2]) ? TRUE : FALSE;
}

bool MySmtp::Connect(const string Serv, const int Port)
{
	if (!MySocket::Connect(Serv, Port))//连接服务器
	{
		return FALSE;
	}
	//检查服务器是否就绪
	if (!TellResponse("220"))
		return FALSE;
	//向服务器发送"HELO "+服务器名
	string strTemp = "HELO " + Serv + "\r\n";
	if (send(mySocket, strTemp.c_str(), strTemp.length(), 0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return FALSE;
	}
	//检查请求操作是否就绪
	if (!TellResponse("250"))
		return FALSE;
	return TRUE;
}

bool MySmtp::ConfirmUser(const string userName, const string password)
{
	MyBase64 base64;

	//发送"AUTH LOGIN"
	if (send(mySocket, "AUTH LOGIN\r\n", strlen("AUTH LOGIN\r\n"), 0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return false;
	}
	if (!TellResponse("334")) 
		return false;//等待用户输入验证信息

	//发送经base64编码的用户名
	string strSendemail = base64.Encode((const unsigned char*)userName.c_str(), userName.length()) + "\r\n";
	if (send(mySocket, strSendemail.c_str(), strSendemail.length(), 0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return false;
	}
	if (!TellResponse("334"))
		return false;

	//发送经base64编码的密码
	string strPassword = base64.Encode((unsigned char *)password.c_str(), password.length()) + "\r\n";
	if (send(mySocket, strPassword.c_str(), strPassword.length(), 0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return false;
	}
	if (!TellResponse("235"))
		return false;//用户验证失败
	return true;
}

bool MySmtp::SendMail(const MailData sendMail) // 邮件内容
{
	if(sendMail.srcAddr.empty())//判断发送地址是否为空
		return false;
	if (sendMail.dstAddr.size() <= 0)//判断目的地址列表是否为空
		return false;

	string strTmp;
	//发送MAIL FROM:<abc@xyz.com>
	strTmp = "MAIL FROM:<" + sendMail.srcAddr + ">\r\n";
	if (send(mySocket,strTmp.c_str(),strTmp.length(),0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return false;
	}
	if (!TellResponse("250"))
		return false;

	//逐个甄别目的地址
	for (unsigned int i = 0; i < sendMail.dstAddr.size(); i++)
	{
		strTmp = "RCPT To:<" + sendMail.dstAddr[i] + ">\r\n";
		if (send(mySocket,strTmp.c_str(),strTmp.length(),0) == SOCKET_ERROR)
		{
			ReleaseSocket();
			return false;
		}
		if (!TellResponse("250"))
			return false;
	}

	//发送"DATA\r\n"
	if (send(mySocket,"DATA\r\n",strlen("DATA\r\n"),0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return false;
	}
	if (!TellResponse("354"))
		return false;

	//"Mail From:Sendname<xxx@mail.com>\r\n"
	strTmp = "From:" + sendMail.sender + "<" + sendMail.srcAddr + ">\r\n";

	//"Subject: 邮件主题\r\n"
	strTmp += "Subject:" + sendMail.subject + "\r\n";

	//先将HEADER部分发送过去
	if (send(mySocket,strTmp.c_str(),strTmp.length(),0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return false;
	}
	//邮件主体
	//邮件内容
	//strTmp = sendMail.contents + "\r\n\r\n";
	strTmp = "hello\r\n\r\n";

	//将邮件内容发送出去
	if (send(mySocket,strTmp.c_str(),strTmp.length(), 0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return false;
	}

	//界尾，以"."为结束标志
	strTmp += "\r\n.\r\n";

	if (send(mySocket,strTmp.c_str(),strTmp.length(),0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return false;
	}
	if (!TellResponse("250"))
	{
		ReleaseSocket();
		return false;
	}
	ReleaseSocket();
	return true;
}

/*
* author: iyuge2
* create-time: 2017/04/15 20:39
* update-time:
* function: define smtp header file
*/
#include "MyPop.h"
#include "structdef.h"
#include <iostream>

#define BUF_LENTH 1024

bool MyPop::IsOk()
{
	char Buf[1024] = { 0 };
	if (recv(mySocket, Buf, 1024, 0) == SOCKET_ERROR)
		return false;
	Sleep(50);
	std::cout << Buf << endl;
	return (strncmp(Buf, "+OK", 3)) ? FALSE : TRUE;
}

bool MyPop::Connect(const string Serv, const int Port)
{
	if (!MySocket::Connect(Serv, Port))//连接服务器
	{
		return FALSE;
	}
	//检查服务器是否就绪
	if (IsOk())
		return TRUE;
	return FALSE;
}

bool MyPop::ConfirmUser(const string user, const string passwd)
{
	string strTemp = "USER " + user + "\r\n";
	if (send(mySocket, strTemp.c_str(), strTemp.length(), 0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return FALSE;
	}
	// 检测user
	if (!IsOk())
	{
		ReleaseSocket();
		return FALSE;
	}
	//strTemp.erase(strTemp.begin(), strTemp.end());
	strTemp = "pass " + passwd + "\r\n";
	if (send(mySocket, strTemp.c_str(), strTemp.length(), 0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return FALSE;
	}
	// 检测passwd
	if (!IsOk())
	{
		ReleaseSocket();
		return FALSE;
	}
	return TRUE;
}

bool MyPop::GetAllMails(list<MailData>& svecMails)
{
	char buf[BUF_LENTH] = { 0 };
	sprintf(buf, "STAT\r\n");
	if (send(mySocket, buf, strlen(buf), 0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return FALSE;
	}
	// 从服务器接收信息写入mailTemp中
	if (recv(mySocket, buf, BUF_LENTH, 0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return false;
	}
	cout << buf << endl;
	if (strncmp(buf, "+OK", 3))
	{
		return FALSE;
	}
	// 获取邮件总数
	int nMails = 0;
	for (unsigned int i = 4; i < strlen(buf); ++i)
	{
		if (buf[i] >= '0' && buf[i] <= '9')
		{
			nMails = nMails * 10 + (buf[i] - '0');
		}
		else
			break;
	}
	//开始接收所有的邮件
	for (int j = 1; j <= nMails; ++j)
	{
		cout << "邮件: " << j << endl;
		sprintf(buf, "RETR %d\r\n", j);
		if (send(mySocket, buf, strlen(buf) , 0) == SOCKET_ERROR)//第三个参数不能乱写啊!!!
		{
			ReleaseSocket();
			return false;
		}
		cout << buf;
		//开始接收第j封邮件
		//一直接收直到接收到的最后的三个字符为遇到".\r\n"
		int len = 0;
		string ctemp(""),endTemp("");
		while (endTemp != ".\r\n")
		{
			if ((len = recv(mySocket, buf, BUF_LENTH - 1, 0)) == SOCKET_ERROR)
			{
				ReleaseSocket();
				return FALSE;
			}
			buf[len] = '\0';
			ctemp += buf;
			endTemp = ctemp.substr(ctemp.length() - 3,3);
		}

		MyBase64 base64;
		int pos1 = 0, pos2 = 0,pos3 = 0;
		while ((pos1 = ctemp.find("?B?", pos1)) != -1)/*对?B?进行解码*/
		{
			pos3 = ctemp.rfind("=?", pos1) - 1;
			pos2 = ctemp.find("?=", pos1);
			string stemp = ctemp.substr(pos1+3, pos2 - pos1 - 3);
			stemp = UTF8_To_GBK(stemp);
			stemp = base64.Decode(stemp.c_str(), stemp.length(), len);
			ctemp.replace(pos3, pos2 - pos3 + 3, stemp);
			pos1 = pos3;
		}
		pos1 = 0;
		while ((pos1 = ctemp.find("?b?", pos1)) != -1)/*对?b?进行解码*/
		{
			pos3 = ctemp.rfind("=?", pos1) - 1;
			pos2 = ctemp.find("?=", pos1);
			string stemp = ctemp.substr(pos1 + 3, pos2 - pos1 - 3);
			stemp = UTF8_To_GBK(stemp);
			stemp = base64.Decode(stemp.c_str(), stemp.length(), len);
			ctemp.replace(pos3, pos2 - pos3 + 3, stemp);
			pos1 = pos3;
		}
		//cout << ctemp.substr(0,10000);      
		MailData MailTemp;
		DecodeMail(MailTemp, ctemp);
		Print(MailTemp);
		svecMails.push_back(MailTemp);
	}
	sprintf(buf, "QUIT\r\n");
	send(mySocket, buf, strlen(buf), 0);
	ReleaseSocket();
	return TRUE;
}

bool MyPop::DecodeMail(MailData &CurrentMail, const string revData)
{
	//获取发送者姓名与发送者地址
	int pos1 = 0, pos2 = 0, pos3 = 0;
	if ((pos1 = revData.find("\r\nFrom:", pos1)) != -1)
	{
		//pos2 = pos1 + 6;
		//while (revData[pos2] != '<')
		//{
		//	pos2++;
		//}
		if ((pos2 = revData.find("<", pos1)) != -1)
		{
			CurrentMail.sender = revData.substr(pos1 + 7, pos2 - pos1 - 7);
			if ((pos3 = revData.find(">", pos1)) != -1)
			{
				CurrentMail.srcAddr = revData.substr(pos2 + 1, pos3 - pos2 - 1);
			}
		}
	}
	//获取邮件主题
	if ((pos1 = revData.find("\r\nSubject:", pos1)) != -1)
	{
		pos1 += string("\r\nSubject:").length();
		if ((pos2 = revData.find("\r\n", pos1)) != -1)
		{
			CurrentMail.subject = revData.substr(pos1, pos2 - pos1);
		}
	}
	//获取邮件时间
	if ((pos1 = revData.find("\r\nDate:", pos1)) != -1)
	{
		if (((pos2 = revData.find(" +0800", pos1)) != -1) || ((pos2 = revData.find(" +0000", pos1)) != -1))
		{
			CurrentMail.time = revData.substr(pos1 + 7, pos2 - pos1 - 7);
		}
	}
	//获取邮件内容
	int len = 0;
	while ((pos1 = revData.find("Content-Type:", pos1)) != -1)
	{
		pos1 += string("Content-Type: ").length();
		pos2 = revData.find(";", pos1);
		if (pos2 < pos1)
		{
			break;
		}
		string MainType = revData.substr(pos1, pos2 - pos1);
		if (MainType.substr(0, 9) == "multipart")
		{
			continue;
		}
		else
		{
			Contents currentContent;
			if (MainType == "text/plain")
			{
				currentContent.type = 1;
			}
			else if (MainType == "text/html")
			{
				currentContent.type = 2;
			}
			else if (MainType.substr(0, 5) == "image")
			{
				currentContent.type = 3;
				if ((pos2 = revData.find("Content-ID: <", pos2)) != -1)
				{
					pos2 += string("Content-ID: <").length();
					pos3 = revData.find(">", pos1);
					if (pos3 > pos2)
					{/*记录图片ID*/
						currentContent.name = revData.substr(pos2, pos3 - pos2);
					}
				}
			}
			else if (MainType.substr(0, 11) == "application")
			{
				currentContent.type = 4;
				if ((pos2 = revData.find("name=", pos2)) != -1)
				{
					pos2 += string("name=").length();
					pos3 = revData.find("\r\nContent-Disposition:", pos1);
					if (pos3 > pos2)
					{/*记录application附件ID*/
						currentContent.name = revData.substr(pos2, pos3 - pos2);
					}
				}
			}
			else
			{
				continue;
			}
			/*获取内容体*/
			if ((pos2 = revData.find("Content-Transfer-Encoding:", pos1)) != -1)
			{
				pos2 += string("Content-Transfer-Encoding: ").length();
				pos3 = revData.find("\r\n", pos2);
				string Code = revData.substr(pos2, pos3 - pos2);
				if (Code == "base64")
				{
					pos2 = revData.find("\r\n\r\n", pos2);
					pos3 = revData.find("\r\n\r\n", pos2 + 4);
					if (pos3 > pos2)
					{
						string stemp = revData.substr(pos2 + 4, pos3 - pos2 - 4);
						MyBase64 base64;
						currentContent.content = base64.Decode(stemp.c_str(), stemp.length(), len);
					}
				}
				else if (Code == "quoted-printable")
				{
					pos2 = revData.find("\r\n\r\n", pos2);
					pos3 = revData.find("\r\n\r\n", pos2 + 4);
					if (pos3 > pos2)
					{
						string stemp = revData.substr(pos2 + 4, pos3 - pos2 - 4);
						MyQuotedPrintable myQuote;
						currentContent.content = myQuote.Decode(stemp);
					}
				}
				else
				{
					continue;
				}
			}
			CurrentMail.contents.push_back(currentContent);
		}	
	}
	return TRUE;
}

void MyPop::Print(MailData serMail)
{
	cout << "From: " << serMail.sender << endl;
	cout << "srcAddr: " << serMail.srcAddr << endl;
	cout << "Subject: " << serMail.subject << endl;
	cout << "Data: " << serMail.time << endl;
	for (unsigned int i = 0; i < serMail.contents.size(); i++)
	{
		int type = serMail.contents[i].type;
		cout << "type: " << type << endl;
		if (type == 3 || type == 4)
			cout << "name: " << serMail.contents[i].name << endl;
		else
			cout << "contents: " << serMail.contents[i].content << endl;
	}
}

string MyPop::UTF8_To_GBK(const std::string & str)
{
	cout << str.length() << endl;
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	cout << nwLen << endl;
	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴
	memset(pwBuf, 0, nwLen * 2 + 2);

	MultiByteToWideChar(CP_UTF8, 0,str.c_str(), -1, pwBuf, nwLen);

	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, 0, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	memset(pBuf, 0, nLen + 1);

	WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, pBuf, nLen, NULL, NULL);

	string retStr(pBuf);
	delete[]pBuf;
	delete[]pwBuf;
	return retStr;
}

string MyPop::GBK_To_UTF8(const string &str)
{
	wchar_t *str1;
	int n = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	str1 = new wchar_t[n];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, str1, n);
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char *str2 = new char[n];
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
	string strOutUTF8(str2);
	delete[]str1;
	delete[]str2;
	return strOutUTF8;
}

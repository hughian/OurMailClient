#include "MyPop.h"

#define BUF_LENTH 1024
#define MAIL_LENTH 102400

void MyPop::sendStr(string m)
{
	cout << m << endl;
}

bool MyPop::Send(const string msg)
{
	sendStr(msg);
	if (send(mySocket, msg.c_str() , msg.length(), 0) == SOCKET_ERROR)
	{
		return FALSE;
	}
	return TRUE;
}

bool MyPop::Send(const char* buf)
{
	sendStr(string(buf));
	if (send(mySocket,buf,strlen(buf), 0) == SOCKET_ERROR)
	{
		return FALSE;
	}
	return TRUE;
}

bool MyPop::IsOk()
{
	char Buf[1024] = { 0 };
	if (recv(mySocket, Buf, 1024, 0) == SOCKET_ERROR)
		return false;
	Sleep(50);
	sendStr(string(Buf));
	return (strncmp(Buf, "+OK", 3)) ? FALSE : TRUE;
}

bool MyPop::Connect()
{
	if (!MySocket::Connect(server, Port))//���ӷ�����
	{
		return FALSE;
	}
	//���������Ƿ����
	if (IsOk())
		return TRUE;
	return FALSE;
}

bool MyPop::ConfirmUser()
{
	string strTemp = "USER " + user + "\r\n";
	if (Send(strTemp) == FALSE)
	{
		return FALSE;
	}
	// ���user
	if (!IsOk())
	{
		return FALSE;
	}
	strTemp = "pass " + passwd + "\r\n";
	if (Send(strTemp) == FALSE)
	{
		return FALSE;
	}
	// ���passwd
	if (!IsOk())
	{
		return FALSE;
	}
	return TRUE;
}

bool MyPop::GetAllMails(list<MailData>& svecMails,int deleteOp)
{
	char buf[BUF_LENTH] = { 0 };
	string strTemp = "STAT\r\n";
	if (Send(strTemp) == FALSE)
	{
		return FALSE;
	}
	// �ӷ�����������Ϣд��buf��
	if (recv(mySocket, buf, BUF_LENTH, 0) == SOCKET_ERROR)
	{
		return false;
	}
	sendStr(string(buf));
	if (strncmp(buf, "+OK", 3))
	{
		return FALSE;
	}
	// ��ȡ�ʼ�����
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
	//��ʼ�������е��ʼ�
	for (int j = 1; j <= nMails; ++j)
	{
		sprintf(buf, "RETR %d\r\n", j);//��ȡ���ʼ�ȫ������
		if (Send(buf) == FALSE)
		{
			return FALSE;
		}
		//һֱ����ֱ�����յ������������ַ�Ϊ����".\r\n"
		int len = 0;
		char Buf[MAIL_LENTH + 1];
		string ctemp = "",endTemp = "";
		while (endTemp != ".\r\n")
		{
			if ((len = recv(mySocket, Buf, MAIL_LENTH, 0)) == SOCKET_ERROR)
			{
				return FALSE;
			}
			Buf[len] = '\0';
			ctemp += Buf;
			endTemp = ctemp.substr(ctemp.length() - 3, 3);
		}
		if (deleteOp)
		{
			sprintf(buf, "DELE %d\r\n", j);//ɾ�����ʼ�
			if (Send(buf) == FALSE)
			{
				return FALSE;
			}
		}
		MyBase64 base64;
		int pos1 = 0, pos2 = 0, pos3 = 0;
		while ((pos1 = ctemp.find("?B?", pos1)) != -1)/*��?B?���н���*/
		{
			pos3 = ctemp.rfind("=?", pos1) - 1;
			pos2 = ctemp.find("?=", pos1);
			string stemp = ctemp.substr(pos1 + 3, pos2 - pos1 - 3);
			stemp = UTF8_To_GBK(stemp);
			stemp = base64.Decode(stemp.c_str(), stemp.length(), len);
			ctemp.replace(pos3, pos2 - pos3 + 3, stemp);
			pos1 = pos3;
		}
		pos1 = 0;
		while ((pos1 = ctemp.find("?b?", pos1)) != -1)/*��?b?���н���*/
		{
			pos3 = ctemp.rfind("=?", pos1) - 1;
			pos2 = ctemp.find("?=", pos1);
			string stemp = ctemp.substr(pos1 + 3, pos2 - pos1 - 3);
			stemp = UTF8_To_GBK(stemp);
			stemp = base64.Decode(stemp.c_str(), stemp.length(), len);
			ctemp.replace(pos3, pos2 - pos3 + 3, stemp);
			pos1 = pos3;
		}
		MailData MailTemp;
		DecodeMail(MailTemp, ctemp);
		svecMails.push_back(MailTemp);
	}
	strTemp = "QUIT\r\n";
	if (Send(strTemp) == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

bool MyPop::DecodeMail(MailData &CurrentMail, const string revData)
{
	int pos1 = 0, pos2 = 0, pos3 = 0,pos4 = 0;
	//��ȡ�����������뷢���ߵ�ַ
	//cout << revData;
	if ((pos1 = revData.find("\nFrom:", pos1)) != -1)
	{
		pos1 += string("\nFrom:").length();
		if ((pos4 = revData.find("\r\nTo:", pos1)) != -1)
		{
			if ((pos2 = revData.find("<", pos1)) != -1)
			{
				if (pos2 < pos4)
				{
					CurrentMail.sender = revData.substr(pos1, pos2 - pos1);
					if ((pos3 = revData.find(">", pos1)) != -1)
					{
						CurrentMail.srcAddr = revData.substr(pos2 + 1, pos3 - pos2 - 1);
					}
				}
				else
				{
					CurrentMail.srcAddr = revData.substr(pos1, pos4 - pos1);
				}
			}
			else
			{
				CurrentMail.srcAddr = revData.substr(pos1, pos4 - pos1);
			}
		}
	}
	//��ȡ�ʼ�����
	if ((pos1 = revData.find("\nSubject:", pos1)) != -1)
	{
		pos1 += string("\nSubject:").length();
		if (((pos2 = revData.find("\nMime-Version:", pos1)) != -1) || ((pos2 = revData.find("\nMIME-Version:", pos1)) != -1))
		{
			CurrentMail.subject = revData.substr(pos1, pos2 - pos1);
		}
	}
	//��ȡ�ʼ�ʱ��
	if ((pos2 = revData.find("\nDate:", pos1)) != -1)
	{
		if (((pos3 = revData.find(" +0800", pos2)) != -1) || ((pos3 = revData.find(" +0000", pos2)) != -1))
		{
			CurrentMail.time = revData.substr(pos2 + 6, pos3 - pos2 - 6);
		}
	}
	CurrentMail.ID = "";
	//��ȡ�ʼ�����
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
					{/*��¼ͼƬID*/
						currentContent.name = revData.substr(pos2, pos3 - pos2);
					}
				}
			}
			else if (MainType.substr(0, 11) == "application")
			{
				currentContent.type = 4;
				if ((pos2 = revData.find("name=\"", pos2)) != -1)
				{
					pos2 += string("name=\"").length();
					pos3 = revData.find("\"", pos2);
					if (pos3 > pos2)
					{/*��¼application����ID*/
						currentContent.name = revData.substr(pos2, pos3 - pos2);
					}
				}
			}
			else
			{
				continue;
			}
			/*��ȡ������*/
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
	wchar_t * pwBuf = new wchar_t[nwLen + 1];//һ��Ҫ��1����Ȼ�����β��
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

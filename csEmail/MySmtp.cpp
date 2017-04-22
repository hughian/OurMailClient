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
	if (!MySocket::Connect(Serv, Port))//���ӷ�����
	{
		return FALSE;
	}
	//���������Ƿ����
	if (!TellResponse("220"))
		return FALSE;
	//�����������"HELO "+��������
	string strTemp = "HELO " + Serv + "\r\n";
	if (send(mySocket, strTemp.c_str(), strTemp.length(), 0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return FALSE;
	}
	//�����������Ƿ����
	if (!TellResponse("250"))
		return FALSE;
	return TRUE;
}

bool MySmtp::ConfirmUser(const string userName, const string password)
{
	MyBase64 base64;

	//����"AUTH LOGIN"
	if (send(mySocket, "AUTH LOGIN\r\n", strlen("AUTH LOGIN\r\n"), 0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return false;
	}
	if (!TellResponse("334")) 
		return false;//�ȴ��û�������֤��Ϣ

	//���;�base64������û���
	string strSendemail = base64.Encode((const unsigned char*)userName.c_str(), userName.length()) + "\r\n";
	if (send(mySocket, strSendemail.c_str(), strSendemail.length(), 0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return false;
	}
	if (!TellResponse("334"))
		return false;

	//���;�base64���������
	string strPassword = base64.Encode((unsigned char *)password.c_str(), password.length()) + "\r\n";
	if (send(mySocket, strPassword.c_str(), strPassword.length(), 0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return false;
	}
	if (!TellResponse("235"))
		return false;//�û���֤ʧ��
	return true;
}

bool MySmtp::SendMail(const MailData sendMail) // �ʼ�����
{
	if(sendMail.srcAddr.empty())//�жϷ��͵�ַ�Ƿ�Ϊ��
		return false;
	if (sendMail.dstAddr.size() <= 0)//�ж�Ŀ�ĵ�ַ�б��Ƿ�Ϊ��
		return false;

	string strTmp;
	//����MAIL FROM:<abc@xyz.com>
	strTmp = "MAIL FROM:<" + sendMail.srcAddr + ">\r\n";
	if (send(mySocket,strTmp.c_str(),strTmp.length(),0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return false;
	}
	if (!TellResponse("250"))
		return false;

	//������Ŀ�ĵ�ַ
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

	//����"DATA\r\n"
	if (send(mySocket,"DATA\r\n",strlen("DATA\r\n"),0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return false;
	}
	if (!TellResponse("354"))
		return false;

	//"Mail From:Sendname<xxx@mail.com>\r\n"
	strTmp = "From:" + sendMail.sender + "<" + sendMail.srcAddr + ">\r\n";

	//"Subject: �ʼ�����\r\n"
	strTmp += "Subject:" + sendMail.subject + "\r\n";

	//�Ƚ�HEADER���ַ��͹�ȥ
	if (send(mySocket,strTmp.c_str(),strTmp.length(),0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return false;
	}
	//�ʼ�����
	//�ʼ�����
	//strTmp = sendMail.contents + "\r\n\r\n";
	strTmp = "hello\r\n\r\n";

	//���ʼ����ݷ��ͳ�ȥ
	if (send(mySocket,strTmp.c_str(),strTmp.length(), 0) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return false;
	}

	//��β����"."Ϊ������־
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

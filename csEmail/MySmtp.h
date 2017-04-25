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

const string BOUNDARY = "----=NEXT_iyuge2Hugnian";

class MySmtp:public MySocket
{
private:
	const string user;
	const string passwd;
	const string server;
	const int Port;
private:
	bool TellResponse(const char *ReturnCode);//�жϷ�����
	bool Send(const string msg);//������Ϣ
	void FormatHead(const MailData sendMail, string &contentsHead);//��ʽ���ʼ�����ͷ����Ϣ
	bool SendTextBody(const string content);//�����ʼ�����
	bool SendHtml(const string content);//����html�ļ�
	bool SendImage(const Contents content);//����ͼƬ��Ϣ
	bool SendAttachment(const Contents content);//���͸���
public:
	MySmtp(const string server, const int port, const string user, const string passwd) :MySocket(),
		user(user), passwd(passwd), server(server), Port(port) {};
    virtual ~MySmtp() {ReleaseSocket();};
	bool Connect();
	bool ConfirmUser();//��֤�û���������
	bool SendMail(const MailData sendMail);//�����ʼ�
	/*
	��ע:SMTPЭ��ķ���״̬��Ϣ
		211 ��������ϵͳ״̬
		214 ������Ϣ
		220 ����׼������
		221 �ر�����
		235 �û���֤�ɹ�
		250 �����������
		251 �û����ڱ��أ�ת�ĵ�����·��
		334 �ȴ��û�������֤��Ϣ
		354 ��ʼ�ʼ�����
		421 ���񲻿���
		450 ����δִ�У�����æ
		451 ������ֹ�����ش���
		452 ����δִ�У��洢�ռ䲻��
		500 �����ʶ������Դ���
		501 �����﷨����
		502 ���֧��
		503 ����˳�����
		504 ���������֧��
		535 ��֤ʧ��
		550 ����δִ�У����䲻����
		551 �Ǳ����û�
		552 ��ֹ�洢�ռ䲻��
		553 ����δִ�У�����������ȷ
		554 ����ʧ��
	*/
};

#endif


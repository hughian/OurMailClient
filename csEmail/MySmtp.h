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
	bool TellResponse(const char *ReturnCode);//�жϷ�����
public:
	MySmtp():MySocket() {};
	virtual ~MySmtp() {};
	bool Connect(const string Serv, const int Port);
	bool ConfirmUser(const string userName, const string password);//��֤�û���������
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


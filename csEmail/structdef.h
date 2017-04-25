#ifndef STRUCTDEF_H
#define STRUCTDEF_H
#include <string>
#include <deque>
#include <QDataStream>
using namespace std;
//
//struct Time
//{//��/��/��/ʱ/��/��
//	int year;
//	int month;
//	int day;
//	int hour;
//	int min;
//	int sec;
//};
struct Contents
{
	/*��������
	* 1--text/plain //������û��������
	* 2--text/html
	* 3--image
	* 4--����
	*/
	int type;
	/*������*/
	string name;
	/*����*/
	string content;
    void write(QDataStream &stream);
    void read(QDataStream &stream);
};
struct MailData
{
	string ID;//�ʼ���ʶ
	string srcAddr; //���͵�ַ
	deque<string> dstAddr;/*Ŀ�ĵ�ַ�б�,����,���ַ�Ϊ�ж��ַ�,a--��ͨ��ַ,b--���͵�ַ,c--���͵�ַ*/
	string sender;// ����������
	string subject;// �ʼ�����
	deque<Contents> contents;// �ʼ�����
	string time;//�ʼ�ʱ��
    void write(QDataStream &stream);
    void read(QDataStream &stream);

};
QString dstr2QString(deque<string> &ds);
deque<string> QString2dstr(QString &str,int sw = 0);

#endif

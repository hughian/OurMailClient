#ifndef _MYSOCKET_H
#define _MYSOCKET_H
#include "qt.h"
#include<string>
#include<winsock.h>
#include <QString>
#pragma comment(lib,"ws2_32.lib")

using namespace std;

class MySocket :public QObject{
    Q_OBJECT
signals:
    void sendStr(string str);
private:
	WSADATA myWsaData;
	HOSTENT *remoteHost;// struct hostent *remoteHost;
	sockaddr_in mySockAddrIn;

	bool CreateSocket(); //¥¥Ω®socket

protected:
	SOCKET mySocket;
	bool ReleaseSocket();// Õ∑≈socket
	bool Connect(const string Smtp, const int Port);
public:
    MySocket(QObject *parent=0):QObject(parent) {};
	virtual ~MySocket() {};
};
#endif

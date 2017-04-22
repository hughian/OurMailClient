/*
* author: iyuge2
* create-time: 2017/04/13 19:25
* update-time: 2017/04/15 20:20
* function: complete smtp class
*/
#ifndef _MYSOCKET_H
#define _MYSOCKET_H
#include<string>
#include<winsock.h>

#pragma comment(lib,"ws2_32.lib")

using namespace std;

class MySocket {
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
	MySocket() {};
	virtual ~MySocket() {};
};
#endif
#ifndef _MYBASE64_H
#define _MYBASE64_H
#include<string>

using namespace std;

class MyBase64
{
public:
	MyBase64() {};
	virtual ~MyBase64(){};
	//����
	string Encode(const unsigned char* Data, int DataByte);
	//����
	string Decode(const char* Data, int DataByte, int& OutByte);
};

#endif
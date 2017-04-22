#ifndef _MYBASE64_H
#define _MYBASE64_H
#include<string>

using namespace std;

class MyBase64
{
public:
	MyBase64() {};
	virtual ~MyBase64(){};
	//±àÂë
	string Encode(const unsigned char* Data, int DataByte);
	//½âÂë
	string Decode(const char* Data, int DataByte, int& OutByte);
};

#endif
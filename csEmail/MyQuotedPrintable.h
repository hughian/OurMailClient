#ifndef _MYQUOTEDPRINTABLE_H
#define _MYQUOTEDPRINTABLE_H
#include <string>

using namespace std;

class MyQuotedPrintable {
public:
	MyQuotedPrintable() {};
	virtual ~MyQuotedPrintable() {};
protected:
	int GetByteFromHexChar(char cHex);
public:
	string Decode(string toDecode);
};
#endif // !_MYQUOTEDPRINTBLE


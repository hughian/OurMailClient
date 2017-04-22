#include"MyQuotedPrintable.h"
// 概述：获取16进制字符对应的10进制数
// 输入：cHex是16进制的字符（'0'-'9','a'-'f','A'-'F'）
// 输出：字符cHex对应的10进制数， 如'A'-10, '9'-9
int MyQuotedPrintable::GetByteFromHexChar(char cHex)
{
	int ret = -1;

	if (cHex >= '0' && cHex <= '9')
	{
		ret = cHex - '0';
	}
	else if (cHex >= 'A' && cHex <= 'F')
	{
		ret = cHex - 'A' + 10;
	}
	else if (cHex >= 'a' && cHex <= 'f')
	{
		ret = cHex - 'a' + 10;
	}

	return ret;
}

// 概述：获取解码后的字节串
// 输入：待解码的字符串toDecode
// 输出：解码后的字节串
string MyQuotedPrintable::Decode(string toDecode)
{
	if (toDecode.empty())
	{
		return string("");
	}

	string strDecoded;

	// 遍历整个要解码的字符串
	for (int i = 0; i < toDecode.length(); i++)
	{
		char currentChar = toDecode[i];
		if (currentChar == '=')
		{
			// 检查 = 后是否还有两个字符
			if (toDecode.length() - i < 3)
			{
				// 到达末尾
				break;
			}

			// 解码Quoted-Printable部分
			string quotedPrintablePart = toDecode.substr(i, 3);
			unsigned char c = GetByteFromHexChar(quotedPrintablePart[1]) << 4;
			c += GetByteFromHexChar(quotedPrintablePart[2]);
			strDecoded += c;

			i += 2;
		}
		else
		{
			// 没有编码过的字符
			strDecoded += currentChar;
		}
	}

	return strDecoded;
}

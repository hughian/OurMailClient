#include"MyQuotedPrintable.h"
// ��������ȡ16�����ַ���Ӧ��10������
// ���룺cHex��16���Ƶ��ַ���'0'-'9','a'-'f','A'-'F'��
// ������ַ�cHex��Ӧ��10�������� ��'A'-10, '9'-9
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

// ��������ȡ�������ֽڴ�
// ���룺��������ַ���toDecode
// ������������ֽڴ�
string MyQuotedPrintable::Decode(string toDecode)
{
	if (toDecode.empty())
	{
		return string("");
	}

	string strDecoded;

	// ��������Ҫ������ַ���
	for (int i = 0; i < toDecode.length(); i++)
	{
		char currentChar = toDecode[i];
		if (currentChar == '=')
		{
			// ��� = ���Ƿ��������ַ�
			if (toDecode.length() - i < 3)
			{
				// ����ĩβ
				break;
			}

			// ����Quoted-Printable����
			string quotedPrintablePart = toDecode.substr(i, 3);
			unsigned char c = GetByteFromHexChar(quotedPrintablePart[1]) << 4;
			c += GetByteFromHexChar(quotedPrintablePart[2]);
			strDecoded += c;

			i += 2;
		}
		else
		{
			// û�б�������ַ�
			strDecoded += currentChar;
		}
	}

	return strDecoded;
}

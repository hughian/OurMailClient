#include "MyBase64.h"

string MyBase64::Encode(const unsigned char* Data, int DataByte)
{
	const char EncodeTable[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";//�����

	string returnEncode;//����ֵ

	unsigned char Tmp[3] = { 0 };
	int LineLength = 0;

	for(int i = 0; i<(int)(DataByte / 3); i++)
	{
		Tmp[0] = *Data++;
		Tmp[1] = *Data++;
		Tmp[2] = *Data++;

		returnEncode += EncodeTable[Tmp[0] >> 2];
		returnEncode += EncodeTable[((Tmp[0] << 4) | (Tmp[1] >> 4)) & 0x3F];
		returnEncode += EncodeTable[((Tmp[1] << 2) | (Tmp[2] >> 6)) & 0x3F];
		returnEncode += EncodeTable[Tmp[2] & 0x3F];
		LineLength += 4;
		if (LineLength == 76) 
		{ 
			returnEncode += "\r\n";//���д���
			LineLength = 0; 
		}
	}
	//��ʣ�����ݽ��б���
	int Mod = DataByte % 3;
	if (Mod == 1)
	{
		Tmp[0] = *Data++;
		returnEncode += EncodeTable[(Tmp[0] & 0xFC) >> 2];
		returnEncode += EncodeTable[((Tmp[0] & 0x03) << 4)];
		returnEncode += "==";
	}
	else if (Mod == 2)
	{
		Tmp[0] = *Data++;
		Tmp[1] = *Data++;
		returnEncode += EncodeTable[(Tmp[0] & 0xFC) >> 2];
		returnEncode += EncodeTable[((Tmp[0] & 0x03) << 4) | ((Tmp[1] & 0xF0) >> 4)];
		returnEncode += EncodeTable[((Tmp[1] & 0x0F) << 2)];
		returnEncode += "=";
	}
	
	return returnEncode;
}

// ����������base64������ֽڴ�
// ���룺Data�Ǵ�������ֽڴ��� DataByte��Data��Ҫ����ĳ���
// �����OutByte�ǽ������ֽڴ����ȣ� strDecode�������ֽڴ�
string MyBase64::Decode(const char* Data, int DataByte, int& OutByte)
{
	//�����
	const char DecodeTable[] =
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0,62, 0, 0, 0,63,52, 53,//��+����/����0-1��
		54,55,56,57,58,59,60,61,0, 0,// '2-9'
		0, 0, 0, 0, 0,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
		13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, // 'A'-'Z'
		0, 0, 0, 0, 0, 0,
		26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
		39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, // 'a'-'z'
	};

	//����ֵ
	string returnDecode;

	int nValue;
	int i = 0;

	while (i < DataByte)
	{
		if (*Data != '\r' && *Data != '\n')
		{
			nValue = DecodeTable[*Data++] << 18;
			nValue += DecodeTable[*Data++] << 12;
			returnDecode += (nValue & 0x00FF0000) >> 16;
			OutByte++;

			if (*Data != '=')
			{
				nValue += DecodeTable[*Data++] << 6;
				returnDecode += (nValue & 0x0000FF00) >> 8;
				OutByte++;

				if (*Data != '=')
				{
					nValue += DecodeTable[*Data++];
					returnDecode += nValue & 0x000000FF;
					OutByte++;
				}
			}
			i += 4;
		}
		else// �س�����,����
		{
			Data++;
			i++;
		}
	}
	return returnDecode;
}
#include"MySocket.h"

bool MySocket::CreateSocket()
{
	if (WSAStartup(0x0101, &myWsaData) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return FALSE;
	}
	if (myWsaData.wVersion != 0x0101)
	{
		WSACleanup();
		return FALSE;
	}
	if ((mySocket = socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR)
	{
		ReleaseSocket();
		return FALSE;
	}
	return TRUE;
}

bool MySocket::ReleaseSocket()
{
	closesocket(mySocket);//�ر�SOCKET�˿�
	WSACleanup();
	return TRUE;
}

bool MySocket::Connect(const string Smtp, const int Port)
{
	/*�����׽���*/
	if (!CreateSocket())
	{
		return FALSE;
	}
	/*
	* ����ԭ�ͣ�struct hostent *gethostbyname(const char *name);
	* ���ض�Ӧ�ڸ����������İ����������ֺ͵�ַ��Ϣ��hostent�ṹָ��
	* struct hostent
	* {
	* char *h_name;//�����Ĺ淶��,��www.google.com
	* char ** h_aliases;//�����ı���
	* short h_addrtype;//����IP��ַ������(AF_INET)��ipv4����ipv6(AF_INET6)
	* short h_length;//����IP��ַ�ĳ���
	* char ** h_addr_list;//������IP��ַ
	* };
	*/
	if ((remoteHost = gethostbyname(Smtp.c_str())) == NULL)
	{
		ReleaseSocket();
		return FALSE;
	}
	if (remoteHost->h_addr_list[0] == NULL)
	{//�ж�IP�Ƿ����
		ReleaseSocket();
		return FALSE;
	}
	memset(&mySockAddrIn, 0, sizeof(mySockAddrIn));
	mySockAddrIn.sin_family = AF_INET;
	mySockAddrIn.sin_port = htons(Port);
	mySockAddrIn.sin_addr.S_un.S_addr = *(ULONG *)remoteHost->h_addr_list[0];
	//���ӷ�����
	int timeout = 600;
    while (timeout && (::connect(mySocket, (LPSOCKADDR)&mySockAddrIn, sizeof(mySockAddrIn)) == SOCKET_ERROR))
	{
		timeout--;
		if (!timeout)
			return FALSE;
		Sleep(10);
	}
	return TRUE;
}

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
	closesocket(mySocket);//关闭SOCKET端口
	WSACleanup();
	return TRUE;
}

bool MySocket::Connect(const string Smtp, const int Port)
{
	/*创建套接字*/
	if (!CreateSocket())
	{
		return FALSE;
	}
	/*
	* 函数原型：struct hostent *gethostbyname(const char *name);
	* 返回对应于给定主机名的包含主机名字和地址信息的hostent结构指针
	* struct hostent
	* {
	* char *h_name;//主机的规范名,如www.google.com
	* char ** h_aliases;//主机的别名
	* short h_addrtype;//主机IP地址的类型(AF_INET)，ipv4或者ipv6(AF_INET6)
	* short h_length;//主机IP地址的长度
	* char ** h_addr_list;//主机的IP地址
	* };
	*/
	if ((remoteHost = gethostbyname(Smtp.c_str())) == NULL)
	{
		ReleaseSocket();
		return FALSE;
	}
	if (remoteHost->h_addr_list[0] == NULL)
	{//判断IP是否存在
		ReleaseSocket();
		return FALSE;
	}
	memset(&mySockAddrIn, 0, sizeof(mySockAddrIn));
	mySockAddrIn.sin_family = AF_INET;
	mySockAddrIn.sin_port = htons(Port);
	mySockAddrIn.sin_addr.S_un.S_addr = *(ULONG *)remoteHost->h_addr_list[0];
	//连接服务器
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

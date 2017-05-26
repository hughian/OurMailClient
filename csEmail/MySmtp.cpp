#include"MySmtp.h"

bool MySmtp::Send(const string msg)
{
	if (send(mySocket, msg.c_str() , msg.length(), 0) == SOCKET_ERROR)
	{
		return FALSE;
	}
	return TRUE;
}

bool MySmtp::TellResponse(const char *ReturnCode)
{
	char Buf[256] = { 0 };
	if (recv(mySocket,Buf,1024,0) == SOCKET_ERROR)
		return FALSE;
	Sleep(50);
    sendStr(string(Buf));
	return (ReturnCode[0] == Buf[0] &&
		ReturnCode[1] == Buf[1] &&
		ReturnCode[2] == Buf[2]) ? TRUE : FALSE;
}

bool MySmtp::Connect()
{
	if (!MySocket::Connect(server, Port))//连接服务器
	{
		return FALSE;
	}
	//检查服务器是否就绪
	if (!TellResponse("220"))
		return FALSE;
	//向服务器发送"HELO "+服务器名
	string strTemp = "HELO " + server + "\r\n";
	if (Send(strTemp) == FALSE)
	{
		return FALSE;
	}
	//检查请求操作是否就绪
	if (!TellResponse("250"))
		return FALSE;
	return TRUE;
}

bool MySmtp::ConfirmUser()
{
	MyBase64 base64;
    string strTemp;
	//发送"AUTH LOGIN"
    strTemp = "AUTH LOGIN\r\n";
    sendStr(strTemp);
	if (Send("AUTH LOGIN\r\n") == FALSE)
	{
		return FALSE;
	}
	if (!TellResponse("334")) 
		return FALSE;//等待用户输入验证信息

	//发送经base64编码的用户名
	string strSendemail = base64.Encode((const unsigned char*)user.c_str(), user.length()) + "\r\n";
    sendStr(strSendemail);
	if (Send(strSendemail) == FALSE)
	{
		return FALSE;
	}
	if (!TellResponse("334"))
		return FALSE;

	//发送经base64编码的密码
	string strPassword = base64.Encode((unsigned char *)passwd.c_str(), passwd.length()) + "\r\n";
    sendStr(strPassword);
	if (Send(strPassword) == FALSE)
	{
		return FALSE;
	}
	if (!TellResponse("235"))
		return FALSE;//用户验证失败
	return true;
}

void MySmtp::FormatHead(const MailData sendMail,string &contentsHead)
{
	//"Mail From:Sendname<xxx@mail.com>\r\n"
	contentsHead = "From: " + sendMail.sender + "<" + sendMail.srcAddr + ">\r\n";

	//增加密送和抄送地址
	for (unsigned int i = 0; i < sendMail.dstAddr.size(); i++)
	{
		if (sendMail.dstAddr[i][0] == 'b')
			contentsHead += "Bcc: <" + sendMail.dstAddr[i].substr(1) + ">\r\n";
		else if (sendMail.dstAddr[i][0] == 'c')
			contentsHead += "Cc: <" + sendMail.dstAddr[i].substr(1) + ">\r\n";
		else
			contentsHead += "To: <" + sendMail.dstAddr[i].substr(1) + ">\r\n";
	}

	//"Subject: 邮件主题\r\n"
	contentsHead += "Subject:" + sendMail.subject + "\r\n";

    contentsHead += "MIME-Version:1.0\r\n";
	
	contentsHead += "Content-Type: multipart/mixed;boundary=\"" + BOUNDARY +"\"\r\n";

    contentsHead += "This is a multi-part message in MIME format.\r\n";

	contentsHead += "\r\n";
}

bool MySmtp::SendTextBody(const string content)
{
	string sendBuff;
    sendBuff = "--" + BOUNDARY + "\r\n";
    sendBuff += "Content-Type: text/plain;";
    sendBuff += "charset=\"UTF-8\"\r\n\r\n";
	sendBuff += content;
	sendBuff += "\r\n\r\n";
	return Send(sendBuff);
}

bool MySmtp::SendHtml(const string content)
{
	string sendBuff;
	sendBuff = "--" + BOUNDARY + "\r\n";
	sendBuff += "Content-Type: text/html;";
    sendBuff += "charset=\"UTF-8\"\r\n\r\n";
	sendBuff += content;
	sendBuff += "\r\n\r\n";
	return Send(sendBuff);
}

bool MySmtp::SendImage(const Contents content)
{
	//提取图片的后缀名与前缀名
	int pos1 = content.name.find(".");
	string BackName = content.name.substr(pos1+1,content.name.length() - pos1 - 1);

	string sendBuff;
	sendBuff = "--" +  BOUNDARY + "\r\n";
	sendBuff += "Content-Type: image/ " + BackName + ";\r\n";
	sendBuff += "name=\"" + content.name + "\"" + "\r\n";

	sendBuff += "Content-Transfer-Encoding: base64\r\n\r\n";
	if (Send(sendBuff) == FALSE)
	{
		return FALSE;
	}
	MyBase64 base64;
	sendBuff = base64.Encode((unsigned char *)content.content.c_str(), content.content.length()) + "\r\n";

	if (Send(sendBuff) == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

bool MySmtp::SendAttachment(const Contents content)
{
	string sendBuff;
	sendBuff = "--" +  BOUNDARY + "\r\n";
	sendBuff += "Content-Type: application/octet-stream;\r\n";
	sendBuff += " name=\"" + content.name + "\"" + "\r\n";

	sendBuff += "Content-Transfer-Encoding: base64\r\n";
	sendBuff += "Content-Disposition: attachment;\r\n";
	sendBuff += " filename=\"" + content.name + "\"" + "\r\n\r\n";

	if (Send(sendBuff) == FALSE)
	{
		return FALSE;
	}
	MyBase64 base64;
	sendBuff = base64.Encode((unsigned char *)content.content.c_str(), content.content.length()) + "\r\n";

	if (Send(sendBuff) == FALSE)
	{
		return FALSE;
	}
    //std::cout << sendBuff;
	return TRUE;
}

bool MySmtp::SendMail(const MailData sendMail) // 邮件内容
{
    QList<MailData> mdl;
    mdl << sendMail;
    printmdl(mdl);
    //qDebug("%s",sendMail.contents.at(0).content.c_str());
    if(sendMail.srcAddr.empty())//判断发送地址是否为空
		return false;
	if (sendMail.dstAddr.size() <= 0)//判断目的地址列表是否为空
		return false;

	string strTmp;
	//发送MAIL FROM:<abc@xyz.com>
	strTmp = "MAIL FROM: <" + sendMail.srcAddr + ">\r\n";
    sendStr(strTmp);
	if (Send(strTmp) == FALSE)
	{
		return FALSE;
	}
	if (!TellResponse("250"))
		return FALSE;

	//逐个甄别目的地址
	for (unsigned int i = 0; i < sendMail.dstAddr.size(); i++)
	{
		strTmp = "RCPT To: <" + sendMail.dstAddr[i].substr(1) + ">\r\n";
        sendStr(strTmp);
		if (Send(strTmp) == FALSE)
		{
			return FALSE;
		}
		if (!TellResponse("250"))
			return FALSE;
	}

	//发送"DATA\r\n"
    strTmp = "DATA\r\n";
    sendStr(strTmp);
	if (Send("DATA\r\n") == FALSE)
	{
		return FALSE;
	}
	if (!TellResponse("354"))
		return FALSE;
	
	//初始化邮件头部信息
	FormatHead(sendMail, strTmp);

	//先将HEADER部分发送过去
	if (Send(strTmp) == FALSE)
	{
		return FALSE;
	}
	//邮件主体
	//邮件内容
	for (unsigned int i = 0; i < sendMail.contents.size(); i++)
	{
		if (sendMail.contents[i].type == 1)//发送text/plain
		{
            if (SendTextBody(sendMail.contents[i].content) == FALSE)
			{
				return FALSE;
			}
		}
		else if (sendMail.contents[i].type == 2)//发送text/html
		{
			if (SendHtml(sendMail.contents[i].content) == FALSE)
			{
				return FALSE;
			}
		}
		else if (sendMail.contents[i].type == 3)//发送image
		{
			if (SendImage(sendMail.contents[i]) == FALSE)
			{
				return FALSE;
			}
		}
		else if (sendMail.contents[i].type == 4)//发送附件
		{
			if (SendAttachment(sendMail.contents[i]) == FALSE)
			{
				return FALSE;
			}
		}
		else
			continue;
	}

	//界尾，以"."为结束标志
    strTmp = "--" + BOUNDARY + "--" + "\r\n";
	strTmp += "\r\n.\r\n";

	if (Send(strTmp) == FALSE)
	{
		return FALSE;
	}
	if (!TellResponse("250"))
	{
		return false;
	}
	//结束邮件的发送
	strTmp = "QUIT\r\n";
    sendStr(strTmp);
	if (Send(strTmp) == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}


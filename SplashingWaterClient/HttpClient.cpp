#include "stdafx.h"
#include "HttpClient.h"

#pragma comment(lib,"ws2_32.lib")

HttpClient* HttpClient::m_pInstance = NULL;

HttpClient::HttpClient() 
{
	m_nReceiveLength = 0;
	m_strAccount = "100001";
	initial();
}


HttpClient::~HttpClient()
{
	end_Thread();

}

void HttpClient::initial()
{
	m_ClientSocket = INVALID_SOCKET;
	
	WSADATA  wsaData;
	m_nErrorCode = WSAStartup(MAKEWORD(2, 2), &wsaData); //调用Winsock2.2版本 0  -1
	handlerErrorInfo();

	//m_MessageHandler.addObserver()
}

void HttpClient::addMsgObserver(ObserverInterface *pObserver)
{
	m_MessageHandler.addObserver(pObserver);
}

void HttpClient::handlerErrorInfo()
{
	if (m_nErrorCode != 0)
	{
		Log_Error("HttpClient::handlerErrorInfo()------get Error");
		throw;
	}
}

bool HttpClient::connectServer(const char *pIPAddr,int nPort)
{
	Log_Info("HttpClient::connectServer()------connect Server....");

	m_ClientSocket = socket(AF_INET, SOCK_STREAM, 0);//创建套接字  家族协议；流式套接字；默认值
	SOCKADDR_IN addrClient;
	addrClient.sin_family = AF_INET;
	addrClient.sin_addr.s_addr = inet_addr(pIPAddr);
	addrClient.sin_port = htons(nPort);

	int nResults = connect(m_ClientSocket, (SOCKADDR*)&addrClient, sizeof(SOCKADDR));
	if (nResults != 0)
	{
		Log_Error("HttpClient::connectServer()------Client Connect Server Fail!");
		closesocket(m_ClientSocket);
		MessageBox(NULL, _T("Client Connect Server Fail!"), _T("HttpClient"), MB_ICONEXCLAMATION | MB_OKCANCEL);
		return false;
	}
	Log_Info("HttpClient::connectServer()------connect Server successfully");

	//open new Thread to receive data
	start_Thread();
	return true;
}

void HttpClient::sendData(const char *pSendData)
{
	if (m_ClientSocket == INVALID_SOCKET)//INVALID_SOCKET非法套接字
	{
		Log_Error("HttpClient::sendData() Client Connect Server Fail!");
		return;
	}
	int bSendResults = send(m_ClientSocket, pSendData, strlen(pSendData) + 1, 0);
	if (bSendResults < 0)
	{
		MessageBox(NULL, _T("Failed to send Data."), _T("标题"), MB_ICONEXCLAMATION | MB_OKCANCEL);
	}
}
void HttpClient::run()
{
	receiveData(m_cReceiveData, sizeof(m_cReceiveData));
	
	if (strcmp(m_cReceiveData, "") != 0)
	{
		string strReceiveData = m_cReceiveData;
		strReceiveData = "HttpClient::receiveData()" + strReceiveData;
		Log_Info(strReceiveData.c_str());
		m_MessageHandler.processMessage(m_cReceiveData, m_nReceiveLength);
		//string strResult = m_MessageHandler.parserMessage();
		//strcpy(m_SubjectData.pChar, strResult.c_str());
		//Notity();
		memset(m_cReceiveData, 0, sizeof(m_cReceiveData));
	}	
}

void HttpClient::receiveData(char *pReceiveData, int nLen)
{
	if (m_ClientSocket == INVALID_SOCKET)//INVALID_SOCKET非法套接字
	{
		Log_Error("HttpClient::receiveData()------Client is not connect Server");
		end_Thread();
		return;
	}
	m_nReceiveLength = recv(m_ClientSocket, pReceiveData, nLen, 0);
	if (m_nReceiveLength < 0)
	{
		Log_Error("HttpClient::receiveData()------get reciveData length is < 0 ");
		end_Thread();
		MessageBox(NULL, _T("Failed to receive Data. Server is disconnect"), _T("HttpClient"), MB_ICONEXCLAMATION | MB_OKCANCEL);
	}
}

bool HttpClient::disConnectServer()
{
	//sendData("disconnect");
	end_Thread();
	closesocket(m_ClientSocket);
	WSACleanup();
	return true;
}

void HttpClient::setAccount(string strAccount)
{
	m_strAccount = strAccount;
}

string HttpClient::getAccount()
{
	return m_strAccount;
}

string HttpClient::getIPAddress()
{
	char szHost[256];
	gethostname(szHost, 256);
	hostent *pHost = gethostbyname(szHost);
	in_addr addr;

	char *p = pHost->h_addr_list[0];
	memcpy(&addr.S_un.S_addr, p, pHost->h_length);
	string strIP = inet_ntoa(addr);
	return strIP;
}


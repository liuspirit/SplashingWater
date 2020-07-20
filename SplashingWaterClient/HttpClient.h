#pragma once
#include<winsock2.h>
#include <string>
#include "HttpThread.h"
#include "Observer\Subject.h"
#include "MessageHandler.h"
using namespace std;


class HttpClient :public HttpThread, public Subject
{
public:

	static HttpClient* getInstance(){
		if (m_pInstance == NULL)
		{
			m_pInstance = new HttpClient();
		}
		return m_pInstance;
	}

	static void DestoryInstance()
	{
		if (m_pInstance != NULL)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}
	
	virtual ~HttpClient();


	void initial();
	void handlerErrorInfo();

	bool connectServer(const char *pIPAddr, int nPort);
	bool disConnectServer();
	void sendData(const char *pSendData);
	void receiveData(char *pReceiveData, int nLen);

	void setAccount(string strAccount);
	string getAccount();

	static string getIPAddress();
	virtual void run();

	void addMsgObserver(ObserverInterface *pObserver);

private:
	HttpClient();


private:
	SOCKET m_ClientSocket;
	int m_nErrorCode;
	MessageHandler m_MessageHandler;
	char m_cReceiveData[2048];
	int m_nReceiveLength;

	static HttpClient* m_pInstance;
	string m_strAccount;
};


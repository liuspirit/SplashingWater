/*
1.ÂÖÑ°
2.¶©ÔÄ
*/
#pragma once
#include "MessageData.h"
class MessageBuffer
{
public:
	static MessageBuffer* getInstance()
	{
		if (m_pInstance == NULL)
		{
			m_pInstance = new MessageBuffer(1);
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

	virtual ~MessageBuffer();
public:
	//ÂÖÑ°
	string getLogicMsg(int nTimeOutS);
	string getRegisterMsg(int nTimeOutS);
	vector<string> getFriendMsg(int nTimeOutS, const char *pAccount);

	void setLogicMsg(string strLogicMsg);
	void setRegisterMsg(string strRegMsg);

	//¶©ÔÄ
	bool getFriendMsgFlag(const char *pAccount);

	void initial();

private:
	MessageBuffer(int nTimeOut);

private:
	static MessageBuffer* m_pInstance;
	MessageData m_MessageData;
	int m_nTimeOut;  //ms
};


#include "stdafx.h"
#include "MessageBuffer.h"
#include "HttpClient.h"
MessageBuffer* MessageBuffer::m_pInstance = NULL;
MessageBuffer::MessageBuffer(int nTimeOut)
{
	m_nTimeOut = nTimeOut;
}


MessageBuffer::~MessageBuffer()
{
}

void MessageBuffer::initial()
{
	HttpClient::getInstance()->addMsgObserver(&m_MessageData);
}

string MessageBuffer::getLogicMsg(int nTimeOutS)
{
	int nNum = nTimeOutS * 1000 / 5;
	string strLogicMsg = "";
	while (nNum--)
	{
		if (m_MessageData.getLogicFlag())
		{
			strLogicMsg = m_MessageData.getLogicMessage();
			break;
		}
		Sleep(5);
	}
	m_MessageData.clearLogicMessage();
	return strLogicMsg;
}

string MessageBuffer::getRegisterMsg(int nTimeOutS)
{
	int nNum = nTimeOutS * 1000 / 5;
	string strRegMsg = "";
	while (nNum--)
	{
		if (m_MessageData.getRegisterFlag())
		{
			strRegMsg = m_MessageData.getRegisterMessage();
			break;
		}
		Sleep(5);
	}
	m_MessageData.clearRegisterMessage();
	return strRegMsg;
}

void MessageBuffer::setLogicMsg(string strLogicMsg)
{
	m_MessageData.setLogicMessage(strLogicMsg.c_str());
}
void MessageBuffer::setRegisterMsg(string strRegMsg)
{
	m_MessageData.setRegisterMessage(strRegMsg.c_str());
}

vector<string> MessageBuffer::getFriendMsg(int nTimeOutS, const char *pAccount)
{
	int nNum = nTimeOutS * 1000 / 5;
	vector<string> vRegMsg;
	while (nNum--)
	{
		if (m_MessageData.getMessageFlag(pAccount))
		{
			return m_MessageData.getFriendMsg(pAccount);
		}
		Sleep(5);
	}
	return vRegMsg;
}

bool MessageBuffer::getFriendMsgFlag(const char *pAccount)
{
	return m_MessageData.getMessageFlag(pAccount);
}
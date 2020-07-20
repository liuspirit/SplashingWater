#include "stdafx.h"
#include "MessageData.h"


MessageData::MessageData()
{
	m_bLogicFlag = false;
	m_bStateFlag = false;
	m_bRegisterFlag =false;
	m_bUpdateFlag = false;
}


MessageData::~MessageData()
{
}

/*
管道队列
管道1：队列；若该好友下线，这关闭管道
管道2：队列
管道3：队列
消息从管道里进入：存储在管道中，没有读取，则堵塞；读取一次则读完；
如果有管道消息，则置管道标志位；读完后复位；
*/

void MessageData::update(struct SubjectData subjectData)
{
	if (subjectData.nInt == 1)
	{
		m_FriendPipeGroup.pushPipeMsg(subjectData.pData2, subjectData.pChar);
	}
}

vector<string> MessageData::getFriendMsg(const char *pFriendAccount)
{
	return m_FriendPipeGroup.popPipeMsg(pFriendAccount);
}

void MessageData::setLogicMessage(const char *pLogicM)
{
	clearLogicMessage();
	strcpy(m_cLogicMessageData, pLogicM);
	m_bLogicFlag = true;
}
void MessageData::setStateMessage(const char *pStateM)
{
	clearStateMessage();
	strcpy(m_cStateMessageData, pStateM);
	m_bStateFlag = true;
}
void MessageData::setRegisterMessage(const char *pRegisterM)
{
	clearRegisterMessage();
	strcpy(m_cRegisterMessageData, pRegisterM);
	m_bRegisterFlag = true;
}
void MessageData::setUpdateMessage(const char *pUpdateM)
{
	clearUpdateMessage();
	strcpy(m_cUpdateMessageData, pUpdateM);
	m_bUpdateFlag = true;
}


char* MessageData::getLogicMessage()
{
	return m_cLogicMessageData;
}
char* MessageData::getStateMessage()
{
	return m_cStateMessageData;
}
char* MessageData::getRegisterMessage()
{
	return m_cRegisterMessageData;
}
char* MessageData::getUpdateMessage()
{
	return m_cUpdateMessageData;
}

void MessageData::clearLogicMessage()
{
	memset(m_cLogicMessageData, 0, sizeof(m_cLogicMessageData));
	m_bLogicFlag = false;
}
void MessageData::clearStateMessage()
{
	memset(m_cStateMessageData, 0, sizeof(m_cStateMessageData));
	m_bStateFlag = false;
}
void MessageData::clearRegisterMessage()
{
	memset(m_cRegisterMessageData, 0, sizeof(m_cRegisterMessageData));
	m_bRegisterFlag = false;
}
void MessageData::clearUpdateMessage()
{
	memset(m_cUpdateMessageData, 0, sizeof(m_cUpdateMessageData));
	m_bUpdateFlag = false;
}

bool MessageData::getLogicFlag()
{
	return m_bLogicFlag;
}
bool MessageData::getStateFlag()
{
	return m_bStateFlag;
}
bool MessageData::getMessageFlag(const char *pFriendAccount)
{
	return m_FriendPipeGroup.getPipeFlag(pFriendAccount);
}
bool MessageData::getRegisterFlag()
{
	return m_bRegisterFlag;
}
bool MessageData::getUpdateFlag()
{
	return m_bUpdateFlag;
}
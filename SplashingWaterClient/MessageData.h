#pragma once
#include "PipeQueue.h"
#include "Observer\ObserverInterface.h"
class MessageData : public ObserverInterface
{
public:
	MessageData();
	~MessageData();

public:
	virtual void update(struct SubjectData subjectData);

	//void setDlgMessage(const char *pFriendAccount, const char *pMsg);
	void setLogicMessage(const char *pLogicM);
	void setStateMessage(const char *pStateM);
	void setRegisterMessage(const char *pRegisterM);
	void setUpdateMessage(const char *pUpdateM);

	vector<string> getFriendMsg(const char *pFriendAccount);


	char* getLogicMessage();
	char* getStateMessage();
	char* getRegisterMessage();
	char* getUpdateMessage();

	void clearDlgMessage();
	void clearLogicMessage();
	void clearStateMessage();
	void clearRegisterMessage();
	void clearUpdateMessage();

	bool getLogicFlag();
	bool getStateFlag();
	bool getMessageFlag(const char *pFriendAccount);
	bool getRegisterFlag();
	bool getUpdateFlag();

private:

	PipeQueue m_FriendPipeGroup;

	char m_cLogicMessageData[2048];
	char m_cStateMessageData[1024];
	char m_cRegisterMessageData[1024];
	char m_cUpdateMessageData[1024];

	bool m_bLogicFlag;
	bool m_bStateFlag;
	bool m_bRegisterFlag;
	bool m_bUpdateFlag;
};


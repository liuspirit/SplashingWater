#include "stdafx.h"
#include "SendStrategy.h"
#include "MessageHandler.h"
#include "SmartPtr.h"

SendStrategy::SendStrategy(string &strFriendAccount, string &strMessage)
{
	m_strFriendAccount = strFriendAccount;
	m_strMessage = strMessage;
}

SendStrategy::SendStrategy()
{


}

SendStrategy::~SendStrategy()
{


}

void SendStrategy::buildPackage()
{
	//0x01 0x03 xx 01 100001 xxx 0x05 FriendAccount 0x06 Message 0x02
	string strAccount = HttpClient::getInstance()->getAccount();

	memset(m_cMessagePackage, 0, sizeof(m_cMessagePackage));
	MessageHandler::buildDataElement(m_cMessagePackage, m_strMessage.c_str(), 1, strAccount.c_str(), m_strFriendAccount.c_str());
	Log_Debug("SendStrategy::");
	Log_Debug(m_cMessagePackage);
	Log_Debug("SendStrategy::buildPackage  end");

}


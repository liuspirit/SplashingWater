#include "stdafx.h"
#include "LogicStrategy.h"

LogicStrategy::LogicStrategy(string strAccount, string strPassword)
{
	m_strAccount = strAccount;
	m_strPassword = strPassword;
}

LogicStrategy::LogicStrategy()
{
}


LogicStrategy::~LogicStrategy()
{
}

void LogicStrategy::buildPackage()
{
	//0x01 0x03 xx 03 Account xxx 0x05 IP 0x06 Password 0x02
	Log_Debug("LogicStrategy::buildPackage  begin");
	HttpClient::getInstance()->setAccount(m_strAccount);
	//获取本机IP
	string strIP = HttpClient::getIPAddress();

	memset(m_cMessagePackage, 0, sizeof(m_cMessagePackage));
	MessageHandler::buildDataElement(m_cMessagePackage, m_strPassword.c_str(), 3, m_strAccount.c_str(), strIP.c_str());
	Log_Debug("LogicStrategy::");
	Log_Debug(m_cMessagePackage);
	Log_Debug("LogicStrategy::buildPackage  end");
}
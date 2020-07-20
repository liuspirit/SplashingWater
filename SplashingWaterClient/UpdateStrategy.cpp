#include "stdafx.h"
#include "UpdateStrategy.h"


UpdateStrategy::UpdateStrategy(int &nChoice, string &strAccount)
{
	m_nChoice = nChoice;
	m_strAccount = strAccount;
}

UpdateStrategy::UpdateStrategy()
{
}

UpdateStrategy::~UpdateStrategy()
{
}


void UpdateStrategy::buildPackage()
{
	Log_Debug("RegisterStrategy::buildPackage  begin");
	string strCurrentAccount = HttpClient::getInstance()->getAccount();


	memset(m_cMessagePackage, 0, sizeof(m_cMessagePackage));


	if (m_nChoice == 1)
	{
		MessageHandler::buildDataElement(m_cMessagePackage, m_strAccount.c_str(), 4, strCurrentAccount.c_str(), "1");
	}
	else if (m_nChoice==0)
	{
		MessageHandler::buildDataElement(m_cMessagePackage, m_strAccount.c_str(), 4, strCurrentAccount.c_str(), "0");
	}

	Log_Debug("UpdateStrategy::");
	Log_Debug(m_cMessagePackage);
	Log_Debug("UpdateStrategy::buildPackage  end");
}

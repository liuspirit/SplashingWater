#include "stdafx.h"
#include "StateStrategy.h"

StateStrategy::StateStrategy(int nStateValue)
{
	m_nStateValue = nStateValue;
}

StateStrategy::StateStrategy()
{
}

StateStrategy::~StateStrategy()
{
}

void StateStrategy::buildPackage()
{
	memset(m_cMessagePackage, 0, sizeof(m_cMessagePackage));
	string strSelfAccount = HttpClient::getInstance()->getAccount();

	if (m_nStateValue == 1)
	{
		MessageHandler::buildDataElement(m_cMessagePackage, strSelfAccount.c_str(), 2, strSelfAccount.c_str(), "1");
	}
	else if (m_nStateValue == 0)
	{
		MessageHandler::buildDataElement(m_cMessagePackage, strSelfAccount.c_str(), 2, strSelfAccount.c_str(), "0");
	}
	Log_Debug("StateStrategy::");
	Log_Debug(m_cMessagePackage);
	Log_Debug("StateStrategy::buildPackage  end");
}

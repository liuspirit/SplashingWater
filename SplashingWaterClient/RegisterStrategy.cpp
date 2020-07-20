#include "stdafx.h"
#include "RegisterStrategy.h"
#include "MessageHandler.h"

RegisterStrategy::RegisterStrategy(string &strName, string &strPassword, string &strPhone)
{
	m_strName = strName;
	m_strPassword = strPassword;
	m_strPhone = strPhone;
}

RegisterStrategy::RegisterStrategy()
{
}


RegisterStrategy::~RegisterStrategy()
{
}

void RegisterStrategy::buildPackage()
{
	//0x01 0x03 xx 05 999999 xxx 0x05 Name 0x06 Password 0x10 Phone 0x10 IP 0x02
	Log_Debug("RegisterStrategy::buildPackage  begin");
	char cDataElement[1024] = "";
	string strIP = HttpClient::getInstance()->getIPAddress();
	memset(cDataElement, 0, sizeof(cDataElement));

	vector<string> vStrData2;
	vStrData2.push_back(strIP);
	vStrData2.push_back(m_strPhone);
	vStrData2.push_back(m_strPassword);

	MessageHandler::buildElement(cDataElement, vStrData2);


	memset(m_cMessagePackage, 0, sizeof(m_cMessagePackage));
	MessageHandler::buildDataElement(m_cMessagePackage, cDataElement, 5, "999999", m_strName.c_str());
	Log_Debug("RegisterPackage::");
	Log_Debug(m_cMessagePackage);
	Log_Debug("RegisterStrategy::buildPackage  end");
}

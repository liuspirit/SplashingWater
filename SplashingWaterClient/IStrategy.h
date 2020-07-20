#pragma once
#include "HttpClient.h"
class IStrategy
{
public:
	virtual inline void processPackage()
	{
		buildPackage();
		HttpClient::getInstance()->sendData(m_cMessagePackage);
	}
	virtual inline void sendPackage()
	{
		buildPackage();
		HttpClient::getInstance()->sendData(m_cMessagePackage);
	}


protected:
	virtual void buildPackage() = 0;

protected:
	char m_cMessagePackage[1024];
};
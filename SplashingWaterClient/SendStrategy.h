#pragma once
#include "IStrategy.h"
class SendStrategy :
	public IStrategy
{
public:
	SendStrategy(string &strFriendAccount, string &strMessage);
	virtual ~SendStrategy();

public:
	virtual void buildPackage();

private:
	SendStrategy();

private:
	string m_strFriendAccount;
	string m_strMessage;
};


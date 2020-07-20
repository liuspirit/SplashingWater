#pragma once
#include "IStrategy.h"
class LogicStrategy :
	public IStrategy
{
public:
	LogicStrategy(string strAccount, string strPassword);
	virtual ~LogicStrategy();

public:
	virtual void buildPackage();

private:
	LogicStrategy();


private:
	string m_strAccount;
	string m_strPassword;
};


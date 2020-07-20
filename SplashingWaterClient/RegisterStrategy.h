#pragma once
#include "IStrategy.h"
class RegisterStrategy :
	public IStrategy
{
public:
	RegisterStrategy(string &strName, string &strPassword, string &strPhone);
	virtual ~RegisterStrategy();

public:
	virtual void buildPackage();

private:
	RegisterStrategy();

private:
	string m_strName;
	string m_strPassword;
	string m_strPhone;
};


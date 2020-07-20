#pragma once
#include "IStrategy.h"
class UpdateStrategy :
	public IStrategy
{
public:
	UpdateStrategy(int &nChoice, string &strAccount);
	virtual ~UpdateStrategy();

public:
	virtual void buildPackage();

private:
	UpdateStrategy();

private:
	int m_nChoice;
	string m_strAccount;
};


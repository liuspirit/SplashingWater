#pragma once
#include "IStrategy.h"

class StateStrategy :
	public IStrategy
{
public:
	StateStrategy(int nStateValue);
	virtual ~StateStrategy();

public:
	virtual void buildPackage();

private:
	StateStrategy();

private:
	int m_nStateValue;
};


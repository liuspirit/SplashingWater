/*
用于管理订阅的主题，如果主题修改，则可以通过通知发给订阅者
*/
#pragma once
#include"ObserverInterface.h"
#include <list>

class ObserverInterface;

struct SubjectData
{
	int nInt;
	double dDouble;
	char pChar[2048];
	char pData2[512];
	SubjectData()
	{
		nInt = 0;
		dDouble = 0;
		memset(pChar, 0, sizeof(pChar));
		memset(pData2, 0, sizeof(pData2));
	}
};

class Subject 
{
public:
	Subject();
	virtual ~Subject();
	
public:
	virtual void addObserver(ObserverInterface *pObserver);
	virtual void deleteObserver(ObserverInterface *pObserver);
	virtual void Notity();
protected:
	struct SubjectData m_SubjectData;
private:
	std::list<ObserverInterface *> m_ObserverList;
};


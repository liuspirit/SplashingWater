#include "stdafx.h"
#include "PipeQueue.h"


PipeQueue::PipeQueue()
{
}


PipeQueue::~PipeQueue()
{
}

void PipeQueue::addPipe(const char* pPipeName)
{

	if (0 == m_MsgPipeGroup.count(pPipeName))
	{
		queue<string> MsgQueue;
		m_MsgPipeGroup.insert(pair<string, queue<string>>(pPipeName, MsgQueue));
		m_MsgPipeFlag.insert(pair<string, bool>(pPipeName, false));
	}
}

void PipeQueue::pushPipeMsg(const char* pPipeName, const char* pMsg)
{
	addPipe(pPipeName);
	m_MsgPipeGroup[pPipeName].push(pMsg);
	m_MsgPipeFlag[pPipeName] = true;
}

void PipeQueue::deletePipe(const char* pPipeName)
{
	if (0 == m_MsgPipeGroup.count(pPipeName))
	{
		return;
	}
	m_MsgPipeGroup.erase(pPipeName);
}

vector<string> PipeQueue::popPipeMsg(const char* pPipeName)
{
	vector<string> vResult;
	if (0 == m_MsgPipeGroup.count(pPipeName))
	{
		throw "popMsg encount exception!";
	}

	string strTemp;
	while (!m_MsgPipeGroup[pPipeName].empty())
	{
		strTemp = m_MsgPipeGroup[pPipeName].front();
		m_MsgPipeGroup[pPipeName].pop();
		vResult.push_back(strTemp);
	}

	m_MsgPipeFlag[pPipeName] = false;

	return vResult;
}

bool PipeQueue::getPipeFlag(const char* pPipeName)
{
	if (0 == m_MsgPipeFlag.count(pPipeName))
	{
		return false;
	}
	return m_MsgPipeFlag[pPipeName];
}
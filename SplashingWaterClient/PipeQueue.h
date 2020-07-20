#pragma once
#include <map>
#include <queue>

class PipeQueue
{
public:
	PipeQueue();
	~PipeQueue();

public:
	void addPipe(const char* pPipeName);
	void pushPipeMsg(const char* pPipeName, const char* pMsg);

	void deletePipe(const char* pPipeName);
	vector<string> popPipeMsg(const char* pPipeName);

	bool getPipeFlag(const char* pPipeName);


private:
	map<string, queue<string>> m_MsgPipeGroup;
	map<string, bool> m_MsgPipeFlag;

};


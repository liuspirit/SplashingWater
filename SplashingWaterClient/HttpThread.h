#pragma once

class HttpThread
{
public:
	HttpThread();
	virtual ~HttpThread();

public:
	void setSleepTime(int nSleepTime);
	void start_Thread();
	void end_Thread();
	void Suspend_Thread();
	bool getThreadRunStatue();
	virtual void run();
	
	static UINT threadFunction(LPVOID pParam);

private:
	void RunInThread();

private:
	bool m_bRunning;
	int m_nSleepTime;
	CWinThread* m_Thread;// = AfxBeginThread(MyThreadFunction, 0, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
};


#include "stdafx.h"
#include "HttpThread.h"


HttpThread::HttpThread()
{
	m_bRunning = false;
	m_nSleepTime = 200;
	m_Thread = AfxBeginThread(threadFunction, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
	Log_Info("HttpThread::HttpThread()------create new thread");
}


HttpThread::~HttpThread()
{
	m_bRunning = false;

	if (m_Thread != NULL)
	{
		delete m_Thread;
		m_Thread = NULL;
	}
}
void HttpThread::setSleepTime(int nSleepTime)
{
	m_nSleepTime = nSleepTime;
}

UINT HttpThread::threadFunction(LPVOID pParam)
{ 
	//线程要调用的函数
	HttpThread *pThread = (HttpThread *)pParam;
	pThread->RunInThread();
	return 0;
}

void HttpThread::RunInThread()
{
	while (m_bRunning)
	{
		run();
		Sleep(m_nSleepTime);
	}
}
void HttpThread::run()
{

}

void HttpThread::start_Thread()
{
	if (m_bRunning == true)
	{
		return;
	}
	m_bRunning = true;
	m_Thread->ResumeThread();//唤醒线程
	Log_Info("HttpThread::start_Thread()------start thread");
}

void HttpThread::end_Thread()
{
	if (m_bRunning == false)
	{
		return;
	}
	m_bRunning = false;
	Log_Info("HttpThread::end_Thread()------wait to end thread...");
	TerminateThread(m_Thread->m_hThread, 0);
	Log_Info("HttpThread::end_Thread()------end thread");
}

void HttpThread::Suspend_Thread()
{
	m_Thread->SuspendThread(); 
}

bool HttpThread::getThreadRunStatue()
{
	DWORD code;
	GetExitCodeThread(m_Thread->m_hThread, &code);  //得到线程状态
	if (code == STILL_ACTIVE)
	{
		return true;
	}
	else
	{
		return false;
	}
}
#pragma once
/*
1.日志创建
2.写入
3.删除文件
4.日志格式定义
日志属性：
格式，级别
时间： 级别：内容

5.日志级别定义
6.外部写入接口
*/
#include "FileOperation.h"

enum LOGLEVEL{ Log_FATAL, Log_ERROR, Log_DEBUG, Log_EVENT };

class LogManager
{
public:
	virtual ~LogManager();

	static LogManager* getInstance(){
		if (m_pInstance == NULL)
		{
			m_pInstance = new LogManager();
		}
		return m_pInstance;
	}

	static void DestoryInstance()
	{
		if (m_pInstance != NULL)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}

	void LogData(const char *pData, LOGLEVEL logLevel);
	
public:
	void setOutLevel(int nLevel);
private:
	LogManager();

	void createFile();

	
	void changeToLogFormat(char *pTargetBuff, int nTargetLen, const char *pSourceData);
	void writeFile(const char * pData);
	void getLogLevel(char *pDataBuff, LOGLEVEL logLevel);

	void createFile(const char *pLogPathFileName);
	void createCurrentDate(char *pCurrentDate);
	void setCurrentPathFileName(char *pLogPathFileName, const char *pCurrentDate, int nFileNum);
	bool judgeCurrentFileOverMax(const char *pLogPathFileName);
	
private:

	string m_strFilePath;
	int m_nLogOutputLevel;
	LOGLEVEL m_CurrentLogLevel;

	FileOperation m_FileOperation;
	static LogManager *m_pInstance;
};



static void Log_Info(const char *pData)
{
	LogManager::getInstance()->LogData(pData, Log_EVENT);
}
static void Log_Debug(const char *pData)
{
	LogManager::getInstance()->LogData(pData, Log_DEBUG);
}
static void Log_Error(const char *pData)
{
	LogManager::getInstance()->LogData(pData, Log_ERROR);
}

static void Log_Fatal(const char *pData)
{
	LogManager::getInstance()->LogData(pData, Log_FATAL);
}




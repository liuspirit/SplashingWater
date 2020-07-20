#pragma once
/*
解析数据包(客户端数据)：

客户端数据到了以后，调用parserMessage，
可以解析出元数据和数据项
通过调用其他函数完成获取

合成数据包:
*/
#include "Observer\Subject.h"
#define DataElementHead1 0x01
#define DataElementHead2 0x03
#define MetaData_Data__INTERVAL 0x05
#define Data_INTERVAL 0x06
#define DataElementTail 0x02
#define FriendList_INTERVAL 0x10

struct ParserResult
{
	string strSourceAccount;
	string strData1;
	string strData2;
	string strData3;
};

#include <vector>
class MessageHandler :public Subject
{
public:
	MessageHandler();
	virtual ~MessageHandler();


public:
	void processMessage(const char *pSource, int nLength);
	ParserResult getResult();
	void test();

	static void buildDataElement(char *pMessagePackage, const char *pDataElement2, int nEvent, const char *pClientAccount, const char *pDataElement1);
	static void buildFriendElement(char *pMessagePackage, const char *pDataName, const char *pDataAccount, const char *pDataStatue);
	static void buildElement(char *pMessagePackage, vector<string> vData);
private:
	void processMetaData(string strSource);
	void processData(string strSource);
	//void buildDataElement(char *pClientMessage, int nEvent, string strClientAccount);
	int converterToInt(const char *pNum, int nLen);

public:
	static char m_cDataHead[3];
	static char m_cEvent[3];
	static char m_cMeta_DataInterval[2];
	static char m_cDataInterval[2];
	static char m_cDataElementTail[2];
	static char m_cDataFriendInterval[2];
private:
	ParserResult m_ParserResult;  //此次处理的元数据结果

};


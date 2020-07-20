#include "stdafx.h"
#include "MessageParser.h"
#include "StrTool.h"

MessageParser::MessageParser()
{
}


MessageParser::~MessageParser()
{
}

//pDes 为空
//0x01 0x03 xx 01 100001 xxx 0x05 100002 0x06 This is Client 0x02
void MessageParser ::converterToTrans(const char *pSource, char *pDes)
{
	if (!pDes || !pSource)
	{
		throw exception("Source and Des is null!");
	}

	//pSendData, strlen(pSendData)
	
	//数据头
	string strClientAccount = "100001";
	string strMessage = pSource;
	string strFriendAccount = "100001";
	int nDataSize = strFriendAccount.size() + strMessage.size() + 1;
	string strDataSize = StrTool::ToString(nDataSize);
	int nMetaSize = 4 + strClientAccount.size() + strDataSize.size();
	string strMetaDataSize = StrTool::ToString(nMetaSize);

	char cDataHead[3] = { DataElementHead1, DataElementHead2, '\0' };
	char cEvent[3] = { '0', '1', '\0' };
	char cMeta_DataInterval[2] = { MetaData_Data__INTERVAL, '\0' };
	char cDataInterval[2] = { Data_INTERVAL, '\0' };
	char cDataElementTail[2] = { DataElementTail, '\0' };


	strcpy(pDes, cDataHead);
	strcat(pDes, strMetaDataSize.c_str());
	strcat(pDes, cEvent);
	strcat(pDes, strClientAccount.c_str());
	strcat(pDes, strDataSize.c_str());
	strcat(pDes, cMeta_DataInterval);
	strcat(pDes, strFriendAccount.c_str());

	strcat(pDes, cDataInterval);
	strcat(pDes, strMessage.c_str());
	strcat(pDes, cDataElementTail);
	int nSize = strlen(pDes);
	
}

/*
void MessageParser::buildDataElement(char *pClientMessage, int nEvent, string strClientAccount)
{
	//数据头
	char cDataHead[3] = { DataElementHead1, DataElementHead2, '\0' };
	char cEvent[3] = { '0', nEvent + '0', '\0' };

	char cMeta_DataInterval[2] = { MetaData_Data__INTERVAL, '\0' };
	char cDataInterval[2] = { Data_INTERVAL, '\0' };
	char cDataElementTail[2] = { DataElementTail, '\0' };

	string strMessage = "This is Client";
	string strFriendAccount = "100002";
	int nDataSize = strFriendAccount.size() + strMessage.size() + 1;

	string strDataSize = StrTool::ToString(nDataSize);

	int nMetaSize = 4 + strClientAccount.size() + strDataSize.size();
	string strMetaDataSize = StrTool::ToString(nMetaSize);


	strcpy(pClientMessage, cDataHead);
	strcat(pClientMessage, strMetaDataSize.c_str());
	strcat(pClientMessage, cEvent);
	strcat(pClientMessage, strClientAccount.c_str());
	strcat(pClientMessage, strDataSize.c_str());
	strcat(pClientMessage, cMeta_DataInterval);
	strcat(pClientMessage, strFriendAccount.c_str());

	strcat(pClientMessage, cDataInterval);
	strcat(pClientMessage, strMessage.c_str());
	strcat(pClientMessage, cDataElementTail);

	int nSize = strlen(pClientMessage);
	//sprintf(cClientMessage, "%s%s%s%s%c%s%c%s%c", cDataHead, strMetaDataSize.c_str(), cEvent, strClientAccount.c_str(), 0x05,strFriendAccount, 0x06, strMessage,0x02);


}*/


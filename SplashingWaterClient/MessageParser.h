#pragma once

#define DataElementHead1 0x01
#define DataElementHead2 0x03
#define MetaData_Data__INTERVAL 0x05
#define Data_INTERVAL 0x06
#define DataElementTail 0x02

class MessageParser
{
public:
	MessageParser();
	~MessageParser();

public:
	static void converterToTrans(const char *pSource, char *pDes);
};


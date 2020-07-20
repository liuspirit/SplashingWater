#pragma once
#include <string>
#include "stdafx.h"
class Converter
{
public:
	Converter();
	~Converter();

	//to CString
	static CString toCString(int nValue);
	static CString toCString(std::string strValue);
	//To int
	static int toInt(CString CStrValue);
	//to string
	static std::string toString(CString CStrValue);
	static std::string toString(int nValue);
};


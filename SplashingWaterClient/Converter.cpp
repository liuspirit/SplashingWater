
#include "Converter.h"
using namespace std;

Converter::Converter()
{
}


Converter::~Converter()
{
}

CString Converter::toCString(int nValue)
{
	CString CStrValue;
	CStrValue.Format(_T("%d"), nValue);
	return CStrValue;
}

CString Converter::toCString(string strValue)
{
	CString CStrCommand;
	CStrCommand = strValue.c_str();
	return CStrCommand;
}

int Converter::toInt(CString CStrValue)
{
	int nValue = atoi(CT2A(CStrValue.GetBuffer()));
	return nValue;
}

string Converter::toString(CString CStrValue)
{
	string strValue = CT2A(CStrValue.GetBuffer());
	return strValue;
}
string  Converter::toString(int nValue)
{
	return std::to_string(nValue);
}

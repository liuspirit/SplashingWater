#include "stdafx.h"
#include "ConfigReader.h"
#include "Converter.h"
ConfigReader::ConfigReader()
{
	m_cstrConfigFileAddr = "";
	m_cstrConfigFileName = _T("SystemConfig.ini");
	m_bConfigFlag = false;
}


ConfigReader::~ConfigReader()
{
}


CString ConfigReader::read(CString cstrKey)
{
	config();
	CString strData;
	::GetPrivateProfileStringW(_T("SystemConfigParameter"), cstrKey, _T("没找到Value信息"), strData.GetBuffer(MAX_PATH), MAX_PATH, m_cstrAddrName);
	strData.ReleaseBuffer();
	return strData;
}
string ConfigReader::read(string strKey)
{
	CString cstrData = read(Converter::toCString(strKey));
	return Converter::toString(cstrData);
}

void  ConfigReader::write(string strKey, string cstrValue)
{
	write(Converter::toCString(strKey), Converter::toCString(cstrValue));
}

void ConfigReader::write(CString cstrKey, CString cstrValue)
{
	//head,key,value,file
	config();
	::WritePrivateProfileStringW(_T("SystemConfigParameter"), cstrKey, cstrValue, m_cstrAddrName);
}

void ConfigReader::config()
{
	if (m_bConfigFlag)
	{
		return;
	}
	CString path;
	GetModuleFileName(NULL, path.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	path.ReleaseBuffer();
	int pos = path.ReverseFind('\\');
	m_cstrConfigFileAddr = path.Left(pos);

	if (m_cstrConfigFileAddr == "")
	{
		throw exception("ConfigReader::config has one exception: cann't get Configure file address");
	}
	m_cstrAddrName = m_cstrConfigFileAddr + "\\" +m_cstrConfigFileName;
	m_bConfigFlag = true;
}
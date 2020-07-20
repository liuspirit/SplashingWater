#pragma once
#include <string>
using namespace std;


class ConfigReader
{
public:
	ConfigReader();
	~ConfigReader();

public:
	string read(string strKey);
	CString read(CString cstrKey);

	void write(string strKey, string cstrValue);
	void write(CString cstrKey, CString cstrValue);

private:
	void config();

private:
	CString m_cstrConfigFileAddr;
	CString m_cstrConfigFileName;
	CString m_cstrAddrName;
	bool m_bConfigFlag;
};


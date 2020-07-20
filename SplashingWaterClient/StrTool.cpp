#include "StrTool.h"
#include <sstream>

StrTool::StrTool()
{
}


StrTool::~StrTool()
{
}
bool StrTool::SplitString(const string& strSource, vector<string>& vResult, char delimiters)
{
	string::size_type pos1, pos2;
	pos2 = strSource.find(delimiters);
	pos1 = 0;
	while (string::npos != pos2)
	{
		vResult.push_back(strSource.substr(pos1, pos2 - pos1));

		pos1 = pos2 + 1;
		pos2 = strSource.find(delimiters, pos1);
	}

	if (pos1 != strSource.length())
	{
		vResult.push_back(strSource.substr(pos1));
		return true;
	}
	else
	{
		return false;
	}
}

bool StrTool::SplitString(const string& strSource, vector<string>& vResult, const string& delimiters)
{
	string::size_type pos1, pos2;
	pos2 = strSource.find(delimiters);
	pos1 = 0;
	while (string::npos != pos2)
	{
		vResult.push_back(strSource.substr(pos1, pos2 - pos1));

		pos1 = pos2 + delimiters.size();
		pos2 = strSource.find(delimiters, pos1);
	}

	if (pos1 != strSource.length())
	{
		vResult.push_back(strSource.substr(pos1));
		return true;
	}
	else
	{
		return false;
	}
		
}
int StrTool::ToInt(string strSource)
{
	return stoi(strSource);
}

string StrTool::ToString(int nSource)
{
	stringstream ss;
	ss << nSource;
	return ss.str();
}
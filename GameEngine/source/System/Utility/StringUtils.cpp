#include "System/Utility/StringUtils.h"

StringUtils::StringUtils()
{
}

StringUtils::~StringUtils()
{
}

float StringUtils::toFloat(const std::string& s)
{
	try
	{
		return std::stof(s);
	}
	catch (...)
	{
		return 0.f;
	}
}

int StringUtils::toInt(const std::string& s)
{
	try
	{
		return std::stoi(s);
	}
	catch (...)
	{
		return 0;
	}
}

bool StringUtils::toBool(const std::string& s)
{
	if (s == "t" || s == "true" || s == "1")
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::vector<std::string> StringUtils::splitString(std::string& s, char cSplitChar)
{
	std::vector<std::string> data;
	std::stringstream ss(s);
	std::string temp;
	while (std::getline(ss, temp, cSplitChar))
	{
		data.push_back(temp);
	}
	return data;
}
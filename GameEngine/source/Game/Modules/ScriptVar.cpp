#include "Game/Modules/ScriptVar.h"

ScriptVar::ScriptVar()
{
	m_activeType = SupportedTypes::VOID;
}

ScriptVar::ScriptVar(std::string& sVal)
{
	m_activeType = SupportedTypes::STRING;
	std::string* s = new std::string(sVal);
	m_stringField = s;
}

ScriptVar::ScriptVar(int iVal)
{
	m_activeType = SupportedTypes::INT;
	m_intField = iVal;
}

ScriptVar::ScriptVar(float fVal)
{
	m_activeType = SupportedTypes::FLOAT;
	m_floatField = fVal;
}

ScriptVar::ScriptVar(bool bVal)
{
	m_activeType = SupportedTypes::BOOL;
	m_boolField = bVal;
}

ScriptVar::ScriptVar(const ScriptVar& other)
{
	// Need to perform a deep copy for strings
	m_activeType = other.m_activeType;
	if (m_activeType == SupportedTypes::STRING)
	{
		std::string* s = new std::string(*other.m_stringField);
		m_stringField = s;
	}
	else if (m_activeType == SupportedTypes::INT)
	{
		m_intField = other.m_intField;
	}
	else if (m_activeType == SupportedTypes::FLOAT)
	{
		m_floatField = other.m_floatField;
	}
	else if (m_activeType == SupportedTypes::BOOL)
	{
		m_boolField = other.m_boolField;
	}
}

ScriptVar& ScriptVar::operator=(const ScriptVar& other)
{
	// Need to perform a deep copy for strings
	m_activeType = other.m_activeType;
	if (m_activeType == SupportedTypes::STRING)
	{
		std::string* s = new std::string(*other.m_stringField);
		m_stringField = s;
	}
	else if (m_activeType == SupportedTypes::INT)
	{
		m_intField = other.m_intField;
	}
	else if (m_activeType == SupportedTypes::FLOAT)
	{
		m_floatField = other.m_floatField;
	}
	else if (m_activeType == SupportedTypes::BOOL)
	{
		m_boolField = other.m_boolField;
	}
	return *this;
}

ScriptVar::~ScriptVar()
{
	if (m_activeType == SupportedTypes::STRING)
	{
		delete m_stringField;
	}
}

const ScriptVar::SupportedTypes& ScriptVar::getType() const
{
	return m_activeType;
}

const std::string& ScriptVar::getString() const
{
	return *m_stringField;
}

int ScriptVar::getInt() const
{
	return m_intField;
}

float ScriptVar::getFloat() const
{
	return m_floatField;
}

bool ScriptVar::getBool() const
{
	return m_boolField;
}

void ScriptVar::setString(const std::string& sVal)
{
	m_activeType = SupportedTypes::STRING;
	m_stringField = new std::string(sVal);
}

void ScriptVar::setInt(int iVal)
{
	m_activeType = SupportedTypes::INT;
	m_intField = iVal;
}

void ScriptVar::setFloat(float fVal)
{
	m_activeType = SupportedTypes::FLOAT;
	m_floatField = fVal;
}

void ScriptVar::setBool(bool bVal)
{
	m_activeType = SupportedTypes::BOOL;
	m_boolField = bVal;
}	

std::string ScriptVar::typeToString(SupportedTypes type)
{
	switch (type)
	{
	case ScriptVar::SupportedTypes::STRING:
		return "string";
	case ScriptVar::SupportedTypes::INT:
		return "int";
	case ScriptVar::SupportedTypes::FLOAT:
		return "float";
	case ScriptVar::SupportedTypes::BOOL:
		return "bool";
	case ScriptVar::SupportedTypes::VOID:
		return "void";
	default:
		return "void";
	}
}
#include "Game/Modules/ScriptParam.h"

ScriptParam::ScriptParam()
{
	m_type = Type::NULL_PARAM;
	m_value = new ScriptVar();
}

ScriptParam::ScriptParam(Function* function)
{
	m_function = function;
	m_type = Type::FUNCTION;
}

ScriptParam::ScriptParam(ScriptVar& scriptVar, bool bIsRef)
{	
	if (bIsRef)
	{
		m_type = Type::REFERENCE;
		m_value = &scriptVar;
	}
	else
	{
		m_type = Type::VALUE;
		m_value = new ScriptVar(scriptVar);
	}
}

ScriptParam::ScriptParam(const ScriptParam& other)
{
	// Need to perform a deep copy for values
	m_type = other.m_type;
	if (m_type == Type::VALUE)
	{
		m_value = new ScriptVar(*other.m_value);
	}
	else if (m_type == Type::REFERENCE)
	{
		m_value = other.m_value;
	}
	else if (m_type == Type::FUNCTION)
	{
		m_function = other.m_function;
	}
	else if (m_type == Type::NULL_PARAM)
	{
		m_value = new ScriptVar(*other.m_value);
	}
}

ScriptParam& ScriptParam::operator=(const ScriptParam& other)
{
	// Need to perform a deep copy for values
	m_type = other.m_type;
	if (m_type == Type::VALUE)
	{
		m_value = new ScriptVar(*other.m_value);
	}
	else if (m_type == Type::REFERENCE)
	{
		m_value = other.m_value;
	}
	else if (m_type == Type::FUNCTION)
	{
		m_function = other.m_function;
	}
	else if (m_type == Type::NULL_PARAM)
	{
		m_value = new ScriptVar(*other.m_value);
	}
	return *this;
}

ScriptParam::~ScriptParam()
{
	if (m_type == Type::VALUE || m_type == Type::NULL_PARAM)
	{
		delete m_value;
	}
}

const ScriptParam::Type& ScriptParam::getType() const
{
	return m_type;
}

const ScriptVar::SupportedTypes& ScriptParam::getReturnType() const
{
	if (m_type == Type::FUNCTION)
	{
		return m_function->getReturnType();
	}
	else
	{
		return m_value->getType();
	}
}

ScriptVar& ScriptParam::getValue(ScriptInfoPack& pack)
{
	if (m_type == Type::FUNCTION)
	{
		return m_function->execute(pack);
	}
	else if (m_type == Type::REFERENCE)
	{
		return *m_value;
	}
	else if (m_type == Type::VALUE)
	{
		return *m_value;
	}
	else
	{
		// This is the return value for a NULL_PARAM parameter. Realistically it should not
		// be being called, but it exists for testing and keeping the compiler happy purposes
		return *m_value;
	}
}
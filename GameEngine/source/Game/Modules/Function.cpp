#include "Game/Modules/Function.h"

Function::Function(ScriptVar::SupportedTypes returnType)
{
	m_returnType = returnType;
	m_returnVal = ScriptVar();
}

bool Function::addParamDefinition(ParamDefinition& definition)
{
	// Prevent duplicate definitions
	for (ParamDefinition& def : m_paramDefinitions)
	{
		if (def == definition)
		{
			return false;
		}
	}

	m_paramDefinitions.push_back(definition);
	return true;
}

bool Function::hasParamDefinition(const ParamDefinition& definition)
{
	for (ParamDefinition& def : m_paramDefinitions)
	{
		if (def == definition)
		{
			return true;
		}
	}

	return false;
}

const std::vector<ParamDefinition>& Function::getDefinitions() const
{
	return m_paramDefinitions;
}

const ScriptVar::SupportedTypes& Function::getReturnType() const
{
	return m_returnType;
}
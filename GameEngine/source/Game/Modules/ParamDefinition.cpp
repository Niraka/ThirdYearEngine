#include "Game/Modules/ParamDefinition.h"

ParamDefinition::ParamDefinition()
{
}

ParamDefinition::ParamDefinition(ScriptVar::SupportedTypes type1)
{
	m_params.push_back(type1);
}

ParamDefinition::ParamDefinition(ScriptVar::SupportedTypes type1, ScriptVar::SupportedTypes type2)
{
	m_params.push_back(type1);
	m_params.push_back(type2);
}

ParamDefinition::ParamDefinition(std::vector<ScriptVar::SupportedTypes> types)
{
	m_params = types;
}

bool ParamDefinition::operator==(const ParamDefinition& other)
{
	if (m_params.size() != other.m_params.size())
	{
		return false;
	}

	unsigned int uiCrnt = 0;
	unsigned int uiSize = m_params.size();
	for (; uiCrnt < uiSize; ++uiCrnt)
	{
		if (m_params.at(uiCrnt) != other.m_params.at(uiCrnt))
		{
			return false;
		}
	}

	return true;
}

std::string ParamDefinition::toString() const
{
	std::string s = "(";

	unsigned int uiCrnt = 0;
	unsigned int uiSize = m_params.size();
	for (; uiCrnt < uiSize; ++uiCrnt)
	{
		s += ScriptVar::typeToString(m_params.at(uiCrnt));
		if (uiCrnt + 1 < uiSize)
		{
			s += ", ";
		}
	}

	s += ")";

	return s;
}
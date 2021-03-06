#include "Game/Modules/FunctionEqual.h"

FunctionEqual::FunctionEqual(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::BOOL)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::INT, ScriptVar::SupportedTypes::FLOAT));
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::FLOAT, ScriptVar::SupportedTypes::INT));
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::INT, ScriptVar::SupportedTypes::INT));
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::FLOAT, ScriptVar::SupportedTypes::FLOAT));

	m_first = params.at(0);
	m_second = params.at(1);
}

FunctionEqual::~FunctionEqual()
{
}

ScriptVar& FunctionEqual::execute(ScriptInfoPack& pack)
{
	float fFirst;
	float fSecond;
	if (m_first.getReturnType() == ScriptVar::SupportedTypes::INT)
	{
		fFirst = (float)m_first.getValue(pack).getInt();
	}
	else
	{
		fFirst = m_first.getValue(pack).getFloat();
	}
	if (m_second.getReturnType() == ScriptVar::SupportedTypes::INT)
	{
		fSecond = (float)m_second.getValue(pack).getInt();
	}
	else
	{
		fSecond = m_second.getValue(pack).getFloat();
	}

	m_returnVal.setBool(fFirst == fSecond);

	return m_returnVal;
}
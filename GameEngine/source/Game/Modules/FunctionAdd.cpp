#include "Game/Modules/FunctionAdd.h"

FunctionAdd::FunctionAdd(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::INT, ScriptVar::SupportedTypes::INT));
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::FLOAT, ScriptVar::SupportedTypes::FLOAT));

	m_first = params.at(0);
	m_second = params.at(1);
}

FunctionAdd::~FunctionAdd()
{
}

ScriptVar& FunctionAdd::execute(ScriptInfoPack& pack)
{
	if (m_first.getReturnType() == ScriptVar::SupportedTypes::INT)
	{
		m_first.getValue(pack).setInt(m_first.getValue(pack).getInt() + m_second.getValue(pack).getInt());
	}
	else
	{
		m_first.getValue(pack).setFloat(m_first.getValue(pack).getFloat() + m_second.getValue(pack).getFloat());
	}

	return m_returnVal;
}
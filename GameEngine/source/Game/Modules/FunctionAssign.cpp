#include "Game/Modules/FunctionAssign.h"

FunctionAssign::FunctionAssign(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::BOOL, ScriptVar::SupportedTypes::BOOL));
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::FLOAT, ScriptVar::SupportedTypes::FLOAT));
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::INT, ScriptVar::SupportedTypes::INT));
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::STRING, ScriptVar::SupportedTypes::STRING));

	m_variable = params.at(0);
	m_value = params.at(1);
}

FunctionAssign::~FunctionAssign()
{
}

ScriptVar& FunctionAssign::execute(ScriptInfoPack& pack)
{
	ScriptVar::SupportedTypes type = m_variable.getValue(pack).getType();
	switch (type)
	{
	case ScriptVar::SupportedTypes::STRING:		
		m_variable.getValue(pack).setString(m_value.getValue(pack).getString());
		break;
	case ScriptVar::SupportedTypes::INT:
		m_variable.getValue(pack).setInt(m_value.getValue(pack).getInt());
		break;
	case ScriptVar::SupportedTypes::FLOAT:
		m_variable.getValue(pack).setFloat(m_value.getValue(pack).getFloat());
		break;
	case ScriptVar::SupportedTypes::BOOL:
		m_variable.getValue(pack).setBool(m_value.getValue(pack).getBool());
		break;
	default:
		break;
	}

	return m_returnVal;
}
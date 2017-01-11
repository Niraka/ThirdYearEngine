#include "Game/Modules/FunctionLog.h"

FunctionLog::FunctionLog(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::BOOL));
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::FLOAT));
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::INT));
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::STRING));

	m_value = params.at(0);
}

FunctionLog::~FunctionLog()
{
}

ScriptVar& FunctionLog::execute(ScriptInfoPack& pack)
{
	if (pack.loggerNode)
	{
		ScriptVar::SupportedTypes type = m_value.getValue(pack).getType();
		switch (type)
		{
		case ScriptVar::SupportedTypes::STRING:
			pack.loggerNode->log(m_value.getValue(pack).getString());
			break;
		case ScriptVar::SupportedTypes::INT:
			pack.loggerNode->log(std::to_string(m_value.getValue(pack).getInt()));
			break;
		case ScriptVar::SupportedTypes::FLOAT:
			pack.loggerNode->log(std::to_string(m_value.getValue(pack).getFloat()));
			break;
		case ScriptVar::SupportedTypes::BOOL:
			pack.loggerNode->log(std::to_string(m_value.getValue(pack).getBool()));
			break;
		default:
			break;
		}
	}

	return m_returnVal;
}
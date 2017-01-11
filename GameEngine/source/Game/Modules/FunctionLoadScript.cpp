#include "Game/Modules/FunctionLoadScript.h"

FunctionLoadScript::FunctionLoadScript(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::STRING, ScriptVar::SupportedTypes::STRING));

	m_scriptName = params.at(0);
	m_fileName = params.at(1);
}

FunctionLoadScript::~FunctionLoadScript()
{
}

ScriptVar& FunctionLoadScript::execute(ScriptInfoPack& pack)
{
	if (pack.actionTerminal)
	{
		pack.actionTerminal->loadScript(
			m_scriptName.getValue(pack).getString(),
			m_fileName.getValue(pack).getString());
	}
	return m_returnVal;
}
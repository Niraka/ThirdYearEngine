#include "Game/Modules/FunctionExecuteScript.h"

FunctionExecuteScript::FunctionExecuteScript(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::STRING));

	m_scriptName = params.at(0);
}

FunctionExecuteScript::~FunctionExecuteScript()
{
}

ScriptVar& FunctionExecuteScript::execute(ScriptInfoPack& pack)
{
	if (pack.actionTerminal)
	{
		pack.actionTerminal->executeScript(m_scriptName.getValue(pack).getString());
	}
	return m_returnVal;
}
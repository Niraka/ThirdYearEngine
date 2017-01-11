#include "Game/Modules/FunctionUnloadScript.h"

FunctionUnloadScript::FunctionUnloadScript(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::STRING));

	m_scriptName = params.at(0);
}

FunctionUnloadScript::~FunctionUnloadScript()
{
}

ScriptVar& FunctionUnloadScript::execute(ScriptInfoPack& pack)
{
	if (pack.actionTerminal)
	{
		pack.actionTerminal->unloadScript(m_scriptName.getValue(pack).getString());
	}
	return m_returnVal;
}
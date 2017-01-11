#include "Game/Modules/FunctionIf.h"

FunctionIf::FunctionIf(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	std::vector<ScriptVar::SupportedTypes> types;
	types.push_back(ScriptVar::SupportedTypes::BOOL);
	types.push_back(ScriptVar::SupportedTypes::STRING);
	types.push_back(ScriptVar::SupportedTypes::STRING);
	addParamDefinition(ParamDefinition(types));

	m_condition = params.at(0);
	m_script1 = params.at(1);
	m_script2 = params.at(2);
}

FunctionIf::~FunctionIf()
{
}

ScriptVar& FunctionIf::execute(ScriptInfoPack& pack)
{
	if (m_condition.getValue(pack).getBool())
	{
		pack.actionTerminal->executeScript(m_script1.getValue(pack).getString());
	}
	else
	{
		pack.actionTerminal->executeScript(m_script2.getValue(pack).getString());
	}
	return m_returnVal;
}
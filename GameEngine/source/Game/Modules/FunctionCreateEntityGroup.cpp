#include "Game/Modules/FunctionCreateEntityGroup.h"

FunctionCreateEntityGroup::FunctionCreateEntityGroup(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::STRING));

	m_groupName = params.at(0);
}

FunctionCreateEntityGroup::~FunctionCreateEntityGroup()
{
}

ScriptVar& FunctionCreateEntityGroup::execute(ScriptInfoPack& pack)
{
	if (pack.entityModule)
	{
		pack.entityModule->createEntityGroup(m_groupName.getValue(pack).getString());
	}
	return m_returnVal;
}
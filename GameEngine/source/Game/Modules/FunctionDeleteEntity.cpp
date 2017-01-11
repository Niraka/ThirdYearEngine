#include "Game/Modules/FunctionDeleteEntity.h"

FunctionDeleteEntity::FunctionDeleteEntity(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::INT));

	m_entityId = params.at(0);
}

FunctionDeleteEntity::~FunctionDeleteEntity()
{
}

ScriptVar& FunctionDeleteEntity::execute(ScriptInfoPack& pack)
{
	if (pack.entityModule)
	{
		pack.entityModule->deleteEntity((unsigned int)m_entityId.getValue(pack).getInt());
	}
	return m_returnVal;
}
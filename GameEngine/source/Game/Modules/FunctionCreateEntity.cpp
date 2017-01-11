#include "Game/Modules/FunctionCreateEntity.h"

FunctionCreateEntity::FunctionCreateEntity(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::INT)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::STRING));
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::STRING, ScriptVar::SupportedTypes::STRING));

	m_specName = params.at(0);

	if (params.size() == 2)
	{
		m_groupName = params.at(1);
	}
	else
	{
		std::string sNoGroup = "";
		m_groupName = ScriptParam(ScriptVar(sNoGroup), false);
	}
}

FunctionCreateEntity::~FunctionCreateEntity()
{
}

ScriptVar& FunctionCreateEntity::execute(ScriptInfoPack& pack)
{
	if (pack.entityModule)
	{
		m_returnVal.setInt((int)pack.entityModule->createEntity(
			m_specName.getValue(pack).getString(),
			m_groupName.getValue(pack).getString()));
	}
	return m_returnVal;
}
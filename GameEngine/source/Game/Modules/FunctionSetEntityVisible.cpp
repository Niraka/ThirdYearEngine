#include "Game/Modules/FunctionSetEntityVisible.h"

FunctionSetEntityVisible::FunctionSetEntityVisible(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::INT, ScriptVar::SupportedTypes::BOOL));

	m_entityId = params.at(0);
	m_visible = params.at(1);
}

FunctionSetEntityVisible::~FunctionSetEntityVisible()
{
}

ScriptVar& FunctionSetEntityVisible::execute(ScriptInfoPack& pack)
{
	if (pack.entityModule)
	{
		std::shared_ptr<Entity> entity = pack.entityModule->getEntity(m_entityId.getValue(pack).getInt());
		if (entity)
		{
			entity->setVisible(m_visible.getValue(pack).getBool());
		}
	}

	return m_returnVal;
}
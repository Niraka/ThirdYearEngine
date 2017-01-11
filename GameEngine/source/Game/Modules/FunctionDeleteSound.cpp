#include "Game/Modules/FunctionDeleteSound.h"

FunctionDeleteSound::FunctionDeleteSound(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::INT, ScriptVar::SupportedTypes::STRING));

	m_entityId = params.at(0);
	m_soundName = params.at(1);
}

FunctionDeleteSound::~FunctionDeleteSound()
{
}

ScriptVar& FunctionDeleteSound::execute(ScriptInfoPack& pack)
{
	if (pack.entityModule)
	{
		std::shared_ptr<Entity> entity = pack.entityModule->getEntity(m_entityId.getValue(pack).getInt());
		if (entity)
		{
			entity->deleteSound(m_soundName.getValue(pack).getString());
		}
	}
	return m_returnVal;
}
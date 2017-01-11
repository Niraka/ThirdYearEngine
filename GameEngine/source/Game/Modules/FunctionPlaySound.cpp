#include "Game/Modules/FunctionPlaySound.h"

FunctionPlaySound::FunctionPlaySound(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::INT, ScriptVar::SupportedTypes::STRING));

	m_entityId = params.at(0);
	m_soundName = params.at(1);
}

FunctionPlaySound::~FunctionPlaySound()
{
}

ScriptVar& FunctionPlaySound::execute(ScriptInfoPack& pack)
{
	if (pack.entityModule)
	{
		std::shared_ptr<Entity> entity = pack.entityModule->getEntity(m_entityId.getValue(pack).getInt());
		if (entity)
		{
			entity->playSound(m_soundName.getValue(pack).getString());
		}
	}
	return m_returnVal;
}
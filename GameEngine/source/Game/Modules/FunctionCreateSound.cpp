#include "Game/Modules/FunctionCreateSound.h"

FunctionCreateSound::FunctionCreateSound(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::BOOL)
{
	std::vector<ScriptVar::SupportedTypes> types;
	types.push_back(ScriptVar::SupportedTypes::INT);
	types.push_back(ScriptVar::SupportedTypes::STRING);
	types.push_back(ScriptVar::SupportedTypes::STRING);
	addParamDefinition(ParamDefinition(types));

	m_entityId = params.at(0);
	m_soundName = params.at(1);
	m_channelName = params.at(2);
}

FunctionCreateSound::~FunctionCreateSound()
{
}

ScriptVar& FunctionCreateSound::execute(ScriptInfoPack& pack)
{
	if (pack.entityModule)
	{
		std::shared_ptr<Entity> entity = pack.entityModule->getEntity(m_entityId.getValue(pack).getInt());
		if (entity)
		{
			m_returnVal.setBool(entity->createSound(m_soundName.getValue(pack).getString(),
				m_channelName.getValue(pack).getString()));
		}
	}
	return m_returnVal;
}
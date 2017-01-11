#include "Game/Modules/FunctionSetSoundAttenuation.h"

FunctionSetSoundAttenuation::FunctionSetSoundAttenuation(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	std::vector<ScriptVar::SupportedTypes> types;
	types.push_back(ScriptVar::SupportedTypes::INT);
	types.push_back(ScriptVar::SupportedTypes::STRING);
	types.push_back(ScriptVar::SupportedTypes::FLOAT);

	addParamDefinition(ParamDefinition(types));

	m_entityId = params.at(0);
	m_soundName = params.at(1);
	m_attenuation = params.at(2);
}

FunctionSetSoundAttenuation::~FunctionSetSoundAttenuation()
{
}

ScriptVar& FunctionSetSoundAttenuation::execute(ScriptInfoPack& pack)
{
	if (pack.entityModule)
	{
		std::shared_ptr<Entity> entity = pack.entityModule->getEntity(m_entityId.getValue(pack).getInt());
		if (entity)
		{
			entity->setSoundAttenuation(m_soundName.getValue(pack).getString(),
				m_attenuation.getValue(pack).getFloat());
		}
	}
	return m_returnVal;
}
#include "Game/Modules/FunctionSetSoundListenerPosition.h"

FunctionSetSoundListenerPosition::FunctionSetSoundListenerPosition(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::BOOL)
{
	std::vector<ScriptVar::SupportedTypes> types;
	types.push_back(ScriptVar::SupportedTypes::FLOAT);
	types.push_back(ScriptVar::SupportedTypes::FLOAT);
	types.push_back(ScriptVar::SupportedTypes::FLOAT);
	addParamDefinition(ParamDefinition(types));

	m_x = params.at(0);
	m_y = params.at(1);
	m_z = params.at(2);
}

FunctionSetSoundListenerPosition::~FunctionSetSoundListenerPosition()
{
}

ScriptVar& FunctionSetSoundListenerPosition::execute(ScriptInfoPack& pack)
{
	if (pack.audioModule)
	{
		pack.audioModule->setListenerPosition(glm::vec3(
			m_x.getValue(pack).getFloat(),
			m_y.getValue(pack).getFloat(),
			m_z.getValue(pack).getFloat()));
	}
	return m_returnVal;
}
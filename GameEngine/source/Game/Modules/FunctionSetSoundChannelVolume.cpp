#include "Game/Modules/FunctionSetSoundChannelVolume.h"

FunctionSetSoundChannelVolume::FunctionSetSoundChannelVolume(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::BOOL)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::STRING, ScriptVar::SupportedTypes::FLOAT));

	m_channelName = params.at(0);
	m_volume = params.at(1);
}

FunctionSetSoundChannelVolume::~FunctionSetSoundChannelVolume()
{
}

ScriptVar& FunctionSetSoundChannelVolume::execute(ScriptInfoPack& pack)
{
	if (pack.audioModule)
	{
		pack.audioModule->setChannelVolume(m_channelName.getValue(pack).getString(),
			m_volume.getValue(pack).getFloat());
	}
	return m_returnVal;
}
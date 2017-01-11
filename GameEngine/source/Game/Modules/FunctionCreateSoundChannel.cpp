#include "Game/Modules/FunctionCreateSoundChannel.h"

FunctionCreateSoundChannel::FunctionCreateSoundChannel(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::BOOL)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::STRING));

	m_channelName = params.at(0);
}

FunctionCreateSoundChannel::~FunctionCreateSoundChannel()
{
}

ScriptVar& FunctionCreateSoundChannel::execute(ScriptInfoPack& pack)
{
	if (pack.audioModule)
	{
		m_returnVal.setBool(pack.audioModule->createChannel(m_channelName.getValue(pack).getString()));
	}
	return m_returnVal;
}
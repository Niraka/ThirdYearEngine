#include "Game/Modules/FunctionLoadSound.h"

FunctionLoadSound::FunctionLoadSound(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::STRING, ScriptVar::SupportedTypes::STRING));

	m_soundName = params.at(0);
	m_fileName = params.at(1);
}

FunctionLoadSound::~FunctionLoadSound()
{
}

ScriptVar& FunctionLoadSound::execute(ScriptInfoPack& pack)
{
	if (pack.audioModule)
	{
		pack.audioModule->loadSoundBuffer(
			m_fileName.getValue(pack).getString(),
			m_soundName.getValue(pack).getString());
	}
	return m_returnVal;
}
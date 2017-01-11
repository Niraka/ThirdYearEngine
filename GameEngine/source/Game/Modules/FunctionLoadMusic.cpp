#include "Game/Modules/FunctionLoadMusic.h"

FunctionLoadMusic::FunctionLoadMusic(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::STRING, ScriptVar::SupportedTypes::STRING));

	m_musicName = params.at(0);
	m_fileName = params.at(1);
}

FunctionLoadMusic::~FunctionLoadMusic()
{
}

ScriptVar& FunctionLoadMusic::execute(ScriptInfoPack& pack)
{
	if (pack.audioModule)
	{
		pack.audioModule->loadMusic(
			m_fileName.getValue(pack).getString(),
			m_musicName.getValue(pack).getString());
	}
	return m_returnVal;
}
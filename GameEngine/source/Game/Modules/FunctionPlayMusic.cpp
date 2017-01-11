#include "Game/Modules/FunctionPlayMusic.h"

FunctionPlayMusic::FunctionPlayMusic(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	std::vector<ScriptVar::SupportedTypes> types;
	types.push_back(ScriptVar::SupportedTypes::STRING);
	types.push_back(ScriptVar::SupportedTypes::BOOL);
	types.push_back(ScriptVar::SupportedTypes::FLOAT);
	addParamDefinition(ParamDefinition(types));

	m_musicName = params.at(0);
	m_loopEnabled = params.at(1);
	m_transitionDuration = params.at(2);
}

FunctionPlayMusic::~FunctionPlayMusic()
{

}

ScriptVar& FunctionPlayMusic::execute(ScriptInfoPack& pack)
{
	if (pack.audioModule)
	{
		pack.audioModule->playMusic(m_musicName.getValue(pack).getString(),
			m_loopEnabled.getValue(pack).getBool(),
			m_transitionDuration.getValue(pack).getFloat());
	}

	return m_returnVal;
}
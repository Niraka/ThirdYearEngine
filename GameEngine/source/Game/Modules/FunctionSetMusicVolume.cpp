#include "Game/Modules/FunctionSetMusicVolume.h"

FunctionSetMusicVolume::FunctionSetMusicVolume(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::FLOAT));

	m_volume = params.at(0);
}

FunctionSetMusicVolume::~FunctionSetMusicVolume()
{

}

ScriptVar& FunctionSetMusicVolume::execute(ScriptInfoPack& pack)
{
	if (pack.audioModule)
	{
		pack.audioModule->setMusicVolume(m_volume.getValue(pack).getFloat());
	}

	return m_returnVal;
}
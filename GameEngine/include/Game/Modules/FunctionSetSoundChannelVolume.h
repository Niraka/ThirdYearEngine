/**
@author Nathan */

#ifndef FUNCTION_SET_SOUND_CHANNEL_VOLUME_H
#define FUNCTION_SET_SOUND_CHANNEL_VOLUME_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionSetSoundChannelVolume :
	public Function
{
	private:
		ScriptParam m_channelName;
		ScriptParam m_volume;

	protected:

	public:
		FunctionSetSoundChannelVolume(std::vector<ScriptParam>& params);
		~FunctionSetSoundChannelVolume();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
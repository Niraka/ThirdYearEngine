/**
@author Nathan */

#ifndef FUNCTION_CREATE_SOUND_CHANNEL_H
#define FUNCTION_CREATE_SOUND_CHANNEL_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionCreateSoundChannel :
	public Function
{
	private:
		ScriptParam m_channelName;

	protected:

	public:
		FunctionCreateSoundChannel(std::vector<ScriptParam>& params);
		~FunctionCreateSoundChannel();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
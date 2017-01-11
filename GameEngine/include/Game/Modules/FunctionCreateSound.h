/**
@author Nathan */

#ifndef FUNCTION_CREATE_SOUND_H
#define FUNCTION_CREATE_SOUND_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionCreateSound :
	public Function
{
	private:
		ScriptParam m_entityId;
		ScriptParam m_soundName;
		ScriptParam m_channelName;

	protected:

	public:
		FunctionCreateSound(std::vector<ScriptParam>& params);
		~FunctionCreateSound();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
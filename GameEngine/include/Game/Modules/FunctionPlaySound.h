/**
@author Nathan */

#ifndef FUNCTION_PLAY_SOUND_H
#define FUNCTION_PLAY_SOUND_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionPlaySound :
	public Function
{
	private:
		ScriptParam m_entityId;
		ScriptParam m_soundName;

	protected:

	public:
		FunctionPlaySound(std::vector<ScriptParam>& params);
		~FunctionPlaySound();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
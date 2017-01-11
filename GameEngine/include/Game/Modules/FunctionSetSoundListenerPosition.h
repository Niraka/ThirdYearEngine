/**
@author Nathan */

#ifndef FUNCTION_SET_SOUND_LISTENER_POSITION_H
#define FUNCTION_SET_SOUND_LISTENER_POSITION_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionSetSoundListenerPosition :
	public Function
{
	private:
		ScriptParam m_x;
		ScriptParam m_y;
		ScriptParam m_z;

	protected:

	public:
		FunctionSetSoundListenerPosition(std::vector<ScriptParam>& params);
		~FunctionSetSoundListenerPosition();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
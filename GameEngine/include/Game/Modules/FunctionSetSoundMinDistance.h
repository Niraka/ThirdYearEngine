/**
@author Nathan */

#ifndef FUNCTION_SET_SOUND_MIN_DISTANCE_H
#define FUNCTION_SET_SOUND_MIN_DISTANCE_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionSetSoundMinDistance :
	public Function
{
	private:
		ScriptParam m_entityId;
		ScriptParam m_soundName;
		ScriptParam m_minDistance;

	protected:

	public:
		FunctionSetSoundMinDistance(std::vector<ScriptParam>& params);
		~FunctionSetSoundMinDistance();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
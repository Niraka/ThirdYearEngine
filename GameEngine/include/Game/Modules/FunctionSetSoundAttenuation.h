/**
@author Nathan */

#ifndef FUNCTION_SET_SOUND_ATTENUTATION_H
#define FUNCTION_SET_SOUND_ATTENUTATION_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionSetSoundAttenuation :
	public Function
{
	private:
		ScriptParam m_entityId;
		ScriptParam m_soundName;
		ScriptParam m_attenuation;

	protected:

	public:
		FunctionSetSoundAttenuation(std::vector<ScriptParam>& params);
		~FunctionSetSoundAttenuation();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
/**
@author Nathan */

#ifndef FUNCTION_DELETE_SOUND_H
#define FUNCTION_DELETE_SOUND_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionDeleteSound :
	public Function
{
	private:
		ScriptParam m_entityId;
		ScriptParam m_soundName;

	protected:

	public:
		FunctionDeleteSound(std::vector<ScriptParam>& params);
		~FunctionDeleteSound();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
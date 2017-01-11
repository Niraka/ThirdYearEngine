/**
@author Nathan */

#ifndef FUNCTION_LOAD_SOUND_H
#define FUNCTION_LOAD_SOUND_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionLoadSound :
	public Function
{
	private:
		ScriptParam m_fileName;
		ScriptParam m_soundName;

	protected:

	public:
		FunctionLoadSound(std::vector<ScriptParam>& params);
		~FunctionLoadSound();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
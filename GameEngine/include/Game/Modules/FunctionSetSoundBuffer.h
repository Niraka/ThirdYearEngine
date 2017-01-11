/**
@author Nathan */

#ifndef FUNCTION_SET_SOUND_BUFFER_H
#define FUNCTION_SET_SOUND_BUFFER_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionSetSoundBuffer :
	public Function
{
	private:
		ScriptParam m_entityId;
		ScriptParam m_soundName;
		ScriptParam m_soundBufferName;

	protected:

	public:
		FunctionSetSoundBuffer(std::vector<ScriptParam>& params);
		~FunctionSetSoundBuffer();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
/**
@author Nathan */

#ifndef FUNCTION_PLAY_MUSIC_H
#define FUNCTION_PLAY_MUSIC_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionPlayMusic :
	public Function
{
	private:
		ScriptParam m_musicName;
		ScriptParam m_loopEnabled;
		ScriptParam m_transitionDuration;

	protected:

	public:
		FunctionPlayMusic(std::vector<ScriptParam>& params);
		~FunctionPlayMusic();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
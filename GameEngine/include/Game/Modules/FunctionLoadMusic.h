/**
@author Nathan */

#ifndef FUNCTION_LOAD_MUSIC_H
#define FUNCTION_LOAD_MUSIC_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionLoadMusic :
	public Function
{
	private:
		ScriptParam m_fileName;
		ScriptParam m_musicName;

	protected:

	public:
		FunctionLoadMusic(std::vector<ScriptParam>& params);
		~FunctionLoadMusic();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
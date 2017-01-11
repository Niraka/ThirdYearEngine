/**
@author Nathan */

#ifndef FUNCTION_SET_MUSIC_VOLUME_H
#define FUNCTION_SET_MUSIC_VOLUME_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionSetMusicVolume :
	public Function
{
	private:
		ScriptParam m_volume;

	protected:

	public:
		FunctionSetMusicVolume(std::vector<ScriptParam>& params);
		~FunctionSetMusicVolume();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
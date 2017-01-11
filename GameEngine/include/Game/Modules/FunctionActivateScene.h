/**
@author Nathan */

#ifndef FUNCTION_ACTIVATE_SCENE_H
#define FUNCTION_ACTIVATE_SCENE_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionActivateScene :
	public Function
{
	private:
		ScriptParam m_sceneName;

	protected:

	public:
		FunctionActivateScene(std::vector<ScriptParam>& params);
		~FunctionActivateScene();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
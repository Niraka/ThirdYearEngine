/**
@author Nathan */

#ifndef FUNCTION_DEACTIVATE_SCENE_H
#define FUNCTION_DEACTIVATE_SCENE_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionDeactivateScene :
	public Function
{
	private:
		ScriptParam m_sceneName;

	protected:

	public:
		FunctionDeactivateScene(std::vector<ScriptParam>& params);
		~FunctionDeactivateScene();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
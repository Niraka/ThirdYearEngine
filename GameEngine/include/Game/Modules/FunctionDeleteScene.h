/**
@author Nathan */

#ifndef FUNCTION_DELETE_SCENE_H
#define FUNCTION_DELETE_SCENE_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionDeleteScene :
	public Function
{
	private:
		ScriptParam m_sceneName;

	protected:

	public:
		FunctionDeleteScene(std::vector<ScriptParam>& params);
		~FunctionDeleteScene();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
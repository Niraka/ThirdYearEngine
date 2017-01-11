/**
@author Nathan */

#ifndef FUNCTION_CREATE_SCENE_H
#define FUNCTION_CREATE_SCENE_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionCreateScene :
	public Function
{
	private:
		ScriptParam m_sceneName;

	protected:

	public:
		FunctionCreateScene(std::vector<ScriptParam>& params);
		~FunctionCreateScene();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
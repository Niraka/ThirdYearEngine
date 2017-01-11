/**
@author Nathan */

#ifndef FUNCTION_SET_ENTITY_GROUP_SCENE_H
#define FUNCTION_SET_ENTITY_GROUP_SCENE_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionSetEntityGroup :
	public Function
{
	private:

	protected:

	public:
		FunctionSetEntityGroup();
		~FunctionSetEntityGroup();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
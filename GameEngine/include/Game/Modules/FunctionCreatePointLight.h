/**
@author Nathan */

#ifndef FUNCTION_CREATE_POINT_LIGHT_H
#define FUNCTION_CREATE_POINT_LIGHT_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionCreatePointLight :
	public Function
{
	private:
		ScriptParam m_sceneName;

	protected:

	public:
		FunctionCreatePointLight(std::vector<ScriptParam>& params);
		~FunctionCreatePointLight();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
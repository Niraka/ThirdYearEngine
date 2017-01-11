/**
@author Nathan */

#ifndef FUNCTION_ENABLE_POINT_LIGHT_H
#define FUNCTION_ENABLE_POINT_LIGHT_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionEnablePointLight :
	public Function
{
	private:
		ScriptParam m_lightId;
		ScriptParam m_sceneName;

	protected:

	public:
		FunctionEnablePointLight(std::vector<ScriptParam>& params);
		~FunctionEnablePointLight();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
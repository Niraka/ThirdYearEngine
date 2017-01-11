/**
@author Nathan */

#ifndef FUNCTION_DISABLE_POINT_LIGHT_H
#define FUNCTION_DISABLE_POINT_LIGHT_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionDisablePointLight :
	public Function
{
	private:
		ScriptParam m_lightId;
		ScriptParam m_sceneName;

	protected:

	public:
		FunctionDisablePointLight(std::vector<ScriptParam>& params);
		~FunctionDisablePointLight();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
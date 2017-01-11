/**
@author Nathan */

#ifndef FUNCTION_ENABLE_SPOT_LIGHT_H
#define FUNCTION_ENABLE_SPOT_LIGHT_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionEnableSpotLight :
	public Function
{
	private:
		ScriptParam m_lightId;
		ScriptParam m_sceneName;

	protected:

	public:
		FunctionEnableSpotLight(std::vector<ScriptParam>& params);
		~FunctionEnableSpotLight();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
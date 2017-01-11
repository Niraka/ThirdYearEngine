/**
@author Nathan */

#ifndef FUNCTION_DISABLE_SPOT_LIGHT_H
#define FUNCTION_DISABLE_SPOT_LIGHT_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionDisableSpotLight :
	public Function
{
	private:
		ScriptParam m_lightId;
		ScriptParam m_sceneName;

	protected:

	public:
		FunctionDisableSpotLight(std::vector<ScriptParam>& params);
		~FunctionDisableSpotLight();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
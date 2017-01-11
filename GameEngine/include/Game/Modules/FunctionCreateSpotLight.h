/**
@author Nathan */

#ifndef FUNCTION_CREATE_SPOT_LIGHT_H
#define FUNCTION_CREATE_SPOT_LIGHT_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionCreateSpotLight :
	public Function
{
	private:
		ScriptParam m_sceneName;

	protected:

	public:
		FunctionCreateSpotLight(std::vector<ScriptParam>& params);
		~FunctionCreateSpotLight();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
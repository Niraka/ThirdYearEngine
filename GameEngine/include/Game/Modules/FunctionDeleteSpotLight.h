/**
@author Nathan */

#ifndef FUNCTION_DELETE_SPOT_LIGHT_H
#define FUNCTION_DELETE_SPOT_LIGHT_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionDeleteSpotLight :
	public Function
{
	private:
		ScriptParam m_lightId;
		ScriptParam m_sceneName;

	protected:

	public:
		FunctionDeleteSpotLight(std::vector<ScriptParam>& params);
		~FunctionDeleteSpotLight();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
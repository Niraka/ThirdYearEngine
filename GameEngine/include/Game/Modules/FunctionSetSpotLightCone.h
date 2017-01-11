/**
@author Nathan */

#ifndef FUNCTION_SET_SPOT_LIGHT_CONE_H
#define FUNCTION_SET_SPOT_LIGHT_CONE_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionSetSpotLightCone :
	public Function
{
	private:
		ScriptParam m_lightId;
		ScriptParam m_coneAngle;
		ScriptParam m_sceneName;

	protected:

	public:
		FunctionSetSpotLightCone(std::vector<ScriptParam>& params);
		~FunctionSetSpotLightCone();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
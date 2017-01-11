/**
@author Nathan */

#ifndef FUNCTION_SET_SPOT_LIGHT_TARGET_H
#define FUNCTION_SET_SPOT_LIGHT_TARGET_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionSetSpotLightTarget :
	public Function
{
	private:
		ScriptParam m_lightId;
		ScriptParam m_x;
		ScriptParam m_y;
		ScriptParam m_z;
		ScriptParam m_sceneName;

	protected:

	public:
		FunctionSetSpotLightTarget(std::vector<ScriptParam>& params);
		~FunctionSetSpotLightTarget();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
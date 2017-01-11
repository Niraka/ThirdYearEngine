/**
@author Nathan */

#ifndef FUNCTION_SET_POINT_LIGHT_POSITION_H
#define FUNCTION_SET_POINT_LIGHT_POSITION_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionSetPointLightPosition :
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
		FunctionSetPointLightPosition(std::vector<ScriptParam>& params);
		~FunctionSetPointLightPosition();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
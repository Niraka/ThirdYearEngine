/**
@author Nathan */

#ifndef FUNCTION_SET_POINT_LIGHT_COLOUR_H
#define FUNCTION_SET_POINT_LIGHT_COLOUR_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionSetPointLightColour :
	public Function
{
	private:
		ScriptParam m_lightId;
		ScriptParam m_r;
		ScriptParam m_g;
		ScriptParam m_b;
		ScriptParam m_sceneName;

	protected:

	public:
		FunctionSetPointLightColour(std::vector<ScriptParam>& params);
		~FunctionSetPointLightColour();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
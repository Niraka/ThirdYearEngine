/**
@author Nathan */

#ifndef FUNCTION_SET_AMBIENT_LIGHT_COLOUR_H
#define FUNCTION_SET_AMBIENT_LIGHT_COLOUR_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionSetAmbientLightColour :
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
		FunctionSetAmbientLightColour(std::vector<ScriptParam>& params);
		~FunctionSetAmbientLightColour();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
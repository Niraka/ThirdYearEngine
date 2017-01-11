/**
@author Nathan */

#ifndef FUNCTION_DISABLE_AMBIENT_LIGHT_H
#define FUNCTION_DISABLE_AMBIENT_LIGHT_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionDisableAmbientLight :
	public Function
{
	private:
		ScriptParam m_lightId;
		ScriptParam m_sceneName;

	protected:

	public:
		FunctionDisableAmbientLight(std::vector<ScriptParam>& params);
		~FunctionDisableAmbientLight();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
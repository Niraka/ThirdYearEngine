/**
@author Nathan */

#ifndef FUNCTION_ENABLE_AMBIENT_LIGHT_H
#define FUNCTION_ENABLE_AMBIENT_LIGHT_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionEnableAmbientLight :
	public Function
{
	private:
		ScriptParam m_lightId;
		ScriptParam m_sceneName;

	protected:

	public:
		FunctionEnableAmbientLight(std::vector<ScriptParam>& params);
		~FunctionEnableAmbientLight();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
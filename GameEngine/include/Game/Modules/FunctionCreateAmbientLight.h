/**
@author Nathan */

#ifndef FUNCTION_CREATE_AMBIENT_LIGHT_H
#define FUNCTION_CREATE_AMBIENT_LIGHT_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionCreateAmbientLight :
	public Function
{
	private:
		ScriptParam m_sceneName;

	protected:

	public:
		FunctionCreateAmbientLight(std::vector<ScriptParam>& params);
		~FunctionCreateAmbientLight();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
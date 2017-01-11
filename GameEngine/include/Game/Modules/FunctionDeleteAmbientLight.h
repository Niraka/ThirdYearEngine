/**
@author Nathan */

#ifndef FUNCTION_DELETE_AMBIENT_LIGHT_H
#define FUNCTION_DELETE_AMBIENT_LIGHT_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionDeleteAmbientLight :
	public Function
{
	private:
		ScriptParam m_lightId;
		ScriptParam m_sceneName;

	protected:

	public:
		FunctionDeleteAmbientLight(std::vector<ScriptParam>& params);
		~FunctionDeleteAmbientLight();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
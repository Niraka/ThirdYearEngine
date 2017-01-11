/**
@author Nathan */

#ifndef FUNCTION_DELETE_POINT_LIGHT_H
#define FUNCTION_DELETE_POINT_LIGHT_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionDeletePointLight :
	public Function
{
	private:
		ScriptParam m_lightId;
		ScriptParam m_sceneName;

	protected:

	public:
		FunctionDeletePointLight(std::vector<ScriptParam>& params);
		~FunctionDeletePointLight();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
/**
@author Nathan */

#ifndef FUNCTION_CREATE_CAMERA_H
#define FUNCTION_CREATE_CAMERA_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionCreateCamera :
	public Function
{
	private:
		ScriptParam m_sceneName;

	protected:

	public:
		FunctionCreateCamera(std::vector<ScriptParam>& params);
		~FunctionCreateCamera();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
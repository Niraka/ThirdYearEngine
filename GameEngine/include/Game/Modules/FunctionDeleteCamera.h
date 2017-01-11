/**
@author Nathan */

#ifndef FUNCTION_DELETE_CAMERA_H
#define FUNCTION_DELETE_CAMERA_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionDeleteCamera :
	public Function
{
	private:
		ScriptParam m_lightId;
		ScriptParam m_sceneName;

	protected:

	public:
		FunctionDeleteCamera(std::vector<ScriptParam>& params);
		~FunctionDeleteCamera();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
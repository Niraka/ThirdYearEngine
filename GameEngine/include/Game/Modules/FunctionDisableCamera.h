/**
@author Nathan */

#ifndef FUNCTION_DISABLE_CAMERA_H
#define FUNCTION_DISABLE_CAMERA_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionDisableCamera :
	public Function
{
	private:
		ScriptParam m_cameraId;
		ScriptParam m_sceneName;

	protected:

	public:
		FunctionDisableCamera(std::vector<ScriptParam>& params);
		~FunctionDisableCamera();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
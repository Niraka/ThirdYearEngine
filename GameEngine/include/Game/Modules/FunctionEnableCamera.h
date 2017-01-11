/**
@author Nathan */

#ifndef FUNCTION_ENABLE_CAMERA_H
#define FUNCTION_ENABLE_CAMERA_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionEnableCamera :
	public Function
{
	private:
		ScriptParam m_cameraId;
		ScriptParam m_sceneName;

	protected:

	public:
		FunctionEnableCamera(std::vector<ScriptParam>& params);
		~FunctionEnableCamera();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
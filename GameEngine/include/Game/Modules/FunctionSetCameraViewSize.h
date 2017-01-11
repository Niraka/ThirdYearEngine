/**
@author Nathan */

#ifndef FUNCTION_SET_CAMERA_VIEW_SIZE_H
#define FUNCTION_SET_CAMERA_VIEW_SIZE_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionSetCameraViewSize :
	public Function
{
	private:
		ScriptParam m_cameraId;
		ScriptParam m_width;
		ScriptParam m_height;
		ScriptParam m_sceneName;

	protected:

	public:
		FunctionSetCameraViewSize(std::vector<ScriptParam>& params);
		~FunctionSetCameraViewSize();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
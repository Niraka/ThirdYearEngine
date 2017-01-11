/**
@author Nathan */

#ifndef FUNCTION_SET_CAMERA_ORIENTATION_H
#define FUNCTION_SET_CAMERA_ORIENTATION_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionSetCameraOrientation :
	public Function
{
	private:
		ScriptParam m_cameraId;
		ScriptParam m_x;
		ScriptParam m_y;
		ScriptParam m_z;
		ScriptParam m_sceneName;

	protected:

	public:
		FunctionSetCameraOrientation(std::vector<ScriptParam>& params);
		~FunctionSetCameraOrientation();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
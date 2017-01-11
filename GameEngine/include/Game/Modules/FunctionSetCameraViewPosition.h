/**
@author Nathan */

#ifndef FUNCTION_SET_CAMERA_VIEW_POSITION_H
#define FUNCTION_SET_CAMERA_VIEW_POSITION_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionSetCameraViewPosition :
	public Function
{
	private:
		ScriptParam m_cameraId;
		ScriptParam m_x;
		ScriptParam m_y;
		ScriptParam m_sceneName;

	protected:

	public:
		FunctionSetCameraViewPosition(std::vector<ScriptParam>& params);
		~FunctionSetCameraViewPosition();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
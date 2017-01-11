/**
@author Nathan */

#ifndef FUNCTION_SET_CAMERA_POSITION_H
#define FUNCTION_SET_CAMERA_POSITION_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionSetCameraPosition :
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
		FunctionSetCameraPosition(std::vector<ScriptParam>& params);
		~FunctionSetCameraPosition();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
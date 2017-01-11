/**
@author Nathan */

#ifndef FUNCTION_BIND_CAMERA_TO_ENTITY_H
#define FUNCTION_BIND_CAMERA_TO_ENTITY_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionBindCameraToEntity :
	public Function
{
	private:
		ScriptParam m_cameraId;
		ScriptParam m_sceneName;
		ScriptParam m_entityId;

	protected:

	public:
		FunctionBindCameraToEntity(std::vector<ScriptParam>& params);
		~FunctionBindCameraToEntity();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
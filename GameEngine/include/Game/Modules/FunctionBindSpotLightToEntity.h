/**
@author Nathan */

#ifndef FUNCTION_BIND_SPOT_LIGHT_TO_ENTITY_H
#define FUNCTION_BIND_SPOT_LIGHT_TO_ENTITY_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionBindSpotLightToEntity :
	public Function
{
	private:
		ScriptParam m_spotLightId;
		ScriptParam m_sceneName;
		ScriptParam m_entityId;

	protected:

	public:
		FunctionBindSpotLightToEntity(std::vector<ScriptParam>& params);
		~FunctionBindSpotLightToEntity();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
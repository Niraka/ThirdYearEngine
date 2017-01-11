/**
A scripting function that binds an movement action to a control set.
@author Nathan */

#ifndef FUNCTION_BIND_ENTITY_MOVEMENT_MAPPING_H
#define FUNCTION_BIND_ENTITY_MOVEMENT_MAPPING_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionBindEntityMovementMapping :
	public Function
{
	private:
		ScriptParam m_controlSetId;
		ScriptParam m_entityId;
		ScriptParam m_sceneName;

	protected:

	public:
		/**
		Constructs a new FunctionBindEntityMovementMapping with the given parameters.
		@param params The function parameters */
		FunctionBindEntityMovementMapping(std::vector<ScriptParam>& params);

		/**
		Destructs a FunctionBindEntityMovementMapping. */
		~FunctionBindEntityMovementMapping();

		/**
		Executes the function.
		@param pack The ScriptingModule information pack
		@return A reference to the return value of the function */
		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
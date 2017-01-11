/**
A scripting function that deactivates a control set on the target scene.

@author Nathan */

#ifndef FUNCTION_DEACTIVATE_CONTROL_SET_H
#define FUNCTION_DEACTIVATE_CONTROL_SET_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionDeactivateControlSet :
	public Function
{
	private:
		ScriptParam m_controlSetId;
		ScriptParam m_sceneName;

	protected:

	public:
		/**
		Constructs a new FunctionDeactivateControlSet with the given parameters.
		@param params The function parameters */
		FunctionDeactivateControlSet(std::vector<ScriptParam>& params);

		/**
		Destructs a FunctionDeactivateControlSet. */
		~FunctionDeactivateControlSet();

		/**
		Executes the function.
		@param pack The ScriptingModule information pack
		@return A reference to the return value of the function */
		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
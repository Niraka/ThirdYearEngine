/**
A scripting function that deletes a control set on the target scene.

@author Nathan */

#ifndef FUNCTION_DELETE_CONTROL_SET_H
#define FUNCTION_DELETE_CONTROL_SET_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionDeleteControlSet :
	public Function
{
	private:
		ScriptParam m_controlSetId;
		ScriptParam m_sceneName;

	protected:

	public:
		/**
		Constructs a new FunctionDeleteControlSet with the given parameters.
		@param params The function parameters */
		FunctionDeleteControlSet(std::vector<ScriptParam>& params);

		/**
		Destructs a FunctionDeleteControlSet. */
		~FunctionDeleteControlSet();

		/**
		Executes the function.
		@param pack The ScriptingModule information pack
		@return A reference to the return value of the function */
		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
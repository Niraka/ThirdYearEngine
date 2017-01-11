/**
A scripting function that activates a control set on the target scene.

@author Nathan */

#ifndef FUNCTION_ACTIVATE_CONTROL_SET_H
#define FUNCTION_ACTIVATE_CONTROL_SET_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionActivateControlSet :
	public Function
{
	private:
		ScriptParam m_controlSetId;
		ScriptParam m_sceneName;

	protected:

	public:
		/**
		Constructs a new FunctionActivateControlSet with the given parameters. 
		@param params The function parameters */
		FunctionActivateControlSet(std::vector<ScriptParam>& params);

		/**
		Destructs a FunctionActivateControlSet. */
		~FunctionActivateControlSet();

		/**
		Executes the function. 
		@param pack The ScriptingModule information pack 
		@return A reference to the return value of the function */
		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
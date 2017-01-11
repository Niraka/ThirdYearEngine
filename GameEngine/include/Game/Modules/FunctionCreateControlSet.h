/**
A scripting function that creates a control set on the target scene.

@author Nathan */

#ifndef FUNCTION_CREATE_CONTROL_SET_H
#define FUNCTION_CREATE_CONTROL_SET_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionCreateControlSet :
	public Function
{
	private:
		ScriptParam m_sceneName;

	protected:

	public:
		/**
		Constructs a new FunctionCreateControlSet with the given parameters.
		@param params The function parameters */
		FunctionCreateControlSet(std::vector<ScriptParam>& params);

		/**
		Destructs a FunctionCreateControlSet. */
		~FunctionCreateControlSet();

		/**
		Executes the function.
		@param pack The ScriptingModule information pack
		@return A reference to the return value of the function */
		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
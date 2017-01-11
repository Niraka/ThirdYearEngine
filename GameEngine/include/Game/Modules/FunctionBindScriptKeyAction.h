/**
A scripting function that binds a scripting action and key code to a given control set.

@author Nathan */

#ifndef FUNCTION_BIND_SCRIPT_KEY_ACTION_H
#define FUNCTION_BIND_SCRIPT_KEY_ACTION_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"
#include "Game/Modules/Script.h"

class FunctionBindScriptKeyAction :
	public Function
{
	private:
		ScriptParam m_controlSetId;
		ScriptParam m_scriptName;
		ScriptParam m_actionName;
		ScriptParam m_keyCode;
		ScriptParam m_actionType;
		ScriptParam m_sceneName;

	protected:

	public:
		/**
		Constructs a new FunctionBindScriptKeyAction with the given parameters.
		@param params The function parameters */
		FunctionBindScriptKeyAction(std::vector<ScriptParam>& params);

		/**
		Destructs a FunctionBindScriptKeyAction. */
		~FunctionBindScriptKeyAction();

		/**
		Executes the function.
		@param pack The ScriptingModule information pack
		@return A reference to the return value of the function */
		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
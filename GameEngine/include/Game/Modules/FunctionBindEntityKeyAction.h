/**
A scripting function that binds an entity action and key code to a given control set.

@author Nathan */

#ifndef FUNCTION_BIND_ENTITY_KEY_ACTION_H
#define FUNCTION_BIND_ENTITY_KEY_ACTION_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionBindEntityKeyAction :
	public Function
{
	private:
		ScriptParam m_controlSetId;
		ScriptParam m_entityId;
		ScriptParam m_actionName;
		ScriptParam m_keyCode;
		ScriptParam m_actionType;
		ScriptParam m_sceneName;

	protected:

	public:
		/**
		Constructs a new FunctionBindEntityKeyAction with the given parameters.
		@param params The function parameters */
		FunctionBindEntityKeyAction(std::vector<ScriptParam>& params);

		/**
		Destructs a FunctionBindEntityKeyAction. */
		~FunctionBindEntityKeyAction();

		/**
		Executes the function.
		@param pack The ScriptingModule information pack
		@return A reference to the return value of the function */
		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
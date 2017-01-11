#ifndef FUNCTION_SET_CURSOR_MODE_H
#define FUNCTION_SET_CURSOR_MODE_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionSetCursorMode :
	public Function
{
	private:
		ScriptParam m_cursorMode;
		ScriptParam m_sceneName;

	protected:

	public:
		/**
		Constructs a new FunctionSetCursorMode with the given parameters.
		@param params The function parameters */
		FunctionSetCursorMode(std::vector<ScriptParam>& params);

		/**
		Destructs a FunctionSetCursorMode. */
		~FunctionSetCursorMode();

		/**
		Executes the function.
		@param pack The ScriptingModule information pack
		@return A reference to the return value of the function */
		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
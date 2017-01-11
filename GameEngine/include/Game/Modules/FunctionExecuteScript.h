/**
@author Nathan */

#ifndef FUNCTION_EXECUTE_SCRIPT_H
#define FUNCTION_EXECUTE_SCRIPT_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionExecuteScript :
	public Function
{
	private:
		ScriptParam m_scriptName;

	protected:

	public:
		FunctionExecuteScript(std::vector<ScriptParam>& params);
		~FunctionExecuteScript();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
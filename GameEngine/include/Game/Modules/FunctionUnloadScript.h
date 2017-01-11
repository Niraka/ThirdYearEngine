/**
@author Nathan */

#ifndef FUNCTION_UNLOAD_SCRIPT_H
#define FUNCTION_UNLOAD_SCRIPT_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionUnloadScript :
	public Function
{
	private:
		ScriptParam m_scriptName;

	protected:

	public:
		FunctionUnloadScript(std::vector<ScriptParam>& params);
		~FunctionUnloadScript();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
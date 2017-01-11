/**
@author Nathan */

#ifndef FUNCTION_LOAD_SCRIPT_H
#define FUNCTION_LOAD_SCRIPT_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionLoadScript :
	public Function
{
	private:
		ScriptParam m_fileName;
		ScriptParam m_scriptName;

	protected:

	public:
		FunctionLoadScript(std::vector<ScriptParam>& params);
		~FunctionLoadScript();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
/**
Assigns a value to a script variable.

@author Nathan */

#ifndef FUNCTION_ASSIGN_H
#define FUNCTION_ASSIGN_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionAssign :
	public Function
{
	private:
		ScriptParam m_variable;
		ScriptParam m_value;

	protected:

	public:
		FunctionAssign(std::vector<ScriptParam>& params);
		~FunctionAssign();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
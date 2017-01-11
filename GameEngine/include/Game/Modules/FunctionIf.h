/**
@author Nathan */

#ifndef FUNCTION_IF_H
#define FUNCTION_IF_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionIf :
	public Function
{
	private:
		ScriptParam m_condition;
		ScriptParam m_script1;
		ScriptParam m_script2;

	protected:

	public:
		FunctionIf(std::vector<ScriptParam>& params);
		~FunctionIf();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
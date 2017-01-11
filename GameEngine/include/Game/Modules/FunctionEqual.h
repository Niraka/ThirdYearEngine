/**
@author Nathan */

#ifndef FUNCTION_EQUAL_H
#define FUNCTION_EQUAL_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionEqual :
	public Function
{
	private:
		ScriptParam m_first;
		ScriptParam m_second;

	protected:

	public:
		FunctionEqual(std::vector<ScriptParam>& params);
		~FunctionEqual();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
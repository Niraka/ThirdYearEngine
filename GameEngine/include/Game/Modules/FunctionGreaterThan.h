/**
@author Nathan */

#ifndef FUNCTION_GREATER_THAN_H
#define FUNCTION_GREATER_THAN_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionGreaterThan :
	public Function
{
	private:
		ScriptParam m_first;
		ScriptParam m_second;

	protected:

	public:
		FunctionGreaterThan(std::vector<ScriptParam>& params);
		~FunctionGreaterThan();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
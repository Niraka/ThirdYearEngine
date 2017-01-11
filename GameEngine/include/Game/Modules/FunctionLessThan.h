/**
@author Nathan */

#ifndef FUNCTION_LESS_THAN_H
#define FUNCTION_LESS_THAN_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionLessThan :
	public Function
{
	private:
		ScriptParam m_first;
		ScriptParam m_second;

	protected:

	public:
		FunctionLessThan(std::vector<ScriptParam>& params);
		~FunctionLessThan();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
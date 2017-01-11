/**
@author Nathan */

#ifndef FUNCTION_GET_RANDOM_FLOAT_H
#define FUNCTION_GET_RANDOM_FLOAT_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionGetRandomFloat :
	public Function
{
	private:
		ScriptParam m_lower;
		ScriptParam m_upper;

	protected:

	public:
		FunctionGetRandomFloat(std::vector<ScriptParam>& params);
		~FunctionGetRandomFloat();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
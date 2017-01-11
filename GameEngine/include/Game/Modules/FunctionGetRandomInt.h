/**
@author Nathan */

#ifndef FUNCTION_GET_RANDOM_INT_H
#define FUNCTION_GET_RANDOM_INT_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionGetRandomInt :
	public Function
{
	private:
		ScriptParam m_lower;
		ScriptParam m_upper;

	protected:

	public:
		FunctionGetRandomInt(std::vector<ScriptParam>& params);
		~FunctionGetRandomInt();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
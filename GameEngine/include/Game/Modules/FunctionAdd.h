/**
@author Nathan */

#ifndef FUNCTION_ADD_H
#define FUNCTION_ADD_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionAdd :
	public Function
{
	private:
		ScriptParam m_first;
		ScriptParam m_second;

	protected:

	public:
		FunctionAdd(std::vector<ScriptParam>& params);
		~FunctionAdd();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
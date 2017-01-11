/**
@author Nathan */

#ifndef FUNCTION_LOG_H
#define FUNCTION_LOG_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionLog :
	public Function
{
	private:
		ScriptParam m_value;

	protected:

	public:
		FunctionLog(std::vector<ScriptParam>& params);
		~FunctionLog();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
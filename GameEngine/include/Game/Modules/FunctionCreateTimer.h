/**
@author Nathan */

#ifndef FUNCTION_CREATE_TIMER_H
#define FUNCTION_CREATE_TIMER_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionCreateTimer :
	public Function
{
	private:
		bool m_bScriptRunEnabled;
		ScriptParam m_timerName;
		ScriptParam m_duration;
		ScriptParam m_scriptToRun;

	protected:

	public:
		FunctionCreateTimer(std::vector<ScriptParam>& params);
		~FunctionCreateTimer();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
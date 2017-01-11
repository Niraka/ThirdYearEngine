/**
@author Nathan */

#ifndef FUNCTION_SET_ENTITY_VISIBLE_H
#define FUNCTION_SET_ENTITY_VISIBLE_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionSetEntityVisible :
	public Function
{
	private:
		ScriptParam m_entityId;
		ScriptParam m_visible;

	protected:

	public:
		FunctionSetEntityVisible(std::vector<ScriptParam>& params);
		~FunctionSetEntityVisible();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
/**
@author Nathan */

#ifndef FUNCTION_SET_ENTITY_ORIENTATION_H
#define FUNCTION_SET_ENTITY_ORIENTATION_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionSetEntityOrientation :
	public Function
{
	private:
		ScriptParam m_entityId;
		ScriptParam m_x;
		ScriptParam m_y;
		ScriptParam m_z;

	protected:

	public:
		FunctionSetEntityOrientation(std::vector<ScriptParam>& params);
		~FunctionSetEntityOrientation();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
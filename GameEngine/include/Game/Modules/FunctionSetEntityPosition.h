/**
@author Nathan */

#ifndef FUNCTION_SET_ENTITY_POSITION_H
#define FUNCTION_SET_ENTITY_POSITION_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionSetEntityPosition :
	public Function
{
	private:
		ScriptParam m_entityId;
		ScriptParam m_x;
		ScriptParam m_y;
		ScriptParam m_z;

	protected:

	public:
		FunctionSetEntityPosition(std::vector<ScriptParam>& params);
		~FunctionSetEntityPosition();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
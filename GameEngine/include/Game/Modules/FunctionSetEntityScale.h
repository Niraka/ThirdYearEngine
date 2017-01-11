/**
@author Nathan */

#ifndef FUNCTION_SET_ENTITY_SCALE_H
#define FUNCTION_SET_ENTITY_SCALE_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionSetEntityScale :
	public Function
{
	private:
		ScriptParam m_entityId;
		ScriptParam m_x;
		ScriptParam m_y;
		ScriptParam m_z;

	protected:

	public:
		FunctionSetEntityScale(std::vector<ScriptParam>& params);
		~FunctionSetEntityScale();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
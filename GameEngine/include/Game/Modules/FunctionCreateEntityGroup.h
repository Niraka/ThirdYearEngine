/**
@author Nathan */

#ifndef FUNCTION_CREATE_ENTITY_GROUP_H
#define FUNCTION_CREATE_ENTITY_GROUP_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionCreateEntityGroup :
	public Function
{
	private:
		ScriptParam m_groupName;

	protected:

	public:
		FunctionCreateEntityGroup(std::vector<ScriptParam>& params);
		~FunctionCreateEntityGroup();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
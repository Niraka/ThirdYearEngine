/**
@author Nathan */

#ifndef FUNCTION_CREATE_ENTITY_H
#define FUNCTION_CREATE_ENTITY_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionCreateEntity :
	public Function
{
	private:
		ScriptParam m_specName;
		ScriptParam m_groupName;

	protected:

	public:
		FunctionCreateEntity(std::vector<ScriptParam>& params);
		~FunctionCreateEntity();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
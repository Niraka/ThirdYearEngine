/**
@author Nathan */

#ifndef FUNCTION_DELETE_ENTITY_H
#define FUNCTION_DELETE_ENTITY_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionDeleteEntity :
	public Function
{
	private:
		ScriptParam m_entityId;

	protected:

	public:
		FunctionDeleteEntity(std::vector<ScriptParam>& params);
		~FunctionDeleteEntity();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
/**
@author Nathan */

#ifndef FUNCTION_SET_ENTITY_GROUP_RENDERABLE_H
#define FUNCTION_SET_ENTITY_GROUP_RENDERABLE_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionSetEntityGroupRenderable :
	public Function
{
	private:
		ScriptParam m_groupName;
		ScriptParam m_renderable;

	protected:

	public:
		FunctionSetEntityGroupRenderable(std::vector<ScriptParam>& params);
		~FunctionSetEntityGroupRenderable();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
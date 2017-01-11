/**
@author Nathan */

#ifndef FUNCTION_LOAD_ENTITY_SPECS_H
#define FUNCTION_LOAD_ENTITY_SPECS_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionLoadEntitySpecs :
	public Function
{
	private:
		ScriptParam m_fileName;

	protected:

	public:
		FunctionLoadEntitySpecs(std::vector<ScriptParam>& params);
		~FunctionLoadEntitySpecs();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
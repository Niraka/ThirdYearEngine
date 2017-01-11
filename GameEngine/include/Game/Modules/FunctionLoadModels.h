/**
@author Nathan */

#ifndef FUNCTION_LOAD_MODELS_H
#define FUNCTION_LOAD_MODELS_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionLoadModels :
	public Function
{
	private:
		ScriptParam m_fileName;

	protected:

	public:
		FunctionLoadModels(std::vector<ScriptParam>& params);
		~FunctionLoadModels();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
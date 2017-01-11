/**
A function to load an interface into the GUIModule
@author Wade */

#ifndef FUNCTION_LOAD_INTERFACE_H
#define FUNCTION_LOAD_INTERFACE_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionLoadInterface :
	public Function
{
	private:
		ScriptParam m_fileName;		//!< The name of the interface, NOTE that the ".txt" is appended in the scirpt, so you only have to give the name of the file

	protected:

	public:
		FunctionLoadInterface(std::vector<ScriptParam>& params);
		~FunctionLoadInterface();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
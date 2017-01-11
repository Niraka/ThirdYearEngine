/**
A function to display a loaded interface from the GUIModule
@author Nathan + Wade */

#ifndef FUNCTION_DISPLAY_INTERFACE_H
#define FUNCTION_DISPLAY_INTERFACE_H

#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptParam.h"

class FunctionDisplayInterface :
	public Function
{
	private:
		ScriptParam m_interfaceName;		//!< The name of the interface to display

	protected:

	public:
		FunctionDisplayInterface(std::vector<ScriptParam>& params);
		~FunctionDisplayInterface();

		ScriptVar& execute(ScriptInfoPack& pack);
};

#endif
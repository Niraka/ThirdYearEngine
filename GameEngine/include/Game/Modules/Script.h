/**
A Script is a series of Function objects that can be executed in order to perform some action
within the engine. For example, a Script could contain a two functions, create entity and position
entity, and could be called "spawn_entity".

Scripts are non-copyable. 

@author Nathan */

#ifndef SCRIPT_H
#define SCRIPT_H

#include "Game/Modules/ScriptInfoPack.h"
#include "Game/Modules/Function.h"
#include "Game/Modules/ScriptVar.h"

#include <vector>
#include <string>
#include <map>

class Script :
	public KeyAction
{
	public:
		enum SymbolType
		{
			UNKNOWN,
			FUNCTION,
			VARIABLE_DEFINITION,
			VARIABLE,
			HARD_VALUE
		};

	private:
		std::string m_sName;
		ScriptActionTerminal* m_actionTerminal;
		const std::string m_sExecuteScriptAction;
		std::vector<Function*> m_functions;

	protected:
		std::map<std::string, ScriptVar>* m_variables;

	public:
		/**
		Constructs a Script. 
		@param sName The name to assign the Script
		@param variables A pointer to the global variable store
		@param actionTerminal A pointer to the script action terminal */
		Script(std::string sName, std::map<std::string, ScriptVar>* variables, ScriptActionTerminal* actionTerminal);

		/**
		Destructs the Script. Function objects are destroyed. */
		~Script();

		/**
		Appends a Function to the Script. The Function should be created on the heap. 
		@param func A pointer to the Function to add*/
		void appendFunction(Function* func);

		/**
		Executes the scripts Functions.
		@param pack The ScriptInfoPack containing references to the modules */
		void execute(ScriptInfoPack& pack);

		/**
		This function is called when an action is triggered by a bound key press/release.
		@param sActionName The name of the action that was triggered */
		void onAction(const std::string& sActionName);
};

#endif
/**
The ScriptActionTerminal is an interface class that defines the necessary functions for a class to be able to
respond to specific Script actions. 

@author Nathan */

#ifndef SCRIPT_ACTION_TERMINAL_H
#define SCRIPT_ACTION_TERMINAL_H

#include <string>

class ScriptActionTerminal
{
	private:

	protected:

	public:
		/**
		Loads a Script from the given file and binds it to the given name. The name must be unique amongst all
		other Scripts currently in memory. Note that the file name should not include the parent directory as
		this is automatically prepended. For example, ".\\data\\scripts\\myScript.txt" should begiven as
		"myScript.txt".
		@param sScriptName The name to bind the Script to
		@param sFileName The name of the file to load from
		@return True if the Script was successfully loaded, false otherwise */
		virtual bool loadScript(const std::string& sScriptName, const std::string& sFileName) = 0;

		/**
		Unloads a Script with the given name. 
		@param sScriptName The name of the Script to unload */
		virtual void unloadScript(const std::string& sScriptName) = 0;

		/**
		Executes a Script with the given name.
		@param sScriptName The name of the Script to execute */
		virtual void executeScript(const std::string& sScriptName) = 0;

		/**
		Gets a Script with the given name. The value must be transferred as a void pointer to avoid
		circular inclusion. 
		@param sScriptName The name of the Script to get */
		virtual void* getScript(const std::string& sScriptName) = 0;
};

#endif
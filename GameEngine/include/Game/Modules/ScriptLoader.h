/**
A ScriptLoader handles the loading of script text files in to Script objects. 

@author Nathan */

#ifndef SCRIPT_LOADER_H
#define SCRIPT_LOADER_H

#include "Game/Modules/Script.h"
#include "Game/Modules/ScriptParam.h"
#include "Game/Modules/FunctionRegister.h"
#include "System/Utility/DirectoryListing.h"

#include <map>
#include <set>

class ScriptLoader
{
	private:
		char m_validChars[12];
		FunctionRegister* m_functionRegister;
		std::set<std::string>* m_variableDefintionSymbols;		    // A listing of the valid variable definition symbols
		std::map<std::string, ScriptVar>* m_variables;               // A listing of the valid variables
		unsigned int m_uiLineNum;                                   // The current line number
		std::string m_sScriptsDirectory;                            // The scripts directory, as extracted from the DirectoryListing
		std::vector<std::string> m_info;                            // A vector of info detailing the script loading process
		StringUtils m_stringUtils;		                            // A string utility object

		std::vector<std::string> getParamStrings(std::string& sLineParams);
		
		Script::SymbolType getSymbolType(std::string& sLine);
		
		/**
		Returns the number of parameters detected within the given line. 
		@param sLine The line to analyse
		@return The number of parameters */
		unsigned int getParamCount(std::string& sLine);

		/**
		Parses a given line and attempts to append to the given script a series of Function objects
		that match the functions defined in the line.
		@param sLine The line to parse
		@param script A reference to the Script to assign the functions to 
		@return A pointer to the Function baseclass */
		Function* parseFunction(std::string& sLine, Script& script);

		/**
		Parses and adds to the given script a variable definition depending on the given line. If the
		line contained no valid definition, this function does nothing.
		@param sLine The line to parse
		@param script A reference to the Script to assign the variable to */
		void parseVariableDefinition(std::string& sLine, Script& script);

		/**
		Parses and returns a ScriptVar as a magic number value. 
		@param sLine The line to parse
		@return A ScriptVar representing the parsed value */
		ScriptVar parseHardValue(std::string& sLine);

		/**
		Returns true if the given line is a numeric string.
		@param sLine The line to parse
		@return True if the line was numeric, false otherwise */
		bool isNumeric(std::string& sLine);

	protected:

	public:
		/**
		Constructs a ScriptLoader. */
		ScriptLoader(FunctionRegister* funcRegister, 
			std::map<std::string, ScriptVar>* variables,
			std::set<std::string>* variableDefintionSymbols);

		/**
		Destructs the ScriptLoader. */
		~ScriptLoader();

		/**
		Attempts to load a Script from the given file. Note that the file name should not include the parent
		directory as this is automatically prepended. For example, ".\\data\\scripts\\myScript.txt" should be
		given as "myScript.txt". 
		@param sFileName The name of the file to load the script from
		@param script A reference to a Script object to populate with the loaded script information
		@return True if the Script was successfully loaded, false otherwise */
		bool loadScript(const std::string& sFileName, Script& script);

		/**
		Retrieves a vector of information relating to the most recent load Script call.
		@return A const reference to an information vector */
		const std::vector<std::string>& getInfo() const;
};

#endif
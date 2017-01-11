#include "Game/Modules/ScriptLoader.h"

ScriptLoader::ScriptLoader(FunctionRegister* funcRegister, std::map<std::string, ScriptVar>* variables, 
	std::set<std::string>* variableDefintionSymbols)
{
	m_functionRegister = funcRegister;
	m_variables = variables;
	m_variableDefintionSymbols = variableDefintionSymbols;

	 m_validChars[0] = '0';
	 m_validChars[1] = '1';
	 m_validChars[2] = '2';
	 m_validChars[3] = '3';
	 m_validChars[4] = '4';
	 m_validChars[5] = '5';
	 m_validChars[6] = '6';
	 m_validChars[7] = '7';
	 m_validChars[8] = '8';
	 m_validChars[9] = '9';
	 m_validChars[10] = '-';
	 m_validChars[11] = '.';

	m_sScriptsDirectory = DirectoryListing::getInstance()->getDirectory("scripts");
}

ScriptLoader::~ScriptLoader()
{
}

bool ScriptLoader::loadScript(const std::string& sFileName, Script& script)
{
	m_info.clear();
	m_uiLineNum = 0;

	if (!m_functionRegister)
	{
		return false;
	}

	// Attempt to open the script file
	std::string sFullPath = m_sScriptsDirectory + sFileName;
	std::ifstream inStream(sFullPath);
	if (inStream.is_open())
	{
		// Create temporary storage for the parsed values
		std::string sLine;

		// Begin parsing each line
		while (getline(inStream, sLine))
		{
			// Discard empty lines and comments
			++m_uiLineNum;
			if (sLine.empty() || sLine.at(0) == '#')
			{
				continue;
			}

			Script::SymbolType symbolType = getSymbolType(sLine);
			if (symbolType == Script::SymbolType::UNKNOWN)
			{
				m_info.push_back("Line " + std::to_string(m_uiLineNum) + ": Unknown symbol");
				continue;
			}
			else if (symbolType == Script::SymbolType::VARIABLE_DEFINITION)
			{
				parseVariableDefinition(sLine, script);
			}
			else if (symbolType == Script::SymbolType::HARD_VALUE)
			{
				m_info.push_back("Line " + std::to_string(m_uiLineNum) + ": Hard-coded value used without context");
				continue;
			}
			else if (symbolType == Script::SymbolType::VARIABLE)
			{
				m_info.push_back("Line " + std::to_string(m_uiLineNum) + ": Variable used value without context");
			}
			else if (symbolType == Script::SymbolType::FUNCTION)
			{
				// If it is a function, recursively parse the parameters until all levels have been resolved
				Function* f = parseFunction(sLine, script);
				if (f != nullptr)
				{
					script.appendFunction(f); 
				}
			}
		}

		return true;
	}
	else
	{
		return false;
	}
}

void ScriptLoader::parseVariableDefinition(std::string& sLine, Script& script)
{
	std::string sVarType = sLine.substr(0, sLine.find_first_of(' '));
	std::string sVarName = sLine.substr(sLine.find_first_of(' ') + 1, std::string::npos);

	// Check for redefinition of a variable
	if (m_variables->find(sVarName) != m_variables->end())
	{
		m_info.push_back("Line " + std::to_string(m_uiLineNum) + ": Redefinition of var '" + sVarName + "' ignored");
		return;
	}

	if (sVarType == "string")
	{
		std::string s = "";
		ScriptVar var(s);
		m_variables->emplace(sVarName, var);
	}
	else if (sVarType == "int")
	{
		int i = 0;
		ScriptVar var(i);
		m_variables->emplace(sVarName, var);
	}
	else if (sVarType == "float")
	{
		float f = 0.f;
		ScriptVar var(f);
		m_variables->emplace(sVarName, var);
	}
	else if (sVarType == "bool")
	{
		bool b = false;
		ScriptVar var(b);
		m_variables->emplace(sVarName, var);
	}
}

Script::SymbolType ScriptLoader::getSymbolType(std::string& sLine)
{
	// Trim leading and trailing whitespace
	sLine = sLine.substr(sLine.find_first_not_of(' '), std::string::npos);
	sLine = sLine.substr(0, sLine.find_last_not_of(' ') + 1);

	// Use the opening bracket to determine the type. If there are brackets, the type
	// is going to be a function or control flow statement
	int iBracketIndex = sLine.find('(');
	if (iBracketIndex == std::string::npos)
	{
		// Check if its a variable definition
		std::string sFirstWord = sLine.substr(0, sLine.find_first_of(' '));
		if (m_variableDefintionSymbols->find(sFirstWord) != m_variableDefintionSymbols->end())
		{
			return Script::SymbolType::VARIABLE_DEFINITION;
		}

		// Check if its a variable (must be previously declared)
		if (m_variables->find(sFirstWord) != m_variables->end())
		{
			return Script::SymbolType::VARIABLE;
		}

		// From here we can only assume it was some hard-coded value
		return Script::SymbolType::HARD_VALUE;
	}
	else
	{
		// Check if its a function. Functions require opening and closing bracket, valid name and valid 
		// parameter count.
		int iClosingBracketIndex = sLine.find_last_of(')');
		if (iClosingBracketIndex == std::string::npos)
		{
			m_info.push_back("Line " + std::to_string(m_uiLineNum) + ": Bad function definition: Expected )");
			return Script::SymbolType::UNKNOWN;
		}
		else
		{
			// Check the name first
			std::string sFunctionName = sLine.substr(0, iBracketIndex);
			if (m_functionRegister->functionExists(sFunctionName))
			{
				return Script::SymbolType::FUNCTION;
			}
			else
			{
				m_info.push_back("Line " + std::to_string(m_uiLineNum) + ": Unknown function '" + sFunctionName + "'");
				return Script::SymbolType::UNKNOWN;
			}
		}
	}
}

unsigned int ScriptLoader::getParamCount(std::string& sLine)
{
	if (sLine.empty())
	{
		return 0;
	}

	unsigned int uiRet = 0;
	unsigned int uiCharsThisParam = 0;
	unsigned int uiBracketDepth = 0;

	// Count each parameters for this function only. If the number of brackets do not match,
	// this function will fail horribly
	for (char& c : sLine)
	{
		if (c == '(')
		{
			++uiBracketDepth;
		}
		else if (c == ')')
		{
			--uiBracketDepth;
		}
		else if (c == ',' && uiBracketDepth == 0 && uiCharsThisParam > 0)
		{
			++uiRet;
			uiCharsThisParam = 0;
		}
		else
		{
			++uiCharsThisParam;
		}
	}

	// Account for the last parameter (if there was one)
	if (uiCharsThisParam > 0)
	{
		++uiRet;
	}

	return uiRet;
}

Function* ScriptLoader::parseFunction(std::string& sLine, Script& script)
{
	// Get the name of the function. This is from the start of the line to the first opening bracket
	int iOpeningBracket = sLine.find_first_of('(');
	int iClosingBracket = sLine.find_last_of(')');
	std::string sFuncName = sLine.substr(0, iOpeningBracket);

	// Get the parameter strings. This is from the first opening bracket to the last closing bracket
	std::vector<std::string> paramStrings = getParamStrings(sLine.substr(iOpeningBracket + 1, iClosingBracket - 1 - iOpeningBracket));
	std::vector<ScriptParam> params;

	// Evaluate the parameters
	for (std::string& s : paramStrings)
	{
		Script::SymbolType symbolType = getSymbolType(s);
		if (symbolType == Script::SymbolType::UNKNOWN)
		{
			m_info.push_back("Line " + std::to_string(m_uiLineNum) + ": Unknown parameter '" + s + "'");
			return nullptr;
		}
		else if (symbolType == Script::SymbolType::VARIABLE_DEFINITION)
		{
			m_info.push_back("Line " + std::to_string(m_uiLineNum) + ": Cannot define a variable in a function parameter");
			return nullptr;
		}
		else if (symbolType == Script::SymbolType::HARD_VALUE)
		{
			params.push_back(ScriptParam(parseHardValue(s), false));
			continue;
		}
		else if (symbolType == Script::SymbolType::VARIABLE)
		{
			std::map<std::string, ScriptVar>::iterator result = m_variables->find(s);
			if (result == m_variables->end())
			{
				m_info.push_back("Line " + std::to_string(m_uiLineNum) + ": Unknown variable '" + s + "'");
			}
			else
			{
				params.push_back(ScriptParam(result->second, true));
			}
			continue;
		}
		else if (symbolType == Script::SymbolType::FUNCTION)
		{
			// If it is a function, recursively parse the parameters until all levels have been resolved
			Function* f = parseFunction(s, script);
			if (f == nullptr)
			{
				return nullptr;
			}
			else
			{
				params.push_back(ScriptParam(f));
				continue;
			}
		}
	}

	Function* f = m_functionRegister->buildFunction(sFuncName, params);
	if (f == nullptr)
	{
		m_info.push_back("Line " + std::to_string(m_uiLineNum) + ": Known function; Bad params");
	}

	return f;
}

ScriptVar ScriptLoader::parseHardValue(std::string& sLine)
{
	// Check if it is a boolean
	if (sLine == "true")
	{
		return ScriptVar(true);
	}
	else if (sLine == "false")
	{
		return ScriptVar(false);
	}

	// Check if the string is entirely numeric (floating points permitted)
	if (isNumeric(sLine))
	{
		// Check for the existence of a floating point
		if (sLine.find('.') == std::string::npos)
		{
			return ScriptVar(std::stoi(sLine));
		}
		else
		{
			return ScriptVar(std::stof(sLine));
		}
	}

	// Finally assume that it is a string
	return ScriptVar(sLine);
}

bool ScriptLoader::isNumeric(std::string& sLine)
{
	// Check each character is a valid numeric character. Also check there is no
	// more than 1 floating point
	bool bPointFound = false;
	for (char& c : sLine)
	{
		bool bCharfound = false;
		for (int i = 0; i < 12; ++i)
		{
			if (c == m_validChars[i])
			{
				bCharfound = true;
				if (c == '.' && bPointFound == false)
				{
					bPointFound = true;
					continue;
				}
				else if (c == '.' && bPointFound == true)
				{
					return false;
				}
			}
		}
		
		if (!bCharfound)
		{
			return false;
		}
	}

	return true;
}

const std::vector<std::string>& ScriptLoader::getInfo() const
{
	return m_info;
}		

std::vector<std::string> ScriptLoader::getParamStrings(std::string& sLineParams)
{


	// Note that we dont need to trim whitespace in this function as it is done during
	// the symbol evaluation stage

	std::vector<std::string> params;

	if (sLineParams.empty())
	{
		return params;
	}

	if (sLineParams.find(',') == std::string::npos)
	{
		params.push_back(sLineParams);
		return params;
	}

	unsigned int uiParamStartIndex = 0;
	unsigned int uiParamEndIndex = 0;
	unsigned int uiBracketDepth = 0;

	for (char& c : sLineParams)
	{
		++uiParamEndIndex;
		if (c == '(')
		{
			++uiBracketDepth;
		}
		else if (c == ')')
		{
			--uiBracketDepth;
		}
		else if (c == ',' && uiBracketDepth == 0)
		{
			params.push_back(sLineParams.substr(uiParamStartIndex, uiParamEndIndex - 1 - uiParamStartIndex));
			uiParamStartIndex = uiParamEndIndex;
		}
	}

	++uiParamStartIndex;
	std::string sLastParam = sLineParams.substr(uiParamStartIndex, uiParamEndIndex - uiParamStartIndex);
	if (sLineParams.size() > 0)
	{
		params.push_back(sLastParam);
	}

	return params;
}
#include "Game/Modules/Script.h"

Script::Script(std::string sName, std::map<std::string, ScriptVar>* variables, ScriptActionTerminal* actionTerminal) :
m_sExecuteScriptAction("execute")
{
	m_sName = sName;
	m_variables = variables;
	m_actionTerminal = actionTerminal;

	addAction(m_sExecuteScriptAction);
}

Script::~Script()
{
	for (Function* f : m_functions)
	{
		delete f;
	}
}

void Script::appendFunction(Function* func)
{
	m_functions.push_back(func);
}

void Script::execute(ScriptInfoPack& pack)
{
	for (Function* i : m_functions)
	{
		i->execute(pack);
	}
}

void Script::onAction(const std::string& sActionName)
{
	if (sActionName == m_sExecuteScriptAction)
	{
		m_actionTerminal->executeScript(m_sName);
	}
}
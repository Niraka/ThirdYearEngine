#include "Game/Modules/ScriptingModule.h"

ScriptingModule::ScriptingModule() :
m_scriptLoader(&m_functionRegister, &m_variables, &m_variableDefintionSymbols),
m_sCommandExecuteScript("execute_script"),
m_sCommandLoadScript("load_script"),
m_sCommandUnloadScript("unload_script"),
m_sInitScriptName("init"),
m_sInitScriptFileName("init.txt")
{

	addServiceDependency(Services::LOGGER);
	addModuleDependency(Modules::WINDOW);
	addModuleDependency(Modules::TIMING);
	addModuleDependency(Modules::RESOURCE);
	addModuleDependency(Modules::AUDIO);
	addModuleDependency(Modules::GUI);
	addModuleDependency(Modules::PHYSICS);
	addModuleDependency(Modules::ACTING);
	addModuleDependency(Modules::ENTITY);
	addModuleDependency(Modules::COMMAND);
	addModuleDependency(Modules::AI);
	addModuleDependency(Modules::EVENTS);

	m_variableDefintionSymbols.emplace("string");
	m_variableDefintionSymbols.emplace("int");
	m_variableDefintionSymbols.emplace("float");
	m_variableDefintionSymbols.emplace("bool");

	// Bind components to the scripting information pack
	m_infoPack.timerRegistrar = this;
	m_infoPack.actionTerminal = this;
	m_infoPack.numberGenerator = &m_numberGenerator;
}

ScriptingModule::~ScriptingModule()
{
}

void ScriptingModule::onUpdate()
{
	Script* s = nullptr;
	while (!m_scriptQueue.empty())
	{
		s = m_scriptQueue.front();
		s->execute(m_infoPack);
		m_scriptQueue.pop();
	}
}

bool ScriptingModule::start()
{
	if (m_loggerNode)
	{
		m_loggerNode->log("Scripting module launching");
	}

	// Output the function bindings info
	if (m_loggerNode)
	{	
		const std::vector<std::string> funcDefs = m_functionRegister.getFunctionDefinitions();
		std::string sSuccessString = "Successfully bound functions:";
		for (const std::string& funcDef : funcDefs)
		{
			sSuccessString += "\n   " + funcDef;
		}
		m_loggerNode->log(sSuccessString);
	}

	if (m_loggerNode)
	{
		m_loggerNode->log("Scripting module successfully launched");
	}
	return true;
}

bool ScriptingModule::stop()
{
	if (m_loggerNode)
	{
		m_loggerNode->log("Scripting module shutting down");
	}

	if (m_loggerNode)
	{
		m_loggerNode->log("Scripting module successfully shut down");
	}
	return true;
}

void ScriptingModule::addTimer(const std::string& sTimerName, const std::string& sScriptName)
{
	m_scriptTimers.push_back(std::make_pair(sTimerName, sScriptName));
}

bool ScriptingModule::loadScript(const std::string& sScriptName, const std::string& sFileName)
{
	if (m_scripts.find(sScriptName) == m_scripts.end())
	{
		m_scripts.emplace(sScriptName, Script(sScriptName, &m_variables, this));
		bool bResult = m_scriptLoader.loadScript(sFileName, m_scripts.at(sScriptName));

		if (m_loggerNode)
		{
			std::vector<std::string> info = m_scriptLoader.getInfo();
			std::string sMessage;
			if (bResult)
			{
				sMessage = "Successfully loaded script '" + sScriptName + "'";
			}
			else
			{
				sMessage = "Failed to load script '" + sScriptName + "'";
			}
		
			for (std::string& s : info)
			{
				sMessage += "\n   " + s;
			}

			m_loggerNode->log(sMessage);
		}

		if (bResult)
		{	
			return true;
		}
		else
		{
			m_scripts.erase(sScriptName);
			return false;
		}
	}
	else
	{
		return false;
	}
}

void ScriptingModule::unloadScript(const std::string& sScriptName)
{
	if (m_scripts.find(sScriptName) != m_scripts.end())
	{
		m_scripts.erase(sScriptName);
	}
}

void ScriptingModule::executeScript(const std::string& sScriptName)
{
	std::map<std::string, Script>::iterator it = m_scripts.find(sScriptName);
	if (it != m_scripts.end())
	{
		it->second.execute(m_infoPack);
	}
}

void* ScriptingModule::getScript(const std::string& sScriptName)
{
	std::map<std::string, Script>::iterator itResult = m_scripts.find(sScriptName);
	if (itResult == m_scripts.end())
	{
		return nullptr;
	}
	else
	{
		return &itResult->second;
	}
}

void ScriptingModule::onTimerExpired(std::string sTimer)
{
	unsigned int uiCrnt = 0;
	unsigned int uiSize = m_scriptTimers.size();
	unsigned int uiRemovals = 0;
	for (; uiCrnt < uiSize - uiRemovals; ++uiCrnt)
	{
		if (m_scriptTimers.at(uiCrnt).first == sTimer)
		{
			// Push the script on to the executable script list if it was valid		
			std::map<std::string, Script>::iterator it = m_scripts.find(m_scriptTimers.at(uiCrnt).second);
			if (it != m_scripts.end())
			{
				m_scriptQueue.push(&(*it).second);
			}
			
			m_scriptTimers.erase(m_scriptTimers.begin() + uiCrnt);

			--uiCrnt;
			++uiRemovals;
		}
	}
}

void ScriptingModule::moduleDependencyBecameAvailable(Modules moduleName, std::shared_ptr<void> module)
{
	switch (moduleName)
	{
	case WINDOW:
		m_infoPack.windowModule = std::static_pointer_cast<WindowModule>(module);
		if (m_loggerNode)
		{
			m_loggerNode->log("Window script functions bound");
		}
		break;
	case TIMING:
		m_infoPack.timingModule = std::static_pointer_cast<TimingModule>(module);
		m_infoPack.timingModule->addTimerListener(this);
		if (m_loggerNode)
		{
			m_loggerNode->log("Timing script functions bound");
		}
		break;
	case RESOURCE:
		m_infoPack.resourceModule = std::static_pointer_cast<ResourceModule>(module);
		if (m_loggerNode)
		{
			m_loggerNode->log("Resource script functions bound");
		}
		break;
	case GUI:
		m_infoPack.guiModule = std::static_pointer_cast<GUIModule>(module);
		if (m_loggerNode)
		{
			m_loggerNode->log("GUI script functions bound");
		}
		break;
	case PHYSICS:
		m_infoPack.physicsModule = std::static_pointer_cast<PhysicsModule>(module);
		if (m_loggerNode)
		{
			m_loggerNode->log("Physics script functions bound");
		}
		break;
	case ACTING:
		m_infoPack.actingModule = std::static_pointer_cast<ActingModule>(module);
		if (m_loggerNode)
		{
			m_loggerNode->log("Acting script functions bound");
		}
		break;
	case ENTITY:
		m_infoPack.entityModule = std::static_pointer_cast<EntityModule>(module);
		if (m_loggerNode)
		{
			m_loggerNode->log("Entity script functions bound");
		}
		break;
	case AI:
		m_infoPack.aiModule = std::static_pointer_cast<AIModule>(module);
		if (m_loggerNode)
		{
			m_loggerNode->log("AI script functions bound");
		}
		break;
	case COMMAND:
		m_commandNode = std::static_pointer_cast<CommandModule>(module)->createCommandNode();
		m_commandNode->addCommandListener(this);
		m_commandNode->addCommand(m_sCommandExecuteScript, 1);
		m_commandNode->addCommand(m_sCommandLoadScript, 2);
		m_commandNode->addCommand(m_sCommandUnloadScript, 1);
		break;
	case EVENTS:
		m_eventModule = std::static_pointer_cast<EventModule>(module);
		m_eventModule->addListener(this);
		m_uiEngineLaunchedEvent = m_eventModule->getEventId("engine_launch_finished", this);
		break;
	case AUDIO:
		m_infoPack.audioModule = std::static_pointer_cast<AudioModule>(module);
		if (m_loggerNode)
		{
			m_loggerNode->log("Audio script functions bound");
		}
		break;
	default:
		break;
	}
}

void ScriptingModule::moduleDependencyBecameUnavailable(Modules moduleName)
{
	switch (moduleName)
	{
	case WINDOW:
		m_infoPack.windowModule = nullptr;
		if (m_loggerNode)
		{
			m_loggerNode->log("Window script functions unbound");
		}
		break;
	case TIMING:
		m_infoPack.timingModule = nullptr;
		if (m_loggerNode)
		{
			m_loggerNode->log("Timing script functions unbound");
		}
		break;
	case RESOURCE:
		m_infoPack.resourceModule = nullptr;
		if (m_loggerNode)
		{
			m_loggerNode->log("Resource script functions unbound");
		}
		break;
	case GUI:
		m_infoPack.guiModule = nullptr;
		if (m_loggerNode)
		{
			m_loggerNode->log("GUI script functions unbound");
		}
		break;
	case PHYSICS:
		m_infoPack.physicsModule = nullptr;
		if (m_loggerNode)
		{
			m_loggerNode->log("Physics script functions unbound");
		}
		break;
	case ACTING:
		m_infoPack.actingModule = nullptr;
		if (m_loggerNode)
		{
			m_loggerNode->log("Acting script functions unbound");
		}
		break;
	case ENTITY:
		m_infoPack.entityModule = nullptr;
		if (m_loggerNode)
		{
			m_loggerNode->log("Entity script functions unbound");
		}
		break;
	case AI:
		m_infoPack.aiModule = nullptr;
		if (m_loggerNode)
		{
			m_loggerNode->log("AI script functions unbound");
		}
		break;
	case COMMAND:
		m_commandNode = nullptr;
		break;
	case EVENTS:
		m_uiEngineLaunchedEvent = 0;
		break;
	case AUDIO:
		m_infoPack.audioModule = nullptr;
		if (m_loggerNode)
		{
			m_loggerNode->log("Audio script functions unbound");
		}
		break;
	default:
		break;
	}
}

void ScriptingModule::serviceDependencyBecameAvailable(Services serviceName, std::shared_ptr<void> service)
{
	if (serviceName == Services::LOGGER)
	{
		std::shared_ptr<LoggerService> loggerService = std::static_pointer_cast<LoggerService>(service);
		m_loggerNode = loggerService->createLoggerNode("SC");
		m_infoPack.loggerNode = loggerService->createLoggerNode("ES");
	}
}

void ScriptingModule::serviceDependencyBecameUnavailable(Services serviceName)
{
	if (serviceName == Services::LOGGER)
	{
		m_loggerNode = nullptr;
		m_infoPack.loggerNode = nullptr;
	}
}

void ScriptingModule::onCommandReceived(std::string sCommandName, std::vector<std::string> args)
{
	if (sCommandName == m_sCommandExecuteScript)
	{
		executeScript(args.at(0));
	}
	else if (sCommandName == m_sCommandLoadScript)
	{
		loadScript(args.at(0), args.at(1));
	}
	else if (sCommandName == m_sCommandUnloadScript)
	{
		unloadScript(args.at(0));
	}
}

void ScriptingModule::onEvent(const unsigned int& uiEventId)
{
	if (uiEventId == m_uiEngineLaunchedEvent)
	{
		if (loadScript(m_sInitScriptName, m_sInitScriptFileName))
		{
			executeScript(m_sInitScriptName);
		}
		else
		{
			if (m_loggerNode)
			{
				m_loggerNode->log("Could not find initialisation script 'init.txt'");
			}
		}
	}
}

void ScriptingModule::onEventRegistered(const std::string& sEventName, const unsigned int& uiEventId)
{
	if (sEventName == "engine_launch_finished")
	{
		m_uiEngineLaunchedEvent = uiEventId;
	}
}
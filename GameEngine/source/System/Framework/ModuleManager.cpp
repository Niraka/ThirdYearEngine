#include "System/Framework/ModuleManager.h"

ModuleManager::ModuleManager()
{
}

ModuleManager::~ModuleManager()
{
}

std::shared_ptr<EventModule> ModuleManager::getEventModule()
{
	return std::static_pointer_cast<EventModule>(m_modules.at(Modules::EVENTS));
}

bool ModuleManager::startModule(Modules module)
{
	// Check the module is not already active. If it is, stop it first
	if (m_modules.find(module) != m_modules.end())
	{
		stopModule(module);
	}

	// Start the new module
	switch (module)
	{
	case COMMAND:
		m_modules.emplace(module, std::make_shared<CommandModule>());
		break;
	case WINDOW:
		m_modules.emplace(module, std::make_shared<WindowModule>());
		break;
	case TIMING:
		m_modules.emplace(module, std::make_shared<TimingModule>());
		break;
	case AUDIO:
		m_modules.emplace(module, std::make_shared<AudioModule>());
		break;
	case RESOURCE:
		m_modules.emplace(module, std::make_shared<ResourceModule>());
		break;
	case EVENTS:
		m_modules.emplace(module, std::make_shared<EventModule>());
		break;
	case GUI:
		m_modules.emplace(module, std::make_shared<GUIModule>());
		break;
	case PHYSICS:
		m_modules.emplace(module, std::make_shared<PhysicsModule>());
		break;
	case ACTING:
		m_modules.emplace(module, std::make_shared<ActingModule>());
		break;
	case ENTITY:
		m_modules.emplace(module, std::make_shared<EntityModule>());
		break;
	case AI:
		//m_modules.emplace(module, std::make_shared<AIModule>());
		break;
	case PARTICLE:
		//m_modules.emplace(module, std::make_shared<ParticleModule>());
		break;
	case SCRIPTING:
		m_modules.emplace(module, std::make_shared<ScriptingModule>());
		break;
	case EDITOR:
		m_modules.emplace(module, std::make_shared<EditorModule>());
		break;
	default:
		return false;
	}

	if (m_modules.find(module) == m_modules.end())
	{
		return false;
	}

	if (module == Modules::COMMAND)
	{
		m_commandNode = std::static_pointer_cast<CommandModule>(m_modules.at(module))->createCommandNode();
		m_commandNode->addCommand("start_module", 1);
		m_commandNode->addCommand("stop_module", 1);
		m_commandNode->addCommand("restart_module", 1);
		m_commandNode->addCommandListener(this);
	}

	// Notify existing modules and services that the new module has been launched
	if (m_moduleLifetimeListener)
	{
		m_moduleLifetimeListener->onModuleStarted(module, m_modules.at(module));
	}
	onModuleStarted(module, m_modules.at(module));
	
	// Initialise the new module
	if (m_modules.at(module)->start())
	{
		return true;
	}
	else
	{
		std::cout << "FATAL: Module '" << moduleAsString(module) << "' failed to start" << std::endl;
		return false;
	}
}

bool ModuleManager::stopModule(Modules module)
{
	if (module == Modules::COMMAND)
	{
		m_commandNode = nullptr;
	}

	// Check the module exists
	if (m_modules.find(module) != m_modules.end())
	{
		onModuleStopped(module);
		if (m_moduleLifetimeListener)
		{
			m_moduleLifetimeListener->onModuleStopped(module);
		}
		m_modules.at(module)->stop();
		m_modules.erase(module);
		return true;
	}
	else
	{
		return false;
	}
}

void ModuleManager::update()
{
	// Call update on each module
	for (const std::pair<Modules, std::shared_ptr<Module>> module : m_modules)
	{
		module.second->update();
	}
}

void ModuleManager::bindModuleLifetimeListener(ModuleLifetimeListener* l)
{
	m_moduleLifetimeListener = l;
}

void ModuleManager::onModuleStarted(Modules moduleName, std::shared_ptr<Module> module)
{
	// For each active module, check if it is interested in the module starting
	for (const std::pair<Modules, std::shared_ptr<Module>>& p : m_modules)
	{
		if (p.second->hasModuleDependency(moduleName))
		{
			p.second->moduleDependencyBecameAvailable(moduleName, module);
		}
	}

	// Check whether the newly started up module is interested in any existing modules
	for (const std::pair<Modules, std::shared_ptr<Module>>& p : m_modules)
	{
		if (module->hasModuleDependency(p.first))
		{
			module->moduleDependencyBecameAvailable(p.first, p.second);
		}
	}
}

void ModuleManager::onModuleStopped(Modules moduleName)
{
	// For each active module, check if it is interested in the module stopping
	for (const std::pair<Modules, std::shared_ptr<Module>>& p : m_modules)
	{
		if (p.second->hasModuleDependency(moduleName))
		{
			p.second->moduleDependencyBecameUnavailable(moduleName);
		}
	}
}

void ModuleManager::onServiceStarted(Services serviceName, std::shared_ptr<Service> service)
{
	// For each active module, check if it is interested in the service starting
	for (const std::pair<Modules, std::shared_ptr<Module>>& p : m_modules)
	{
		if (p.second->hasServiceDependency(serviceName))
		{
			p.second->serviceDependencyBecameAvailable(serviceName, service);
		}
	}

	// Check whether the newly started up service is interested in any existing modules
	for (const std::pair<Modules, std::shared_ptr<Module>>& p : m_modules)
	{
		if (service->hasModuleDependency(p.first))
		{
			service->moduleDependencyBecameAvailable(p.first, p.second);
		}
	}
}

void ModuleManager::onServiceStopped(Services serviceName)
{
	// For each active module, check if it is interested in the service stopping
	for (const std::pair<Modules, std::shared_ptr<Module>>& p : m_modules)
	{
		if (p.second->hasServiceDependency(serviceName))
		{
			p.second->serviceDependencyBecameUnavailable(serviceName);
		}
	}
}

std::string ModuleManager::moduleAsString(Modules module)
{
	switch (module)
	{
	case COMMAND:
		return "command";
	case WINDOW:
		return "window";
	case TIMING:
		return "timing";
	case AUDIO:
		return "audio";
	case RESOURCE:
		return "resource";
	case EVENTS:
		return "events";
	case GUI:
		return "GUI";
	case PHYSICS:
		return "physics";
	case ACTING:
		return "acting";
	case ENTITY:
		return "entity";
	case AI:
		return "AI";
	case PARTICLE:
		return "particle";
	case SCRIPTING:
		return "scripting";
	case EDITOR:
		return "editor";
	default:
		return "unknown_module";
	}
}

void ModuleManager::onCommandReceived(std::string sCommandName, std::vector<std::string> args)
{
	if (sCommandName == "start_module")
	{
		if (args.at(0) == "resource")
		{
			startModule(Modules::RESOURCE);
		}
		else if (args.at(0) == "acting")
		{
			startModule(Modules::ACTING);
		}
	}
	else if (sCommandName == "stop_module")
	{
		if (args.at(0) == "resource")
		{
			stopModule(Modules::RESOURCE);
		}
		else if (args.at(0) == "acting")
		{
			stopModule(Modules::ACTING);
		}
	}
	else if (sCommandName == "restart_module")
	{
		if (args.at(0) == "resource")
		{
			stopModule(Modules::RESOURCE);
			startModule(Modules::RESOURCE);
		}
		else if (args.at(0) == "acting")
		{
			stopModule(Modules::ACTING);
			startModule(Modules::ACTING);
		}
	}
}
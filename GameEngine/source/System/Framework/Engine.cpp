#include "System/Framework/Engine.h"

Engine::Engine() :
m_uiMinLR(1),
m_uiMaxLR(100)
{
	m_bInitialised = false;
	m_bRunningUser = false;
	m_bRunningSystem = false;
}

void Engine::run()
{
	m_bRunningSystem = true;

	// Enter engine loop
	m_fTimeNow = glfwGetTime();
	m_fNextUpdateTime = m_fTimeNow;
	while (m_bRunningUser)
	{
		if (m_fTimeNow >= m_fNextUpdateTime)
		{
			// Perform updates and calculate the next update time
			m_moduleManager.update();
			m_fNextUpdateTime += m_fTimeInterval;
		}
		else
		{
			std::this_thread::sleep_for(m_sleepDuration);
		}

		m_fTimeNow = glfwGetTime();
	}

	// Shut down and clean up any resources
	m_moduleManager.stopModule(Modules::SCRIPTING);
	m_moduleManager.stopModule(Modules::EDITOR);
	m_moduleManager.stopModule(Modules::ENTITY);
	m_moduleManager.stopModule(Modules::AUDIO);
	m_moduleManager.stopModule(Modules::TIMING);
	m_moduleManager.stopModule(Modules::GUI);
	m_moduleManager.stopModule(Modules::ACTING);
	m_moduleManager.stopModule(Modules::PHYSICS);
	m_moduleManager.stopModule(Modules::COMMAND);
	m_moduleManager.stopModule(Modules::WINDOW);
	m_moduleManager.stopModule(Modules::RESOURCE);
	m_moduleManager.stopModule(Modules::EVENTS);
	m_serviceManager.stopService(Services::FILE_SYSTEM_WATCHER);
	m_serviceManager.stopService(Services::LOGGER);
	m_serviceManager.stopService(Services::MODULE_WATCHER);
	m_serviceManager.stopService(Services::RESOURCE_CLEANER);
	m_serviceManager.stopService(Services::RESOURCE_USAGE_TRACKER);

	glfwTerminate();
	m_thread = nullptr;
	m_bRunningSystem = false;
}

bool Engine::initialise()
{
	// Initialise GLFW and OpenGL bindings
	if (!glfwInit())
	{
		return false;
	}

	// Create and load the engine configuration
	m_configManager = ConfigurationManager::getInstance();	
	m_configManager->loadConfig();

	// Set some default properties
	m_uiLogicRate = m_configManager->getLogicRate();
	if (m_uiLogicRate < m_uiMinLR)
	{
		m_uiLogicRate = m_uiMinLR;
	}
	if (m_uiLogicRate > m_uiMaxLR)
	{
		m_uiLogicRate = m_uiMaxLR;
	}
	
	m_fTimeInterval = 1.f / (float) m_uiLogicRate;
	m_uiSleepTime = (unsigned int)(1000.f / (float) m_uiLogicRate);
	m_sleepDuration = std::chrono::milliseconds(m_uiSleepTime);

	m_moduleManager.bindModuleLifetimeListener(&m_serviceManager);
	m_serviceManager.bindServiceLifetimeListener(&m_moduleManager);

	// Start up the system modules and services
	m_serviceManager.startService(Services::LOGGER);
	m_serviceManager.startService(Services::FILE_SYSTEM_WATCHER);
	m_serviceManager.startService(Services::MODULE_WATCHER);
	m_serviceManager.startService(Services::RESOURCE_CLEANER);
	m_serviceManager.startService(Services::RESOURCE_USAGE_TRACKER);
	m_moduleManager.startModule(Modules::EVENTS);
	m_moduleManager.startModule(Modules::RESOURCE);
	m_moduleManager.startModule(Modules::WINDOW);
	m_moduleManager.startModule(Modules::TIMING);
	m_moduleManager.startModule(Modules::AUDIO);
	m_moduleManager.startModule(Modules::PHYSICS);
	m_moduleManager.startModule(Modules::COMMAND);
	m_moduleManager.startModule(Modules::ACTING);
	m_moduleManager.startModule(Modules::GUI);
	m_moduleManager.startModule(Modules::ENTITY);
	m_moduleManager.startModule(Modules::SCRIPTING);
	m_moduleManager.startModule(Modules::EDITOR);

	// Bind the lifetime of the engine to the windows existence
	WindowEventsManager* wem = WindowEventsManager::getInstance();
	wem->addWindowListener(this);

	InputManager* im = InputManager::getInstance();
	im->addInputListener(this);

	// Return success
	m_bInitialised = true;
	return true;
}

bool Engine::start()
{
	if (!m_bInitialised)
	{
		std::cout << "EN : Must initialise before launching" << std::endl;
		return false;
	}

	if (m_bRunningUser || m_bRunningSystem)
	{
		std::cout << "EN : Engine already running" << std::endl;
		return false;
	}

	m_bRunningUser = true;
	
	// Launch an event to indicate that the engine has finished launching
	std::shared_ptr<EventModule> mod = m_moduleManager.getEventModule();
	mod->registerEvent("engine_launch_finished");
	unsigned int uiEngineLaunchEventId = mod->getEventId("engine_launch_finished");
	mod->launchEvent(uiEngineLaunchEventId);

	run();
	return true;
}

void Engine::stop()
{
	m_bInitialised = false;
	m_bRunningUser = false;
}

void Engine::onWindowClose()
{
	stop();
}

void Engine::onKeyPressed(int iKey, int iScancode, int iMods)
{
	if (iKey == GLFW_KEY_ESCAPE)
	{
		stop();
	}
}
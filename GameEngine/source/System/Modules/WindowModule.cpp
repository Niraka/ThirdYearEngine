#include "System/Modules/WindowModule.h"

WindowModule::WindowModule()
{
	m_bRenderingContextValid = false;
	m_bRendering = false;
	m_window = nullptr;
	m_inputManager = InputManager::getInstance();
	m_windowEventsManager = WindowEventsManager::getInstance();

	addServiceDependency(Services::LOGGER);
	addModuleDependency(Modules::EVENTS);
}

WindowModule::~WindowModule()
{
	m_bRendering = false;
}

void WindowModule::repositionWindow()
{
	ConfigurationManager* config = ConfigurationManager::getInstance();
	WindowStyle windowStyle = config->getWindowStyle();

	// Check the validity of the monitor and the window
	if (!m_window || !m_monitor)
	{
		return;
	}

	// Check whether the reposition should be done - if not, instantly return
	if (windowStyle == WindowStyle::WINDOWED || windowStyle == WindowStyle::WINDOWED_BORDERLESS)
	{
		const GLFWvidmode* m_videoMode = glfwGetVideoMode(m_monitor);
		switch (config->getWindowPositionStyle())
		{
		case WindowPositionStyle::TOP_LEFT:
			glfwSetWindowPos(m_window, 0, 0);
			break;
		case WindowPositionStyle::CENTRE:
			glfwSetWindowPos(
				m_window,
				(m_videoMode->width / 2) - (config->getWindowWidth() / 2),
				(m_videoMode->height / 2) - (config->getWindowHeight() / 2));
			break;
		}
	}
}

bool WindowModule::createWindow()
{
	// Check the monitor is valid
	if (!m_monitor)
	{
		return false;
	}

	// Grab a reference to the configuration manager so that the window can be constructed
	// to the desired specification
	ConfigurationManager* config = ConfigurationManager::getInstance();

	// Set the window to invisible so that it can be positioned before displaying
	glfwWindowHint(GLFW_VISIBLE, false);

	// Select the OpenGL profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// If the window was already active, kill it
	if (m_window)
	{
		glfwDestroyWindow(m_window);
		if (m_eventModule)
		{
			m_eventModule->launchEvent(m_uiWindowClosedId);
		}
	}

	// Create the window according to the desired specification. The default behaviour
	// is to create a windowed window
	WindowStyle windowStyle = config->getWindowStyle();
	unsigned int uiWindowWidth = config->getWindowWidth();
	unsigned int uiWindowHeight = config->getWindowHeight();
	switch (windowStyle)
	{
	case WindowStyle::WINDOWED:
		glfwWindowHint(GLFW_RESIZABLE, true);
		glfwWindowHint(GLFW_DECORATED, true);
		m_window = glfwCreateWindow(
			uiWindowWidth,
			uiWindowHeight,
			config->getWindowTitle().c_str(),
			nullptr,
			nullptr);
		break;

	case WindowStyle::WINDOWED_BORDERLESS:
		glfwWindowHint(GLFW_RESIZABLE, false);
		glfwWindowHint(GLFW_DECORATED, false);
		m_window = glfwCreateWindow(
			uiWindowWidth,
			uiWindowHeight,
			config->getWindowTitle().c_str(),
			nullptr,
			nullptr);
		break;

	case WindowStyle::FULLSCREEN:
		m_window = glfwCreateWindow(
			uiWindowWidth,
			uiWindowHeight,
			config->getWindowTitle().c_str(),
			m_monitor,
			nullptr);
		break;

	default:
		glfwWindowHint(GLFW_RESIZABLE, true);
		glfwWindowHint(GLFW_DECORATED, true);
		m_window = glfwCreateWindow(
			uiWindowWidth,
			uiWindowHeight,
			config->getWindowTitle().c_str(),
			nullptr,
			nullptr);
		break;
	}

	// Check that the window was successfully created
	if (!m_window)
	{
		return false;
	}	
	glfwMakeContextCurrent(m_window);
	if (m_eventModule)
	{
		m_eventModule->launchEvent(m_uiWindowOpenedId);
	}

	// This MUST be called AFTER making the context current
	glewExperimental = true;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		return false;
	}

	// Bind input & window response
	glfwSetCharCallback(m_window, &InputManager::char_callback);
	glfwSetScrollCallback(m_window, &InputManager::scroll_callback);
	glfwSetCursorPosCallback(m_window, &InputManager::cursorPosition_callback);
	glfwSetCursorEnterCallback(m_window, &InputManager::cursorEnter_callback);
	glfwSetMouseButtonCallback(m_window, &InputManager::mouse_callback);
	glfwSetKeyCallback(m_window, &InputManager::key_callback);

	glfwSetWindowCloseCallback(m_window, &WindowEventsManager::windowCloseCallback);
	glfwSetWindowSizeCallback(m_window, &WindowEventsManager::windowResizedCallback);
	glfwSetFramebufferSizeCallback(m_window, &WindowEventsManager::frameBufferResizedCallback);

	// Activate the window
	repositionWindow();
	m_bRenderingContextValid = true;
	glfwShowWindow(m_window);

	return true;
}

void WindowModule::onUpdate()
{
	// Poll events
	glfwPollEvents();
	
	// Update logic
	m_sceneManager.updateScene();

	if (m_bRenderingContextValid && m_bRendering)
	{
		// Render
		m_sceneManager.renderScene();

		// Display
		glfwSwapBuffers(m_window);
	}
}

bool WindowModule::start()
{
	if (m_loggerNode)
	{
		m_loggerNode->log("Window module launching");
	}

	// Grab the primary monitor. There is no support for multi-monitor
	m_monitor = glfwGetPrimaryMonitor();
	if (!m_monitor)
	{
		return false;
	}

	// Create the window
	if (!createWindow())
	{
		if (m_loggerNode)
		{
			m_loggerNode->log("Window creation failed");
		}
		return false;
	}
	m_bRendering = true;

	// Create a shader
	createShaders("multi_light");

	m_sceneManager.addListener(this);
	
	if (m_loggerNode)
	{
		m_loggerNode->log("Window module successfully launched");
	}

	return true;
}

bool WindowModule::stop()
{
	if (m_eventModule)
	{
		m_eventModule->deregisterEvent(m_uiSceneChangedId);
		m_eventModule->deregisterEvent(m_uiWindowOpenedId);
		m_eventModule->deregisterEvent(m_uiWindowClosedId);
	}

	InputManager::getInstance()->clearListeners();

	m_bRenderingContextValid = false;
	m_bRendering = false;
	glfwHideWindow(m_window);
	glfwDestroyWindow(m_window);
	return true;
}

bool WindowModule::createShaders(std::string sShaderName)
{
	if (m_shaderManager.shaderExists(sShaderName))
	{
		if (m_loggerNode)
		{
			m_loggerNode->log(sShaderName + " shader already existed");
		}
		return false;
	}

	bool bSuccess = m_shaderManager.createShaders(sShaderName);
	
	if (m_loggerNode)
	{
		if (bSuccess)
		{
			m_loggerNode->log(sShaderName + " shader compilation successful");
		}
		else
		{
			m_loggerNode->log(sShaderName + " shader compilation failed");
		}
	}

	return bSuccess;
}

std::shared_ptr<Scene> WindowModule::createScene(std::string sSceneName)
{
	return m_sceneManager.createScene(sSceneName);
}

std::shared_ptr<Scene> WindowModule::getScene(std::string sSceneName)
{
	return m_sceneManager.getScene(sSceneName);
}

bool WindowModule::sceneExists(std::string sSceneName)
{
	return m_sceneManager.sceneExists(sSceneName);
}

void WindowModule::deleteScene(std::string sSceneName)
{
	m_sceneManager.deleteScene(sSceneName);
}

bool WindowModule::activateScene(std::string sSceneName)
{
	return m_sceneManager.activateScene(sSceneName);
}

bool WindowModule::sceneIsActive(std::string sSceneName)
{
	return m_sceneManager.sceneIsActive(sSceneName);
}

bool WindowModule::deactivateScene(std::string sSceneName, bool bSceneChangeEvent)
{
	return m_sceneManager.deactivateScene(sSceneName, bSceneChangeEvent);
}

void WindowModule::addSceneManagerListener(SceneManagerListener* l)
{
	m_sceneManager.addListener(l);
}

int WindowModule::removeSceneManagerListener(SceneManagerListener* l)
{
	return m_sceneManager.removeListener(l);
}

void WindowModule::serviceDependencyBecameAvailable(Services serviceName, std::shared_ptr<void> service)
{
	if (serviceName == Services::LOGGER)
	{
		std::shared_ptr<LoggerService> loggerService = std::static_pointer_cast<LoggerService>(service);
		if (loggerService)
		{
			m_loggerNode = loggerService->createLoggerNode("WI");
		}
	}
}

void WindowModule::serviceDependencyBecameUnavailable(Services serviceName)
{
	if (serviceName == Services::LOGGER)
	{
		m_loggerNode = nullptr;
	}
}

void WindowModule::moduleDependencyBecameAvailable(Modules moduleName, std::shared_ptr<void> module)
{
	if (moduleName == Modules::EVENTS)
	{
		m_eventModule = std::static_pointer_cast<EventModule>(module);
		m_uiSceneChangedId = m_eventModule->registerEvent("scene_changed");
		m_uiWindowOpenedId = m_eventModule->registerEvent("window_closed");
		m_uiWindowClosedId = m_eventModule->registerEvent("window_opened");
	}
}

void WindowModule::moduleDependencyBecameUnavailable(Modules moduleName)
{
	if (moduleName == Modules::EVENTS)
	{
		m_eventModule = nullptr;
	}
}

void WindowModule::setRendering(bool bRendering)
{
	m_bRendering = bRendering;
}

void WindowModule::onPropertyUpdated(ConfigurationProperties prop)
{
	ConfigurationManager* config = ConfigurationManager::getInstance();

	switch (prop)
	{
	case ConfigurationProperties::WINDOW_TITLE:
		if (m_window)
		{
			glfwSetWindowTitle(m_window, config->getWindowTitle().c_str());
		}
		break;
	case ConfigurationProperties::WINDOW_WIDTH:
		if (m_window)
		{
			glfwSetWindowSize(m_window, config->getWindowWidth(), config->getWindowHeight());
			repositionWindow();
		}
		break;
	case ConfigurationProperties::WINDOW_HEIGHT:
		if (m_window)
		{
			glfwSetWindowSize(m_window, config->getWindowWidth(), config->getWindowHeight());
			repositionWindow();
		}
		break;
	case ConfigurationProperties::WINDOW_STYLE:
		if (m_window)
		{
			m_bRenderingContextValid = false;

			glfwHideWindow(m_window);
			glfwDestroyWindow(m_window);
			createWindow();

			m_bRenderingContextValid = true;
		}
		break;
	case ConfigurationProperties::WINDOW_POS:
		if (m_window)
		{
			if (config->getWindowPositionStyle() != WindowPositionStyle::FREE)
			{
				repositionWindow();
			}
		}
		break;
	}
}

void WindowModule::addInputListener(InputListener* l)
{
	if (m_inputManager)
	{
		m_inputManager->addInputListener(l);
	}
}

int WindowModule::removeInputListener(InputListener* l)
{
	if (m_inputManager)
	{
		return m_inputManager->removeInputListener(l);
	}
	else
	{
		return -1;
	}
}

void WindowModule::onSceneChanged(std::string sNewScene, std::string sOldScene)
{
	// Unlink the old scenes input listener and link the new one
	// Unlink the old scenes shaders and link the new one. The old one is unlinked for
	// house-keeping purposes
	if (m_sceneManager.sceneExists(sOldScene))
	{
		m_inputManager->removeInputListener(&(*m_sceneManager.getScene(sOldScene)));
		m_sceneManager.getScene(sOldScene)->linkComponents(nullptr, nullptr);
	}
	if (m_sceneManager.sceneExists(sNewScene))
	{
		m_inputManager->addInputListener(&(*m_sceneManager.getScene(sNewScene)));
		m_sceneManager.getScene(sNewScene)->linkComponents(m_window, &m_shaderManager);
	}

	if (m_eventModule)
	{
		m_eventModule->launchEvent(m_uiSceneChangedId);
	}
}
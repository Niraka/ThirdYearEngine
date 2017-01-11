#include "Scene/Modules/GUIModule.h"

GUIModule::GUIModule()
{
	addServiceDependency(Services::LOGGER);
	addModuleDependency(Modules::RESOURCE);
	addModuleDependency(Modules::WINDOW);
	m_activeGUI = "NO_GUI";	
}

GUIModule::~GUIModule()
{
}

bool GUIModule::start()
{
	if (m_loggerNode)
	{
		m_loggerNode->log("GUI module launching");
	}

	WindowEventsManager* windMan = WindowEventsManager::getInstance();
	windMan->addWindowListener(this);

	//if (FT_Init_FreeType(&m_libray))		//initilize freetype libaray
	//{
	//	m_loggerNode->log("FreeType libaray failed to initilize");
	//}
	//std::string fontDir = DirectoryListing::getInstance()->getDirectory("fonts") + "\\arial.ttf";
	//if (FT_New_Face(m_libray, fontDir.c_str(), 0, &m_face))		//initilize font face
	//{
	//	m_loggerNode->log("Font file failed to open");
	//}
	//FT_Set_Pixel_Sizes(m_face, 0, 48);
	//g = m_face->glyph;		//Shortcut function to access a glyph (following a tutorial)

	if (m_loggerNode)
	{
		m_loggerNode->log("GUI module successully launched");
	}
	return true;
}

bool GUIModule::stop()
{
	return true;
}

void GUIModule::onUpdate()
{
}

void GUIModule::addComponentSet(std::string idname, std::vector<std::shared_ptr<UIComponent>> component)
{
	int vecSize = component.size();
	for (int i = 0; i < vecSize; ++i)
	{
		component.at(i)->updateWidth(1200);
		component.at(i)->updateHeight(800);
	}

	m_components.insert(std::pair<std::string, std::vector<std::shared_ptr<UIComponent>>>(idname, component));
}

void GUIModule::moduleDependencyBecameAvailable(Modules moduleName, std::shared_ptr<void> module)
{
	if (moduleName == Modules::WINDOW)
	{
		// Bind the rendering and input listeners to the window module
		m_windowModule = std::static_pointer_cast<WindowModule>(module);
		if (m_windowModule)
		{
			m_windowModule->addInputListener(this);
			m_windowModule->createShaders("image_shader");
			m_windowModule->addSceneManagerListener(this);
		}
	}
	else if (moduleName == Modules::RESOURCE)
	{
		m_resourceModule = std::static_pointer_cast<ResourceModule>(module);		//add pointer to the resource module
	}
}

void GUIModule::moduleDependencyBecameUnavailable(Modules moduleName)
{
	if (moduleName == Modules::TIMING)
	{
		m_timingModule = nullptr;
	}
	if (moduleName == Modules::RESOURCE)
	{
		m_resourceModule = nullptr;
	}
}

void GUIModule::render(ShaderManager& shaderManager, const RenderData& data)
{
	if (m_components.count(m_activeGUI) != 0)
	{
		for (std::shared_ptr<UIComponent>& c : m_components.at(m_activeGUI))
		{
			c->render(shaderManager, data);
		}
	}
}

void GUIModule::onCursorMoved(double fXPos, double fYPos)
{
	m_mouseX = fXPos;
	m_mouseY = fYPos;
}

void GUIModule::onMousePressed(int iButton, int iMods)
{
	if (m_components.count(m_activeGUI) != 0)
	{
		if (iButton == GLFW_MOUSE_BUTTON_LEFT)
		{
			for (std::shared_ptr<UIComponent>& c : m_components.at(m_activeGUI))
			{
				if (c->getType() == UIComponent::UIType::BUTTON && c->checkClick(m_mouseX, m_mouseY))		//if this clicks on an object that is a button
				{
					this->performButtonAction(c->getName());
				}
			}
		}
	}
	
}

void GUIModule::serviceDependencyBecameAvailable(Services serviceName, std::shared_ptr<void> service)
{
	if (serviceName == Services::LOGGER)
	{
		std::shared_ptr<LoggerService> loggerService = std::static_pointer_cast<LoggerService>(service);
		if (loggerService)
		{
			m_loggerNode = loggerService->createLoggerNode("UI");
		}
	}
}

void GUIModule::serviceDependencyBecameUnavailable(Services serviceName)
{
	if (serviceName == Services::LOGGER)
	{
		m_loggerNode = nullptr;
	}
}

void GUIModule::performButtonAction(std::string buttonName)
{
	if (buttonName == "startbutton")
	{
		//execute start game scirpt
	}
	else if (buttonName == "exitbutton")
	{
		//execute close game script
	}
}

void GUIModule::onSceneChanged(std::string sNewScene, std::string sOldScene)
{
	if (sNewScene == "title_screen")
	{
		this->setActiveUI("title_screen");
		m_windowModule->getScene("title_screen")->addRenderable(this);
	}
}

void GUIModule::setActiveUI(std::string newUI)
{
	m_activeGUI = newUI;
}

std::string GUIModule::getActiveUI()
{
	return m_activeGUI;
}

void GUIModule::onWindowClose()
{
}

void GUIModule::onWindowResized(int iWidth, int iHeight)
{
	if (m_components.find(m_activeGUI) != m_components.end())
	{
		for (std::shared_ptr<UIComponent>& c : m_components.at(m_activeGUI))
		{
			c->updateHeight(iHeight);
			c->updateWidth(iWidth);
		}
	}
}

void GUIModule::onFramebufferResized(int iWidth, int iHeight)
{
}
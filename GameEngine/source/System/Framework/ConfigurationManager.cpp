#include "System/Framework/ConfigurationManager.h"

bool ConfigurationManager::m_bInstanceExists;
ConfigurationManager* ConfigurationManager::m_instance;

ConfigurationManager::ConfigurationManager() :
m_sFileName(".//..//data//config//engine_properties.xml")
{	
	m_bInstanceExists = true;
	
	// Set the default configuration
	m_bLoggerServiceEnabled = true;

	m_uiLogicRate = 60;

	m_sWindowTitle = "Game Engine";
	m_windowStyle = WindowStyle::WINDOWED;
	m_windowPositionStyle = WindowPositionStyle::CENTRE;
	m_uiWindowWidth = 1200;
	m_uiWindowHeight = 800;
}

ConfigurationManager::~ConfigurationManager()
{
	m_bInstanceExists = false;
}

ConfigurationManager* ConfigurationManager::getInstance()
{
	if (m_bInstanceExists)
	{
		return m_instance;
	}
	else
	{
		m_instance = new ConfigurationManager();
		return m_instance;
	}
}

void ConfigurationManager::launchEventPropertyUpdated(ConfigurationProperties prop)
{
	int iSize = m_configListeners.size();
	for (int i = 0; i < iSize; ++i)
	{
		m_configListeners.at(i)->onPropertyUpdated(prop);
	}
}

void ConfigurationManager::addConfigListener(ConfigurationListener* l)
{
	m_configListeners.add(l);
}

void ConfigurationManager::removeConfigListener(ConfigurationListener* l)
{
	m_configListeners.remove(l);
}

bool ConfigurationManager::loadConfig()
{
	// Parse the configuration and launch events where change occurs
	tinyxml2::XMLDocument doc;
	int iLoadResult = doc.LoadFile(m_sFileName.c_str());
	if (iLoadResult == tinyxml2::XML_NO_ERROR)
	{
		// System properties
		tinyxml2::XMLElement* eSystem = doc.FirstChildElement("system");
		if (eSystem)
		{
			// Window properties
			tinyxml2::XMLElement* eWindow = eSystem->FirstChildElement("window");
			if (eWindow)
			{
				// Window title
				tinyxml2::XMLElement* eTitle = eWindow->FirstChildElement("title");
				if (eTitle)
				{
					std::string sValue = eTitle->GetText();
					if (m_sWindowTitle != sValue)
					{
						m_sWindowTitle = sValue;
						launchEventPropertyUpdated(ConfigurationProperties::WINDOW_TITLE);
					}
				}

				// Window style
				tinyxml2::XMLElement* eWindowStyle = eWindow->FirstChildElement("window_style");
				if (eWindowStyle)
				{
					std::string sValue = eWindowStyle->GetText();
					WindowStyle style;
					if (sValue == "fullscreen")
					{
						style = WindowStyle::FULLSCREEN;
					}
					else if (sValue == "windowed_borderless")
					{
						style = WindowStyle::WINDOWED_BORDERLESS;
					}
					else
					{
						style = WindowStyle::WINDOWED;
					}

					if (style != m_windowStyle)
					{
						m_windowStyle = style;
						launchEventPropertyUpdated(ConfigurationProperties::WINDOW_STYLE);
					}
				}
				
				// Window position style
				tinyxml2::XMLElement* eWindowPosition = eWindow->FirstChildElement("window_pos_style");
				if (eWindowPosition)
				{
					std::string sValue = eWindowPosition->GetText();
					WindowPositionStyle style;
					if (sValue == "free")
					{
						style = WindowPositionStyle::FREE;
					}
					else if (sValue == "top_left")
					{
						style = WindowPositionStyle::TOP_LEFT;
					}
					else
					{
						style = WindowPositionStyle::CENTRE;
					}

					if (style != m_windowPositionStyle)
					{
						m_windowPositionStyle = style;
						launchEventPropertyUpdated(ConfigurationProperties::WINDOW_POS);
					}
				}

				// Window width
				tinyxml2::XMLElement* eWidth = eWindow->FirstChildElement("width");
				if (eWidth)
				{	
					unsigned int uiWidth = 1200;
					try
					{
						uiWidth = (unsigned int)std::stoi(eWidth->GetText());
					}
					catch (...)
					{
						uiWidth = 1200;
					}
				
					if (uiWidth != m_uiWindowWidth)
					{
						m_uiWindowWidth = uiWidth;
						launchEventPropertyUpdated(ConfigurationProperties::WINDOW_WIDTH);
					}
				}

				// Window height
				tinyxml2::XMLElement* eHeight = eWindow->FirstChildElement("height");
				if (eHeight)
				{
					unsigned int uiHeight = 1200;
					try
					{
						uiHeight = (unsigned int)std::stoi(eHeight->GetText());
					}
					catch (...)
					{
						uiHeight = 1200;
					}

					if (uiHeight != m_uiWindowHeight)
					{
						m_uiWindowHeight = uiHeight;
						launchEventPropertyUpdated(ConfigurationProperties::WINDOW_HEIGHT);
					}
				}
			}

			// Service properties
			tinyxml2::XMLElement* eServices = eSystem->FirstChildElement("services");
			if (eServices)
			{
				// Logger
				tinyxml2::XMLElement* eLogger = eServices->FirstChildElement("logger");
				if (eLogger)
				{
					std::string sValue = eLogger->GetText();
					bool b = false;
					if (sValue == "enabled")
					{
						b = true;
					}

					if (b != m_bLoggerServiceEnabled)
					{
						m_bLoggerServiceEnabled = b;
						launchEventPropertyUpdated(ConfigurationProperties::LOGGER_ENABLED);
					}
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

bool ConfigurationManager::getLoggerServiceEnabled() const
{
	return m_bLoggerServiceEnabled;
}

std::string ConfigurationManager::getWindowTitle() const
{
	return m_sWindowTitle;
}

WindowStyle ConfigurationManager::getWindowStyle() const
{
	return m_windowStyle;
}

WindowPositionStyle ConfigurationManager::getWindowPositionStyle() const
{
	return m_windowPositionStyle;
}

unsigned int ConfigurationManager::getWindowWidth() const
{
	return m_uiWindowWidth;
}

unsigned int ConfigurationManager::getWindowHeight() const
{
	return m_uiWindowHeight;
}

unsigned int ConfigurationManager::getLogicRate() const
{
	return m_uiLogicRate;
}
/**
The configuration manager is responsible for loading the engine configuration from the
"engine_properties.xml" file.

This manager has the following functionality:
- Properties may be accessed from anywhere
- Properties can be loaded and reloaded at any time with the loadProperties function
- The name of the properties file is fixed
- Classes may subscribe to the configuration manager to receive notification of properties
  changing

IMPORTANT: The configuration manager only represents the DESIRED configuration, not the active 
configuration. Of course, once the configuration has been loaded and distributed, settings may
be changed by the program or the user to best accommodate the runtime environment. Take the
window style for example. The configuration may launch in windowed, but the user may switch to
fullscreen.

@author Nathan */

#ifndef CONFIGURATION_MANAGER_H
#define CONFIGURATION_MANAGER_H

#include "System/Framework/ConfigurationListener.h"
#include "System/Framework/ConfigurationProperties.h"
#include "System/Modules/WindowStyle.h"
#include "System/Modules/WindowPositionStyle.h"
#include "System/Utility/VectorSim.h"

#include <string>
#include <tinyxml2.h>

class ConfigurationManager
{
	private:
		static ConfigurationManager* m_instance;
		static bool m_bInstanceExists;

		const std::string m_sFileName;
		VectorSim<ConfigurationListener*> m_configListeners;

		//=========================================================
		// Properties
		bool m_bLoggerServiceEnabled;

		unsigned int m_uiLogicRate;

		std::string m_sWindowTitle;
		WindowStyle m_windowStyle;
		WindowPositionStyle m_windowPositionStyle;
		unsigned int m_uiWindowWidth;
		unsigned int m_uiWindowHeight;

		//=========================================================

		/**
		Constructs a default ConfigurationManager. */
		ConfigurationManager();

		/**
		Destructs the ConfigurationManager. */
		~ConfigurationManager();

		/**
		Launches a property updated event to all registered configuration listeners that details
		the property that was updated. 
		@param prop The Id of the property that was updated */
		void launchEventPropertyUpdated(ConfigurationProperties prop);

	protected:

	public:
		/**
		Returns a raw pointer to the ConfigurationManager instance. If the instance did not exist, it is
		first instantiated. 
		@return The ConfigurationManager instance */
		static ConfigurationManager* getInstance();

		/**
		Adds a configuration listener to the configuration manager.
		@param l The configuration listener to add */
		void addConfigListener(ConfigurationListener* l);

		/**
		Removes a configuration listener from the configuration manager.
		@param l The configuration listener to remove */
		void removeConfigListener(ConfigurationListener* l);

		/**
		Loads or reloads the configuration from the configuration file. If the file was missing
		or otherwise innaccessible, this function will fail. A property update event will be 
		launched each time a property changes its value. 
		@return True if the configuration was successfully loaded */
		bool loadConfig();

		/**
		Returns true if the logger service is enabled.
		@return True if the logger service is enabled */
		bool getLoggerServiceEnabled() const;
			
		/**
		Returns the window title
		@return The window title */
		std::string getWindowTitle() const;
			
		/**
		Returns the window style
		@return The window style */
		WindowStyle getWindowStyle() const;
			
		/**
		Returns the window position style
		@return The window position style */
		WindowPositionStyle getWindowPositionStyle() const;
			
		/**
		Returns the window width
		@return The window width */
		unsigned int getWindowWidth() const;
			
		/**
		Returns the window height
		@return The window height */
		unsigned int getWindowHeight() const;
			
		/**
		Returns the logic rate
		@return The logic rate */
		unsigned int getLogicRate() const;
};

#endif
/**
A listing of all the settings that can be loaded in to the configuration manager. 

Each time a new setting is added, a matching enum value should be added to this file
so that the configuration manager can correctly notify configuration listeners. 

@author Nathan */

#ifndef CONFIGURATION_PROPERTIES_H
#define CONFIGURATION_PROPERTIES_H

enum ConfigurationProperties
{
	LOGIC_RATE,

	LOGGER_ENABLED,

	WINDOW_TITLE,
	WINDOW_STYLE,
	WINDOW_POS,
	WINDOW_WIDTH,
	WINDOW_HEIGHT
};

#endif
/**
An interface that allows classes to register with the configuration manager to receive notification
of updates to the engine configuration.

@author Nathan */

#ifndef CONFIGURATION_LISTENER_H
#define CONFIGURATION_LISTENER_H

#include "System/Framework/ConfigurationProperties.h"

class ConfigurationListener
{
	private:
	protected:
	public:
		/**
		Called by the ConfigurationManager when a property is updated. 
		@param prop The property that was modified */
		virtual void onPropertyUpdated(ConfigurationProperties prop) = 0;
};

#endif
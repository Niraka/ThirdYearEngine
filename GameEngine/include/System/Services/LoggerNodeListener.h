/**
Provides the necessary functionality for allowing a class to register with a LoggerNode
to receive notifications of its events. 

@author Nathan */

#ifndef LOGGER_NODE_LISTENER_H
#define LOGGER_NODE_LISTENER_H

#include <string>

class LoggerNodeListener
{
	private:

	protected:

	public:
		/**
		Called by a LoggerNode when a message is logged.
		@param sMsg The message */
		virtual void onMessageLogged(std::string sMsg) = 0;
};

#endif
/**
A LoggerNode is produced by the LoggerService as a means of sending pre-formatted messages from
any Module or Service back to the logger.

@author Nathan */

#ifndef LOGGER_NODE_H
#define LOGGER_NODE_H

#include "System/Services/LoggerNodeListener.h"

class LoggerNode
{	
	// Allow the LoggerService to inject itself as the listener
	friend class LoggerService;

	private:
		std::string m_sPrefix;
		LoggerNodeListener* m_listener;

		/**
		Constructs a default LoggerNode. */
		LoggerNode();

	protected:

	public:
		/**
		Constructs a LoggerNode.
		@param sPrefix The prefix to use on this node */
		LoggerNode(std::string sPrefix);

		/**
		Destructs a LoggerNode. */
		~LoggerNode();

		/**
		Logs a message to the LoggerService. The prefix of the node is automatically prepended to
		the message before it is sent to the LoggerService.*/
		void log(std::string sMessage);
};

#endif
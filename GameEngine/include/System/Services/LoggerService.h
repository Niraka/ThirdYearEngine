/**
The LoggerService is responsible for receiving and fowarding log messages to a specified output location.

The supported output locations are a given output stream and a log file. By default, the output stream
points to std::cout;

@author Nathan */

#ifndef LOGGER_SERVICE_H
#define LOGGER_SERVICE_H

#include <queue>
#include <memory>
#include <mutex>
#include <iostream>
#include <fstream>
#include <time.h>

#include "System/Framework/Service.h"
#include "System/Services/LoggerNode.h"
#include "System/Services/LoggerNodeListener.h"

class LoggerService :
	public Service,
	public LoggerNodeListener
{
	private:
		std::string m_sDefaultLogFile;
		std::ofstream m_ofStream;
		std::mutex m_mutex;
		std::queue<std::string> m_messages;
		bool m_bFileOutputEnabled;
		bool m_bConsoleOutputEnabled;

		/**
		Constructs a default LoggerService. */
		LoggerService();

	protected:
		/**
		Called by the service when the service is starting. Note that the service is valid at the time of
		calling.
		@return True if the service started up successfully */
		bool onStart();

		/**
		Called by the service when the service is stopping. Note that the service is still valid at the time
		of calling.
		@return True if the service stopped successfully */
		bool onStop();

		/**
		Called periodically by the service. */
		void onUpdate();

	public:
		/**
		Constructs a LoggerService. 
		@param uiInterval The update interval, in milliseconds */
		LoggerService(unsigned int uiInterval);

		/**
		Destructs a LoggerService. */
		~LoggerService();

		/**
		Creates and returns a LoggerNode with the given prefix. 
		@param sPrefix The deiresed prefix of the node
		@return A shared pointer to a LoggerNode */
		std::shared_ptr<LoggerNode> createLoggerNode(std::string sPrefix);

		/**
		Forces the LoggerService to instantly post its output. */
		void forceOutput();

		/**
		Enables or disables the file output of the logger service. Enabled by default. 
		@param bEnabled True to enable */
		void setFileOutputEnabled(bool bEnabled);

		/**
		Enables or disables the console output of the logger service. Enabled by default.
		@param bEnabled True to enable */
		void setConsoleOutputEnabled(bool bEnabled);
			
		/**
		Called by a LoggerNode when a message is logged. This function is thread-safe. 
		@param sMsg The message */
		void onMessageLogged(std::string sMsg);
};

#endif
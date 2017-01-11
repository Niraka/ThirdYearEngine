/**
The CommandModule will listen for commands coming in from the given input stream. By
default, this is the console.

@author Nathan */

#ifndef COMMAND_MODULE_H
#define COMMAND_MODULE_H

#include <set>
#include <map>
#include <thread>
#include <queue>
#include <memory>
#include <mutex>
#include <iostream>

#include "System/Framework/Module.h"
#include "System/Utility/StringUtils.h"
#include "System/Modules/CommandNodeInfo.h"
#include "System/Modules/CommandNodeListener.h"
#include "System/Services/LoggerService.h"

class CommandModule :
	public Module,
	public CommandNodeListener,
	public CommandListener,
	public std::enable_shared_from_this<CommandModule>
{
	private:
		std::shared_ptr<CommandModule> m_self;
		std::shared_ptr<CommandNode> m_commandNode;
		std::istream* m_inputStream;
		StringUtils m_stringUtils;
		std::map<unsigned int, CommandNodeInfo> m_commandNodes;
		unsigned int m_uiNextId;
		std::mutex m_mutex;
		std::queue<std::string> m_pendingCommands;
		std::shared_ptr<LoggerNode> m_loggerNode;
		bool m_bRunning;

		/**
		Interprets the given command and forwards it to any registered CommandNodes who are
		interested in the command.
		@param s The command to interpret */
		void interpretCommand(std::string& s);

		/**
		Starts and executes the input monitoring thread. */
		void run();

	protected:
		/**
		Updates the CommandModule. */
		void onUpdate();

	public:
		/**
		Constructs a default CommandModule. */
		CommandModule();

		/**
		Destructs a CommandModule. */
		~CommandModule();

		/**
		Creates and returns a CommandNode. 
		@return A shared pointer to a CommandNode */
		std::shared_ptr<CommandNode> createCommandNode();

		/**
		Starts up the module.
		@return True if the module started up successfully, false otherwise */
		bool start();

		/**
		Stops the module.
		@return True if the module stopped successfully, false otherwise */
		bool stop();

		/**
		Sets the input stream. Defaults to std::cin. 
		@param stream A pointer to the input stream */
		void setInputStream(std::istream* stream);

		/**
		Called by a CommandNode when the node is destroyed. 
		@param uiId The id of the node that was destroyed */
		void onNodeDestruction(unsigned int uiId);

		/**
		Called by a CommandNode when the node adds a new command. 
		@param uiId The id of the node that added the command
		@param sCommandName The name of the new command
		@param uiNumParams The number of parameters the new command takes */
		void onCommandAdded(unsigned int uiId, std::string sCommandName, unsigned int uiNumParams);

		/**
		Called by a CommandNode when the node removes one of its command.
		@param uiId The id of the node that removed the command 
		@param sCommandName The name of the command that was removed 
		@param uiNumParams The number of parameters the command used */
		void onCommandRemoved(unsigned int uiId, std::string sCommandName, unsigned int uiNumParams);

		/**
		Called by the CommandModule when a command associated with the CommandNode this class is listening
		to is executed.
		@param sCommandName The name of the command
		@param args A vector of strings containing the command arguments */
		void onCommandReceived(std::string sCommandName, std::vector<std::string> args);

		/**
		This function is called when a service becomes available that is a dependency of this class. Note that
		the pointer is delivered as a void pointer and must first be cast to the correct service using a static
		pointer cast.
		@param serviceName The name of the service
		@param service A shared pointer to the new service */
		void serviceDependencyBecameAvailable(Services serviceName, std::shared_ptr<void> service);

		/**
		This function is called when a service that is a dependency of this class becomes unavailable.
		@param serviceName The name of the service */
		void serviceDependencyBecameUnavailable(Services serviceName);
};

#endif
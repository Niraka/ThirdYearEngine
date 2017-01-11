/**
A CommandNode can be used via componentism to attach commands to a class. These commands may then be executed
by the user by either typing

Notes:
- If the CommandModule is lost for any reason, the Node must be reacquired to continue
functioning

@author Nathan */

#ifndef COMMAND_NODE_H
#define COMMAND_NODE_H

#include <string>

#include "System/Utility/VectorSim.h"
#include "System/Modules/CommandListener.h"
#include "System/Modules/CommandNodeListener.h"

class CommandNode
{
	/**
	The CommandModule controls the construction of CommandNodes so that it may attach itself as a 
	CommandListener before the node is used. */
	friend class CommandModule;

	private:
		CommandNodeListener* m_commandNodeListener;
		VectorSim<CommandListener*> m_commandListeners;
		unsigned int m_uiId;

	protected:

	public:		
		/**
		Constructs a default CommandNode. */
		CommandNode();

		/**
		Destructs a CommandNode. */
		~CommandNode();

		/**
		Adds a command listener to the node.
		@param l The listener to add */
		void addCommandListener(CommandListener* l);

		/**
		Removes a command listener from the node. 
		@param l The listener to remove */
		void removeCommandListener(CommandListener* l);

		/**
		Adds a new command to the node.
		@param sCommandName The name of the command 
		@param uiNumParams The number of parameters the command takes */
		void addCommand(std::string sCommandName, unsigned int uiNumParams);

		/**
		Removes a command from the node. 
		@param sCommandName The name of the command
		@param uiNumParams The number of parameters the command takes */
		void removeCommand(std::string sCommandName, unsigned int uiNumParams);

		/**
		Called by the CommandModule when a command registered on this CommandNode is executed.
		@param sCommandName The name of the command
		@param args A vector of strings containing the arguments for the command */
		void receiveCommand(std::string sCommandName, std::vector<std::string> args);
};

#endif
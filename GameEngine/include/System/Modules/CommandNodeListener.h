/**
Defines the necessary functions for listening to events occurring on a CommandNode.

@author Nathan */

#ifndef COMMAND_NODE_LISTENER_H
#define COMMAND_NODE_LISTENER_H

#include <string>

class CommandNodeListener
{
	private:

	protected:

	public:
		/**
		Called by a CommandNode when the node is destroyed.
		@param uiId The id of the node that was destroyed */
		virtual void onNodeDestruction(unsigned int uiId) = 0;
		
		/**
		Called by a CommandNode when the node adds a new command.
		@param uiId The id of the node that added the command
		@param sCommandName The name of the new command
		@param uiNumParams The number of parameters the new command takes */
		virtual void onCommandAdded(unsigned int uiId, std::string sCommandName, unsigned int uiNumParams) = 0;
		
		/**
		Called by a CommandNode when the node removes one of its command.
		@param uiId The id of the node that removed the command
		@param sCommandName The name of the command that was removed
		@param uiNumParams The number of parameters the command used */
		virtual void onCommandRemoved(unsigned int uiId, std::string sCommandName, unsigned int uiNumParams) = 0;
};

#endif
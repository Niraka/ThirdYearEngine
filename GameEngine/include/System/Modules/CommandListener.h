/**
An interface class that provides the necessary functionality for listening to command events
occurring on the CommandModule.

@author Nathan*/

#ifndef COMMAND_LISTENER_H
#define COMMAND_LISTENER_H

#include <string>
#include <vector>

class CommandListener
{
	private:

	protected:

	public:
		/**
		Called by the CommandModule when a command associated with the CommandNode this class is listening
		to is executed.
		@param sCommandName The name of the command
		@param args A vector of strings containing the command arguments */
		virtual void onCommandReceived(std::string sCommandName, std::vector<std::string> args) = 0;
};

#endif
/**
The ScriptingModule is responsible for all Scripting functionality.

@author Nathan */

#ifndef SCRIPTING_MODULE_H
#define SCRIPTING_MODULE_H

#include "System/Framework/Module.h"
#include "System/Services/LoggerNode.h"
#include "Game/Modules/ScriptLoader.h"
#include "Game/Modules/ScriptInfoPack.h"
#include "Game/Modules/FunctionRegister.h"
#include "Game/Modules/ScriptTimerRegistrar.h"
#include "Game/Modules/ScriptActionTerminal.h"
#include "Game/Modules/ScriptingNumberGenerator.h"
#include "System/Modules/EventModule.h"
#include "System/Modules/TimerListener.h"
#include "System/Modules/AudioModule.h"

#include <string>
#include <queue>
#include <map>

class ScriptingModule :
	public Module,
	public ScriptTimerRegistrar,
	public ScriptActionTerminal,
	public CommandListener,
	public EventListener
{
	private:
		const std::string m_sCommandExecuteScript;
		const std::string m_sCommandLoadScript;
		const std::string m_sCommandUnloadScript;
		const std::string m_sInitScriptName;
		const std::string m_sInitScriptFileName;
		std::set<std::string> m_variableDefintionSymbols;
		std::map<std::string, ScriptVar> m_variables;

		unsigned int m_uiEngineLaunchedEvent;

		std::shared_ptr<EventModule> m_eventModule;
		std::shared_ptr<CommandNode> m_commandNode;
		FunctionRegister m_functionRegister;
		ScriptLoader m_scriptLoader;                                    // For loading scripts
		std::map<std::string, Script> m_scripts;                        // All scripts
		std::shared_ptr<LoggerNode> m_loggerNode;                       // For logging to the console
		ScriptInfoPack m_infoPack;                                      // Given to scripts to execute functions in other modules
		std::queue<Script*> m_scriptQueue;                              // Scripts to execute
		ScriptingNumberGenerator m_numberGenerator;

	protected:
		/**
		Updates the ScriptingModule. */
		void onUpdate();

	public:
		/**
		Constructs a ScriptingModule. */
		ScriptingModule();

		/**
		Destructs the ScriptingModule. */
		~ScriptingModule();

		/**
		Starts up the ScriptingModule.
		@return True if the module started up successfully, false otherwise */
		bool start();

		/**
		Stops the ScriptingModule.
		@return True if the module stopped successfully, false otherwise */
		bool stop();

		/**
		Adds a timer.
		@param sTimerName The name of the timer
		@param sScriptName The name of the script to execute on expirey */
		void addTimer(const std::string& sTimerName, const std::string& sScriptName);

		/**
		Called by the TimingModule when a Timer expires.
		@param sTimer The name of the Timer that expired */
		void onTimerExpired(std::string sTimer);

		/**
		Loads a Script from the given file and binds it to the given name. The name must be unique amongst all
		other Scripts currently in memory. Note that the file name should not include the parent directory as 
		this is automatically prepended. For example, ".\\data\\scripts\\myScript.txt" should begiven as 
		"myScript.txt". 
		@param sScriptName The name to bind the Script to 
		@param sFileName The name of the file to load from 
		@return True if the Script was successfully loaded, false otherwise */
		bool loadScript(const std::string& sScriptName, const std::string& sFileName);

		/**
		Unloads a Script with the given name.
		@param sScriptName The name of the Script to unload */
		void unloadScript(const std::string& sScriptName);

		/**
		Executes a Script with the given name.
		@param sScriptName The name of the Script to execute */
		void executeScript(const std::string& sScriptName);

		/**
		Gets a Script with the given name. The value must be transferred as a void pointer to avoid
		circular inclusion.
		@param sScriptName The name of the Script to get */
		void* getScript(const std::string& sScriptName);

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

		/**
		This function is called when a module becomes available that is a dependency of this class. Note that
		the pointer is delivered as a void pointer and must first be cast to the correct module using a
		static pointer cast.
		@param moduleName The name of the module
		@param module A shared pointer to the new module */
		void moduleDependencyBecameAvailable(Modules moduleName, std::shared_ptr<void> module);

		/**
		This function is called when a module that is a dependency of this class becomes unavailable.
		@param moduleName The name of the module */
		void moduleDependencyBecameUnavailable(Modules moduleName);

		/**
		Called by the CommandModule when a command associated with the CommandNode this class is listening
		to is executed.
		@param sCommandName The name of the command
		@param args A vector of strings containing the command arguments */
		void onCommandReceived(std::string sCommandName, std::vector<std::string> args);

		/**
		Called by the EventModule when an event is launched.
		@param uiEventId A constant reference to the id of the event*/
		void onEvent(const unsigned int& uiEventId);

		/**
		Called by the EventModule when an event that this listener is listening for becomes available.
		@param sEventName The name of the event
		@param uiEventId The id of the event */
		void onEventRegistered(const std::string& sEventName, const unsigned int& uiEventId);
};

#endif
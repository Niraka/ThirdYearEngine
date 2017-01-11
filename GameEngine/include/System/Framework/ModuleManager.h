/**
The ModuleManager is responsible for starting, storing, stopping and delivering updates to modules.

@author Nathan */

#ifndef MODULE_MANAGER_H
#define MODULE_MANAGER_H

#include "System/Modules/WindowModule.h"
#include "System/Modules/CommandModule.h"
#include "System/Modules/TimingModule.h"
#include "System/Modules/ResourceModule.h"
#include "System/Modules/EventModule.h"
#include "Scene/Modules/EntityModule.h"
#include "Scene/Modules/ActingModule.h"
#include "Scene/Modules/PhysicsModule.h"
#include "System/Modules/AudioModule.h"
#include "Scene/Modules/GUIModule.h"
#include "Game/Modules/ScriptingModule.h"
#include "Game/Modules/EditorModule.h"
#include "System/Framework/Modules.h"
#include "System/Framework/ModuleLifetimeListener.h"
#include "System/Framework/ServiceLifetimeListener.h"

#include <map>
#include <string>
#include <memory>

class ModuleManager :
	public ServiceLifetimeListener,
	public CommandListener
{
	private:
		std::map<Modules, std::shared_ptr<Module>> m_modules;
		ModuleLifetimeListener* m_moduleLifetimeListener;
		std::shared_ptr<CommandNode> m_commandNode;

		/**
		Called when a new module starts up.
		@param moduleName The name of the module
		@param module A shared pointer to the module */
		void onModuleStarted(Modules moduleName, std::shared_ptr<Module> module);

		/**
		Called when a module shuts down.
		@param moduleName The name of the module */
		void onModuleStopped(Modules moduleName);

	protected:

	public:
		/**
		Constructs a default ModuleManager. */
		ModuleManager();

		/**
		Destructs the ModuleManager. */
		~ModuleManager();

		/**
		Returns a shared pointer to the events module. 
		@return A shared pointer to the events module */
		std::shared_ptr<EventModule> getEventModule();

		/**
		Starts a Module. If the module already existed, it is stopped and restarted.
		@param module The Id of the module to start */
		bool startModule(Modules module);

		/**
		Stops a Module and cleans up any resources that it was using.
		@param module The Id of the module to stop */
		bool stopModule(Modules module);

		/**
		Returns a string representation of a module. Returns an empty string if no such module existed.
		@param module The module to convert
		@return The module as a string, or an empty string */
		std::string moduleAsString(Modules module);

		/**
		Updates the ModuleManager and all Modules stored within it. */
		void update();

		/**
		Binds a ModuleLifetimeListener to this ModuleManager. Note that only one lifetime listener may
		be bound at any one time.
		@param l The lifetime listener to bind */
		void bindModuleLifetimeListener(ModuleLifetimeListener* l);

		/**
		Called by the ServiceManager when a new service starts up.
		@param serviceName The name of the service
		@param service A shared pointer to the service */
		void onServiceStarted(Services serviceName, std::shared_ptr<Service> service);

		/**
		Called by the ServiceManager when a service shuts down.
		@param serviceName The name of the service */
		void onServiceStopped(Services serviceName);

		/**
		Called by the CommandModule when a command associated with the CommandNode this class is listening
		to is executed.
		@param sCommandName The name of the command
		@param args A vector of strings containing the command arguments */
		void onCommandReceived(std::string sCommandName, std::vector<std::string> args);
};

#endif
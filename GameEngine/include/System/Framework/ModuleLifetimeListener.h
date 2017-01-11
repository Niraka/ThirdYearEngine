/**
A module lifetime listener allows a class to register itself with the module manager to receive 
notifications of when modules are started and stopped.

@author Nathan */

#ifndef MODULE_LIFETIME_LISTENER_H
#define MODULE_LIFETIME_LISTENER_H

#include <memory>
#include "System/Framework/Modules.h"
#include "System/Framework/Module.h"

class ModuleLifetimeListener
{
	private:

	protected:

	public:
		/**
		Called by the ModuleManager when a new module starts up. 
		@param moduleName The name of the module
		@param module A shared pointer to the module */
		virtual void onModuleStarted(Modules moduleName, std::shared_ptr<Module> module) = 0;

		/**
		Called by the ModuleManager when a module shuts down.
		@param moduleName The name of the module */
		virtual void onModuleStopped(Modules moduleName) = 0;
};

#endif
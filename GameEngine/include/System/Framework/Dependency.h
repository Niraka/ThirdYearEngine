/**
A dependency allows a class to attach a list of dependencies to itself. This list is then read each time
a new module or service becomes available and is used to notify the class of the new module or service.

@author Nathan */

#ifndef DEPENDENCY_H
#define DEPENDENCY_H

#include <vector>
#include <memory>
#include "System/Framework/Modules.h"
#include "System/Framework/Services.h"

class Dependency
{
	private:
		std::vector<Modules> m_moduleDependencies;
		std::vector<Services> m_serviceDependencies;

	protected:
		/**
		Adds a dependency to this module. When the given module becomes available, it will be presented to this module
		for processing. Note that dependencies cannot be removed as this does not make any sense. Furthermore, a module
		should not be a dependency of itself.
		@param moduleName The name of the module to add as a dependency */
		void addModuleDependency(Modules moduleName);

		/**
		Adds a dependency to this module. When the given service becomes available, it will be presented to this module
		for processing. Note that dependencies cannot be removed as this does not make any sense. Furthermore, a module
		should not be a dependency of itself.
		@param serviceName The name of the module to add as a dependency */
		void addServiceDependency(Services serviceName);

	public:
		/**
		Checks if the given module is a dependency of this one.
		@param moduleName The name of the module to check
		@return True if the given module is a dependency of this one */
		bool hasModuleDependency(Modules moduleName);

		/**
		Checks if the given service is a dependency of this module.
		@param serviceName The name of the service to check
		@return True if the given service is a dependency of this module */
		bool hasServiceDependency(Services serviceName);

		/**
		This function is called when a module becomes available that is a dependency of this class. Note that
		the pointer is delivered as a void pointer and must first be cast to the correct module using a 
		static pointer cast.
		@param moduleName The name of the module 
		@param module A shared pointer to the new module */
		virtual void moduleDependencyBecameAvailable(Modules moduleName, std::shared_ptr<void> module);

		/**
		This function is called when a service becomes available that is a dependency of this class. Note that
		the pointer is delivered as a void pointer and must first be cast to the correct service using a static
		pointer cast. 
		@param serviceName The name of the service
		@param service A shared pointer to the new service */
		virtual void serviceDependencyBecameAvailable(Services serviceName, std::shared_ptr<void> service);

		/**
		This function is called when a module that is a dependency of this class becomes unavailable.
		@param moduleName The name of the module */
		virtual void moduleDependencyBecameUnavailable(Modules moduleName);

		/**
		This function is called when a service that is a dependency of this class becomes unavailable.
		@param serviceName The name of the service */
		virtual void serviceDependencyBecameUnavailable(Services serviceName);
};

#endif
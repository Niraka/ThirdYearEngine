/**
The service manager is responsible for starting, storing and stopping services. 

@author Nathan */

#ifndef SERVICE_MANAGER_H
#define SERVICE_MANAGER_H

#include "System/Framework/Service.h"
#include "System/Framework/Services.h"
#include "System/Framework/ModuleLifetimeListener.h"
#include "System/Framework/ServiceLifetimeListener.h"

#include "System/Services/FileSystemWatcherService.h"
#include "System/Services/LoggerService.h"
#include "System/Services/ModuleWatcherService.h"
#include "System/Services/ResourceCleanerService.h"
#include "System/Services/ResourceUsageTrackerService.h"

#include <map>
#include <vector>
#include <string>
#include <memory>

class ServiceManager :
	public ModuleLifetimeListener
{
	private:
		std::map<Services, std::shared_ptr<Service>> m_services;
		ServiceLifetimeListener* m_serviceLifetimeListener;

		/**
		Called by the ServiceManager when a new service starts up.
		@param serviceName The name of the service
		@param service A shared pointer to the service */
		void onServiceStarted(Services serviceName, std::shared_ptr<Service> service);

		/**
		Called by the ServiceManager when a service shuts down.
		@param serviceName The name of the service */
		void onServiceStopped(Services serviceName);

	protected:

	public:
		/**
		Constructs a default ServiceManager. */
		ServiceManager();

		/**
		Destructs the ServiceManager. */
		~ServiceManager();

		/**
		Starts a service with the given name. If the service is already running, it is first
		stopped before being restarted. 
		@param service The name of the service */
		bool startService(Services service);

		/**
		Stops a service. If the service was already stopped, this function does nothing.
		@param service The name of the service */
		bool stopService(Services service); 

		/**
		Returns a string representation of a service. Returns an empty string if no such service
		existed.
		@param service The service to convert
		@return The service as a string, or an empty string */
		std::string serviceAsString(Services service);

		/**
		Binds a ServiceLifetimeListener to this ServiceManager. Note that only one lifetime listener
		may be bound at any one time. 
		@param l The lifetime listener to bind */
		void bindServiceLifetimeListener(ServiceLifetimeListener* l);

		/**
		Called by the ModuleManager when a new module starts up.
		@param moduleName The name of the module
		@param module A shared pointer to the module */
		void onModuleStarted(Modules moduleName, std::shared_ptr<Module> module);

		/**
		Called by the ModuleManager when a module shuts down.
		@param moduleName The name of the module */
		void onModuleStopped(Modules moduleName);
};

#endif
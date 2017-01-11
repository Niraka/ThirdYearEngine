/**
A service lifetime listener allows a class to register itself with the service manager to receive
notification of when services are started and stopped.

@author Nathan */

#ifndef SERVICE_LIFETIME_LISTENER_H
#define SERVICE_LIFETIME_LISTENER_H

#include <memory>
#include "System/Framework/Services.h"
#include "System/Framework/Service.h"

class ServiceLifetimeListener
{
	private:

	protected:

	public:
		/**
		Called by the ServiceManager when a new service starts up.
		@param serviceName The name of the service
		@param service A shared pointer to the service */
		virtual void onServiceStarted(Services serviceName, std::shared_ptr<Service> service) = 0;
		
		/**
		Called by the ServiceManager when a service shuts down.
		@param serviceName The name of the service */
		virtual void onServiceStopped(Services serviceName) = 0;
};

#endif
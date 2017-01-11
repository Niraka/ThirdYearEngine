/**
The resource cleaner service periodically attempts to remove unused resources from the
resource modules storage. The cleaner can be tuned to target specific resource types
more aggressively than others.

@author Nathan */

#ifndef RESOURCE_CLEANER_SERVICE_H
#define RESOURCE_CLEANER_SERVICE_H

#include "System/Framework/Service.h"

class ResourceCleanerService :
	public Service
{
	private:
		/**
		Constructs a default ResourceCleanerService. */
		ResourceCleanerService();

	protected:
		/**
		Called by the service when the service is starting. Note that the service is valid at the time of
		calling.
		@return True if the service started up successfully */
		bool onStart();

		/**
		Called by the service when the service is stopping. Note that the service is still valid at the time
		of calling.
		@return True if the service stopped successfully */
		bool onStop();

		/**
		Called periodically by the service. */
		void onUpdate();

	public:
		/**
		Constructs a ResourceCleanerService.
		@param uiInterval The update interval, in milliseconds */
		ResourceCleanerService(unsigned int uiInterval);

		/**
		Destructs a ResourceCleanerService. */
		~ResourceCleanerService();
};

#endif
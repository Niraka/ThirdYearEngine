/**
The resource usage tracker service tracks the frequency that a resource is accessed over the course of the
engines runtime and produces a report upon shutdown.

The report can then be used to determine which resources are sitting idle.

@author Nathan */

#ifndef RESOURCE_USAGE_TRACKER_SERVICE_H
#define RESOURCE_USAGE_TRACKER_SERVICE_H

#include "System/Framework/Service.h"

class ResourceUsageTrackerService :
	public Service
{
	private:
		/**
		Constructs a default ResourceUsageTrackerService. */
		ResourceUsageTrackerService();

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
		Constructs a ResourceUsageTrackerService. 
		@param uiInterval The update interval, in milliseconds */
		ResourceUsageTrackerService(unsigned int uiInterval);

		/**
		Destructs a ResourceUsageTrackerService. */
		~ResourceUsageTrackerService();
};

#endif
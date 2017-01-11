/**
The ModuleWatcherService is responsible for detecting and resolving errors that would cause modules
to stop functioning correctly.

@author Nathan */

#ifndef MODULE_WATCHER_SERVICE_H
#define MODULE_WATCHER_SERVICE_H

#include "System/Framework/Service.h"

class ModuleWatcherService :
	public Service
{
	private:
		/** 
		Constructs a default ModuleWatcherService. */
		ModuleWatcherService();

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
		Constructs a ModuleWatcherService. 
		@param uiInterval The update interval, in milliseconds */
		ModuleWatcherService(unsigned int uiInterval);

		/**
		Destructs a ModuleWatcherService. */
		~ModuleWatcherService();
};

#endif
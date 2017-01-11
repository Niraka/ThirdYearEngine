#ifndef FILE_SYSTEM_WATCHER_SERVICE_H
#define FILE_SYSTEM_WATCHER_SERVICE_H

#include "System/Framework/Service.h"

class FileSystemWatcherService :
	public Service
{
	private:
		/**
		Constructs a default FileSystemWatcherService. */
		FileSystemWatcherService();

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
		Constructs a FileSystemWatcherService.
		@param uiInterval The update interval, in milliseconds */
		FileSystemWatcherService(unsigned int uiInterval);

		/**
		Destructs a FileSystemWatcherService. */
		~FileSystemWatcherService();

};

#endif
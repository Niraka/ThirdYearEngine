/**
Services are background functionality that run constantly and perform either one or very few
tasks.

For a service that uses a blocking function, the interval should be set to 0. This can be seen in
the FileSystemWatcherService.

@author Nathan */

#ifndef SERVICE_H
#define SERVICE_H

#include <thread>
#include <GLFW\glfw3.h>

#include <memory>
#include "System/Framework/Dependency.h"

class Service :
	public Dependency,
	public std::enable_shared_from_this<Service>
{
	private:
		unsigned int m_uiSleepTime;  // The time interval in milliseconds (for the sleep_for function)
		double m_fNextUpdateTime;    // The next time to run an update
		double m_fTimeInterval;      // The time between each update
		double m_fTimeNow;           // The time now
		bool m_bRunning;             // Is the service running
		std::shared_ptr<Service> m_self;

		/**
		Constructs a default Service. */
		Service();

	protected:
		/**
		Executes the service. */
		void run();

		/**
		Called by the service when the service is starting. Note that the service is valid at the time of
		calling. 
		@return True if the service started up successfully */
		virtual bool onStart() = 0;

		/**
		Called by the service when the service is stopping. Note that the service is still valid at the time
		of calling. 
		@return True if the service stopped successfully */
		virtual bool onStop() = 0;

		/**
		Called periodically by the service. */
		virtual void onUpdate() = 0;

	public:
		/**
		Constructs a Service with the desired interval.
		@param uiInterval The interval, in milliseconds, between each execution of this services instructions */
		Service(unsigned int uiInterval);

		/**
		Destructs the Service. */
		~Service();

		/**
		Starts the service. 
		@return True if the service started successfully */
		bool start();

		/**
		Stops the service. Note that a service will always stop when stop is called. The returned boolean
		indicates whether the stop operation was clean or not.
		@return True if the service stopped successfully */
		bool stop();
};

#endif
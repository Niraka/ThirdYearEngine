/**
The TimingModule handles the monitoring and event broadcasting for all Timers that are added to it. The
internal Timing system depends on the glfw timer.

@author Nathan */

#ifndef TIMING_MODULE_H
#define TIMING_MODULE_H

#include "System/Framework/Module.h"
#include "System/Modules/Timer.h"
#include "System/Modules/TimerListener.h"
#include "System/Utility/VectorSim.h"
#include "System/Services/LoggerService.h"

#include <GLFW\glfw3.h>
#include <memory>

class TimingModule :
	public Module
{
	private:
		VectorSim<TimerListener*> m_listeners;
		std::vector<std::shared_ptr<Timer>> m_timers;
		std::shared_ptr<LoggerNode> m_loggerNode;
		double m_fTimeRewind;
		double m_fTimeNow;

		/**
		Launches an event to all registered TimerListeners to notify them that a Timer has
		expired.
		@param sName The name of the timer that has expired */
		void launchExpireEvent(const std::string& sName);

	protected:
		/**
		Updates the TimingModule. */
		void onUpdate();

	public:
		/**
		Constructs a TimingModule. */
		TimingModule();

		/**
		Destructs the TimingModule. */
		~TimingModule();

		/**
		Starts up the module.
		@return True if the module started up successfully, false otherwise */
		bool start();

		/**
		Stops the module.
		@return True if the module stopped successfully, false otherwise */
		bool stop();

		/**
		Adds a Timer to the TimingModule.
		@param timer A shared pointer to a Timer */
		void addTimer(std::shared_ptr<Timer> timer);
		
		/**
		Adds a TimerListener. The listener will receive notification of events occurring on  the module until 
		it is removed. 
		@param l A pointer to the listener to add */
		void addTimerListener(TimerListener* l);
		
		/**
		Removes a TimerListener. The listener will no longer receive notification of events occurring on the 
		TimingModule.
		@param l A pointer to the listener to remove */
		void removeTimerListener(TimerListener* l);

		/**
		This function is called when a service becomes available that is a dependency of this class. Note that
		the pointer is delivered as a void pointer and must first be cast to the correct service using a static
		pointer cast.
		@param serviceName The name of the service
		@param service A shared pointer to the new service */
		void serviceDependencyBecameAvailable(Services serviceName, std::shared_ptr<void> service);

		/**
		This function is called when a service that is a dependency of this class becomes unavailable.
		@param serviceName The name of the service */
		void serviceDependencyBecameUnavailable(Services serviceName);
};

#endif
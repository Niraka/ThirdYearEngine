/**
The main class of the engine. Hosts the core components and a method to start
and stop the engine.

@author Nathan */

#ifndef ENGINE_H
#define ENGINE_H

#define GLM_FORCE_RADIANS

#include <iostream>
#include <thread>
#include <memory>
#include "System/Framework/ModuleManager.h"
#include "System/Framework/ServiceManager.h"
#include "System/Framework/ConfigurationManager.h"
#include "System/Modules/WindowListener.h"

class Engine :
	public WindowListener,
	public InputListener
{
	private:
		ModuleManager m_moduleManager;
		ServiceManager m_serviceManager;
		ConfigurationManager* m_configManager;
		std::shared_ptr<std::thread> m_thread;

		bool m_bRunningUser;                       // The running flag that the user sets
		bool m_bRunningSystem;                     // The running flag that the system sets
		bool m_bInitialised;                       // Has the engine been initialised?
									               
		const unsigned int m_uiMinLR;              // The minimum logic rate (fixed)
		const unsigned int m_uiMaxLR;              // The maximum logic rate (fixed)
		unsigned int m_uiLogicRate;                // The engine logic rate
		unsigned int m_uiSleepTime;                // The time interval in milliseconds (for the sleep_for function)
		double m_fNextUpdateTime;                  // The next time to run an update
		double m_fTimeInterval;                    // The time between each update
		double m_fTimeNow;                         // The time now
		std::chrono::milliseconds m_sleepDuration; // The sleep duration, as a chrono object

		/**
		Begins running the engine loop in another thread. */
		void run();

	protected:

	public:
		/**
		Constructs a default Engine. */
		Engine();

		/**
		Initialises the engine. This function must be called prior to calling "start" to
		perform mandatory setup and configuration of the engine.
		@return True if the engine was successfully initialised, false if there were errors */
		bool initialise();

		/**
		Starts the engine.
		@return True if the engine started successfully, false otherwise */
		bool start();

		/**
		Stops the engine and releases all of its resources. The engine must be re-initialised
		before it may be started again. */
		void stop();

		/**
		Called when the WindowModule signals that the window is closing. */
		void onWindowClose(); 

		/**
		Called when the WindowModule signals that a key has been pressed. 
		@param iKey The key code
		@param iScancode The scan code 
		@param iMods The key modifier bitmask */
		void onKeyPressed(int iKey, int iScancode, int iMods);
};

#endif
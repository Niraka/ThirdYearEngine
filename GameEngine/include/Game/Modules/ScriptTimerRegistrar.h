/**
The ScriptTimerRegistrar is a component of the ScriptingModule that allows a Script to register a timer
and a script to execute in response to it.

@author Nathan */

#ifndef SCRIPT_TIMER_REGISTRAR_H
#define SCRIPT_TIMER_REGISTRAR_H

#include "System/Modules/TimerListener.h"

#include <string>
#include <vector>

class ScriptTimerRegistrar :
	public TimerListener
{
	private:

	protected:
		std::vector<std::pair<std::string, std::string>> m_scriptTimers;

	public:
		ScriptTimerRegistrar();
		~ScriptTimerRegistrar();

		/**
		Adds a timer. 
		@param sTimerName The name of the timer
		@param sScriptName The name of the script to execute on expirey */
		virtual void addTimer(const std::string& sTimerName, const std::string& sScriptName) = 0;

		/**
		Called by the TimingModule when a Timer expires.
		@param sTimer The name of the Timer that expired */
		virtual void onTimerExpired(std::string sTimer) = 0;
};

#endif
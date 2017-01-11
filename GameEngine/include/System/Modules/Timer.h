/**
A Timer with a duration and name. Timers should be created and then added to the TimingModule. The
module will then notify all TimerListeners when the Timer expires.

@author Nathan */

#ifndef TIMER_H
#define TIMER_H

#include <string>

class Timer
{
	friend class TimingModule;

	private:
		std::string m_sName;        // The name of the timer
		double m_fDuration;         // The duration, in seconds
		double m_fExpireTime;       // The expire time, in seconds

		/**
		Constructs a Timer. */
		Timer();

	protected:
		/**
		Sets the expire time. This function should only be called by the TimingModule.
		@param fExpireTime The time, in seconds, that the Timer should expire */
		void setExpireTime(double fExpireTime);

	public:
		/**
		Constructs a Timer with the given name and default duration of 5 seconds. 
		@param sName The name of the timer */
		Timer(std::string sName);

		/**
		Constructs a Timer with the given name and duration. 
		@param sName The name of the timer
		@param fDuration The duration of the timer, in seconds */
		Timer(std::string sName, double fDuration);

		/**
		Destructs the Timer. */
		~Timer();

		/**
		Returns a constant reference to the name of the Timer. 
		@return A constant reference to the name of the Timer */
		const std::string& getName() const;

		/**
		Returns the duration of the Timer, in seconds. 
		@return The duration, in seconds */
		double getDuration() const;

		/**
		Returns the expire time of the Timer, in seconds.
		@return The expire time, in seconds */
		double getExpireTime() const;
};

#endif
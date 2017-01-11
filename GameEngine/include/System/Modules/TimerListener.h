/**
Defines the necessary functionality for a class to listen to Timer events occurring on
the TimingModule. 

@author Nathan */

#ifndef TIMER_LISTENER_H
#define TIMER_LISTENER_H

#include <string>

class TimerListener
{
	private:
	protected:
	public:
		/**
		Called by the TimingModule when a Timer expires. 
		@param sTimer The name of the Timer that expired */
		virtual void onTimerExpired(std::string sTimer) = 0;
};

#endif
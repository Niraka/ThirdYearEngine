/**
Provides the necessary functions for a class to be able to listen to and provide a response for events
occurring as part of the EventModule.

@author Nathan */

#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

#include <string>

class EventListener
{
	private:

	protected:

	public:
		/**
		Called by the EventModule when an event is launched.
		@param uiEventId A constant reference to the id of the event*/
		virtual void onEvent(const unsigned int& uiEventId) = 0;

		/**
		Called by the EventModule when an event that this listener is listening for becomes available.
		@param sEventName The name of the event
		@param uiEventId The id of the event */
		virtual void onEventRegistered(const std::string& sEventName, const unsigned int& uiEventId) = 0;
};

#endif
/**
The EventModule is responsible for distributing notifications of system-wide events.

Events specified within this module are arbitrarily defined and have no data attached. This
means that the events can and should only be used as an indication of something occurring,
rather than a means of transferring data.

For example:
Upon creating a window, the WindowModule will launch an event signalling that a window has
been created. However, the event does not contain any information about the size, position 
or contents of the window.

@author Nathan */

#ifndef EVENT_MODULE_H
#define EVENT_MODULE_H

#include "System/Framework/Module.h"
#include "System/Modules/EventListener.h"
#include "System/Services/LoggerService.h"
#include "System/Utility/VectorSim.h"

#include <string>
#include <vector>
#include <map>

class EventModule :
	public Module
{
	private:
		std::map<std::string, unsigned int> m_eventsNameKey;
		std::map<unsigned int, std::string> m_eventsIdKey;
		std::vector<std::pair<std::string, EventListener*>> m_pendingIdRequests;

		VectorSim<EventListener*> m_eventListeners;
		std::shared_ptr<LoggerNode> m_loggerNode;
		unsigned int m_uiNextNodeId;
		unsigned int m_uiNextEventId;

		void checkPendingRequests(const std::string& sEventName);

	protected:
		/**
		Updates the EventsModule. */
		void onUpdate();

	public:
		/**
		Constructs an EventsModule. */
		EventModule();

		/**
		Destructs the EventsModule. */
		~EventModule();

		/**
		Starts up the EventsModule.
		@return True if the module started up successfully, false otherwise */
		bool start();

		/**
		Stops the EventsModule.
		@return True if the module stopped successfully, false otherwise */
		bool stop();

		/**
		Registers a new event under the given name. The name must be unique across all other events.
		@param sEventName The name of the event to register
		@return The id of the event, or 0 if the registration failed */
		unsigned int registerEvent(std::string sEventName);

		/**
		Deregisters an event with the given id.
		@param uiEventId The id of the event to deregister
		@return True if an event was deregistered, false otherwise */
		bool deregisterEvent(const unsigned int& uiEventId);

		/**
		Launches the event associated with the given id. If the id did not correspond to a valid event, 
		no action is taken.
		@param uiEventId The id of the event to launch */
		void launchEvent(const unsigned int& uiEventId);
		
		/**
		Adds an EventListener. 
		@param l The listener to add*/
		void addListener(EventListener* l);

		/**
		Removes an EventListener.
		@param l The listener to remove
		@return True if a listener was removed, false otherwise */
		bool removeListener(EventListener* l);

		/**
		Retrieves the id of an event with the given name. If the event was not currently registered and an
		appropriate EventListener was provided, a record of the request will be stored. Once the desired
		event becomes available, the given EventListener will be notified with the id the new event was
		allocated. If no EventListener is given, no record is stored. 
		@param sEventName A constant reference to the name of the event to query
		@param l (Optional) A pointer to an EventListener. Defaults to a nullptr. 
		@return The id of the event, or 0 if the event did not exist */
		unsigned int getEventId(const std::string& sEventName, EventListener* l = nullptr);

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
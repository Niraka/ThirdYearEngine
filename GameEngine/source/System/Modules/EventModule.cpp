#include "System/Modules/EventModule.h"

EventModule::EventModule()
{
	m_uiNextEventId = 1;
	m_uiNextNodeId = 1;

	addServiceDependency(Services::LOGGER);
}

EventModule::~EventModule()
{
}

void EventModule::onUpdate()
{

}

bool EventModule::start()
{
	if (m_loggerNode)
	{
		m_loggerNode->log("Event module launching");
	}

	if (m_loggerNode)
	{
		m_loggerNode->log("Event module successfully launched");
	}
	return true;
}

bool EventModule::stop()
{
	return true;
}


void EventModule::checkPendingRequests(const std::string& sEventName)
{
	unsigned int uiCrnt = 0;
	unsigned int uiRemovals = 0;
	unsigned int uiSize = m_pendingIdRequests.size();
	for (; uiCrnt < (uiSize - uiRemovals); ++uiCrnt)
	{
		std::string sTempName = m_pendingIdRequests.at(uiCrnt).first;
		if (sTempName == sEventName)
		{
			m_pendingIdRequests.at(uiCrnt).second->onEventRegistered(sTempName, m_eventsNameKey.at(sTempName));
			m_pendingIdRequests.erase(m_pendingIdRequests.begin() + uiCrnt);
			uiRemovals++;
			uiCrnt--;
		}
	}	
}

unsigned int EventModule::registerEvent(std::string sEventName)
{
	// If the event name was useless, reject the request
	if (sEventName == "")
	{
		return 0;
	}

	// Check the name was unique
	if (m_eventsNameKey.find(sEventName) == m_eventsNameKey.end())
	{
		m_eventsNameKey.emplace(sEventName, m_uiNextEventId);
		m_eventsIdKey.emplace(m_uiNextEventId, sEventName);
		m_uiNextEventId++;

		checkPendingRequests(sEventName);

		return m_uiNextEventId - 1;
	}
	else
	{
		return 0;
	}
}

bool EventModule::deregisterEvent(const unsigned int& uiEventId)
{
	if (uiEventId == 0)
	{
		return false;
	}

	if (m_eventsIdKey.find(uiEventId) != m_eventsIdKey.end())
	{
		std::string sEventName = m_eventsIdKey.at(uiEventId);
		m_eventsNameKey.erase(sEventName);
		m_eventsIdKey.erase(uiEventId);
		return true;
	}
	else
	{

		return false;
	}
}

void EventModule::launchEvent(const unsigned int& uiEventId)
{
	if (uiEventId == 0)
	{
		return;
	}

	// The event must be a valid event
	if (m_eventsIdKey.find(uiEventId) == m_eventsIdKey.end())
	{
		return;
	}

	// Launch the event to all listeners
	unsigned int uiCrnt = 0;
	unsigned int uiSize = m_eventListeners.size();
	for (; uiCrnt < uiSize; ++uiCrnt)
	{
		m_eventListeners.at(uiCrnt)->onEvent(uiEventId);
	}
}

unsigned int EventModule::getEventId(const std::string& sEventName, EventListener* l)
{
	std::map<std::string, unsigned int>::iterator it = m_eventsNameKey.find(sEventName);
	if (it != m_eventsNameKey.end())
	{
		return it->second;
	}
	else
	{
		if (l != nullptr)
		{
			m_pendingIdRequests.push_back(std::make_pair(sEventName, l));
		}
		return 0;
	}
}

void EventModule::addListener(EventListener* l)
{
	m_eventListeners.add(l);
}

bool EventModule::removeListener(EventListener* l)
{
	return m_eventListeners.remove(l) == 1;
}

void EventModule::serviceDependencyBecameAvailable(Services serviceName, std::shared_ptr<void> service)
{
	if (serviceName == Services::LOGGER)
	{
		std::shared_ptr<LoggerService> loggerService = std::static_pointer_cast<LoggerService>(service);
		if (loggerService)
		{
			m_loggerNode = loggerService->createLoggerNode("EV");
		}
	}
}

void EventModule::serviceDependencyBecameUnavailable(Services serviceName)
{
	if (serviceName == Services::LOGGER)
	{
		m_loggerNode = nullptr;
	}
}
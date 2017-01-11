#include "System/Modules/TimingModule.h"

TimingModule::TimingModule()
{
	m_fTimeNow = 0;
	m_fTimeRewind = 0;
	addServiceDependency(Services::LOGGER);
}

TimingModule::~TimingModule()
{
}

void TimingModule::launchExpireEvent(const std::string& sName)
{
	for (int i = 0; i < m_listeners.size(); ++i)
	{
		m_listeners.at(i)->onTimerExpired(sName);
	}
}

void TimingModule::onUpdate()
{
	// Check whether the retrieved time is equal to 0. If it is, this indicates that the GLFW
	// window is either not open or has frozen. Ignore the change and  wait for the  window to 
	// become available again. Once it does, subtract the time difference from each active timer 
	// so that they continue where they left off.
	double time = glfwGetTime();
	if (time == 0)
	{
		m_fTimeRewind = m_fTimeNow - time;
		return;
	}
	else
	{
		m_fTimeNow = time;
	}

	if (m_fTimeRewind > 0)
	{
		for (std::shared_ptr<Timer>& t : m_timers)
		{
			t->setExpireTime(t->getExpireTime() - m_fTimeRewind);
		}

		m_fTimeRewind = 0;
	}

	// Evaluate each timer
	int i = 0;
	int iSize = m_timers.size();
	for (; i < iSize; ++i)
	{
		if (m_timers.at(i)->getExpireTime() <= m_fTimeNow)
		{
			launchExpireEvent(m_timers.at(i)->getName());

			m_timers.erase(m_timers.begin() + i);
			iSize--;	
		}
	}
}

bool TimingModule::start()
{
	if (m_loggerNode)
	{
		m_loggerNode->log("Timing module launching");
	}

	if (m_loggerNode)
	{
		m_loggerNode->log("Timing module successfully launched");
	}
	return true;
}

bool TimingModule::stop()
{
	m_listeners.clear();
	return true;
}

void TimingModule::addTimer(std::shared_ptr<Timer> timer)
{
	timer->setExpireTime(glfwGetTime() + timer->getDuration());
	m_timers.push_back(timer);
}

void TimingModule::addTimerListener(TimerListener* l)
{
	m_listeners.add(l);
}

void TimingModule::removeTimerListener(TimerListener* l)
{
	m_listeners.remove(l);
}

void TimingModule::serviceDependencyBecameAvailable(Services serviceName, std::shared_ptr<void> service)
{
	if (serviceName == Services::LOGGER)
	{
		std::shared_ptr<LoggerService> logger = std::static_pointer_cast<LoggerService>(service);
		if (logger)
		{
			m_loggerNode = logger->createLoggerNode("TI");
		}
	}
}

void TimingModule::serviceDependencyBecameUnavailable(Services serviceName)
{
	if (serviceName == Services::LOGGER)
	{
		m_loggerNode = nullptr;
	}
}
#include "System/Framework/Service.h"

Service::Service()
{
}

Service::Service(unsigned int uiInterval)
{
	m_bRunning = false;
	m_fTimeInterval = (float) uiInterval / 1000.f;
	m_uiSleepTime = uiInterval;
}

Service::~Service()
{
}

void Service::run()
{	
	// Run derived service setup
	onStart();

	// Enter service loop
	m_fTimeNow = glfwGetTime();
	m_fNextUpdateTime = m_fTimeNow + m_fTimeInterval;
	while (m_bRunning)
	{
		if (m_fTimeNow >= m_fNextUpdateTime)
		{
			// Perform updates and calculate the next update time
			onUpdate();
			m_fNextUpdateTime += m_fTimeInterval;
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(m_uiSleepTime));
		}

		m_fTimeNow = glfwGetTime();
	}

	// Run derived service termination
	onStop();
	m_self = nullptr;
}

bool Service::start()
{
	m_bRunning = true;
	m_self = shared_from_this();
	std::thread thread(&Service::run, this);
	thread.detach();
	return true;
}

bool Service::stop()
{
	m_bRunning = false;
	return true;
}
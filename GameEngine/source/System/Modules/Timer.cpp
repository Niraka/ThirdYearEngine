#include "System/Modules/Timer.h"

Timer::Timer()
{
}

Timer::Timer(std::string sName)
{
	m_fDuration = 5.f;
	m_fExpireTime = -1;
}

Timer::Timer(std::string sName, double fDuration)
{
	m_sName = sName;
	m_fDuration = fDuration;
	m_fExpireTime = -1;
}

Timer::~Timer()
{
}

void Timer::setExpireTime(double fExpireTime)
{
	m_fExpireTime = fExpireTime;
}

const std::string& Timer::getName() const
{
	return m_sName;
}

double Timer::getDuration() const
{
	return m_fDuration;
}

double Timer::getExpireTime() const
{
	return m_fExpireTime;
}
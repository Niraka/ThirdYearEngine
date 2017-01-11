#include "System/Services/LoggerService.h"

LoggerService::LoggerService() :
Service(0)
{
}

LoggerService::LoggerService(unsigned int uiInterval) :
Service(uiInterval)
{
	m_sDefaultLogFile = ".\\logs\\log.txt";
	m_bFileOutputEnabled = true;
	m_bConsoleOutputEnabled = true;
}

LoggerService::~LoggerService()
{
}
			
bool LoggerService::onStart()
{
	m_ofStream.open(m_sDefaultLogFile, std::ios::app);
	return m_ofStream.is_open();
}

bool LoggerService::onStop()
{
	if (m_ofStream.is_open())
	{
		m_ofStream.close();
	}
	return true;
}

void LoggerService::onUpdate()
{		
	m_mutex.lock();
	while (!m_messages.empty())
	{
		// Get a timestamp
		struct tm timeNow;
		__time64_t time64Bit;
		_time64(&time64Bit);
		_localtime64_s(&timeNow, &time64Bit);

		// Prepend the timestamp
		std::string s;
		s += std::to_string(timeNow.tm_year + 1900) + "-";
		s += std::to_string(timeNow.tm_mon + 1) + "-";
		s += std::to_string(timeNow.tm_mday) + " ";
		s += std::to_string(timeNow.tm_hour) + ":";
		s += std::to_string(timeNow.tm_min) + ":";
		s += std::to_string(timeNow.tm_sec) + " ";

		// Append the message
		s += "| ";
		s += m_messages.front();

		// Print it to the correct streams
		if (m_bConsoleOutputEnabled)
		{
			std::cout << s << std::endl;
		}
		if (m_bFileOutputEnabled)
		{
			if (m_ofStream.is_open())
			{
				m_ofStream << s << std::endl;
			}
		}
		
		m_messages.pop();
	}
	m_mutex.unlock();
}

std::shared_ptr<LoggerNode> LoggerService::createLoggerNode(std::string sPrefix)
{
	std::shared_ptr<LoggerNode> node = std::make_shared<LoggerNode>(sPrefix);
	node->m_listener = this;
	return node;
}

void LoggerService::forceOutput()
{
	onUpdate();
}

void LoggerService::setFileOutputEnabled(bool bEnabled)
{
	m_bConsoleOutputEnabled = bEnabled;
}

void LoggerService::setConsoleOutputEnabled(bool bEnabled)
{
	m_bConsoleOutputEnabled = bEnabled;
}

void LoggerService::onMessageLogged(std::string sMsg)
{
	m_mutex.lock();
	m_messages.push(sMsg);
	m_mutex.unlock();
}
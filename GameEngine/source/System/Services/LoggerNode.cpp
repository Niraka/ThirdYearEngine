#include "System/Services/LoggerNode.h"

LoggerNode::LoggerNode()
{
}

LoggerNode::LoggerNode(std::string sPrefix)
{
	m_sPrefix = sPrefix;
}

LoggerNode::~LoggerNode()
{
}

void LoggerNode::log(std::string sMessage)
{
	if (m_listener)
	{
		m_listener->onMessageLogged(m_sPrefix + " : " + sMessage);
	}
}
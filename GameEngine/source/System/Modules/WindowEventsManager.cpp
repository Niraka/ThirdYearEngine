#include "System/Modules/WindowEventsManager.h"

bool WindowEventsManager::m_bInstanceExists;
WindowEventsManager* WindowEventsManager::m_instance;

WindowEventsManager::WindowEventsManager()
{
	m_bInstanceExists = true;
}

WindowEventsManager::~WindowEventsManager()
{
	m_bInstanceExists = false;
}

WindowEventsManager* WindowEventsManager::getInstance()
{
	if (m_bInstanceExists)
	{
		return m_instance;
	}
	else
	{
		m_instance = new WindowEventsManager();
		return m_instance;
	}
}

void WindowEventsManager::windowCloseCallbackBroadcaster()
{
	int iSize = m_listeners.size();
	for (int i = 0; i < iSize; ++i)
	{
		m_listeners.at(i)->onWindowClose();
	}
}

void WindowEventsManager::windowResizedCallbackBroadcaster(int iWidth, int iHeight)
{
	int iSize = m_listeners.size();
	for (int i = 0; i < iSize; ++i)
	{
		m_listeners.at(i)->onWindowResized(iWidth, iHeight);
	}
}

void WindowEventsManager::frameBufferResizedCallbackBroadcaster(int iWidth, int iHeight)
{
	int iSize = m_listeners.size();
	for (int i = 0; i < iSize; ++i)
	{
		m_listeners.at(i)->onFramebufferResized(iWidth, iHeight);
	}
}

void WindowEventsManager::windowCloseCallback(GLFWwindow* window)
{
	getInstance()->windowCloseCallbackBroadcaster();
}

void WindowEventsManager::windowResizedCallback(GLFWwindow* window, int iWidth, int iHeight)
{
	getInstance()->windowResizedCallbackBroadcaster(iWidth, iHeight);
}

void WindowEventsManager::frameBufferResizedCallback(GLFWwindow* window, int iWidth, int iHeight)
{
	getInstance()->frameBufferResizedCallbackBroadcaster(iWidth, iHeight);
}

void WindowEventsManager::addWindowListener(WindowListener* l)
{
	m_listeners.add(l);
}

int WindowEventsManager::removeWindowListener(WindowListener* l)
{
	return m_listeners.remove(l);
}

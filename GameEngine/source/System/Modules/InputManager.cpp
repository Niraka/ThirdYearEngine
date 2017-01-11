#include "System/Modules/InputManager.h"

bool InputManager::m_bInstanceExists;
InputManager* InputManager::m_instance;

InputManager::InputManager()
{
	m_bInstanceExists = true;
}

InputManager::~InputManager()
{
	m_bInstanceExists = false;
}

InputManager* InputManager::getInstance()
{
	if (m_bInstanceExists)
	{
		return m_instance;
	}
	else
	{
		m_instance = new InputManager();
		return m_instance;
	}
}

void InputManager::char_callback(GLFWwindow* window, unsigned int uiChar)
{
	getInstance()->charCallbackBroadcaster(window, uiChar);
}

void InputManager::scroll_callback(GLFWwindow* window, double fXOffset, double fYOffset)
{
	getInstance()->scrollCallbackBroadcaster(window, fXOffset, fYOffset);
}

void InputManager::cursorEnter_callback(GLFWwindow* window, int iEntered)
{
	getInstance()->cursorEnterCallbackBroadcaster(window, iEntered);
}

void InputManager::cursorPosition_callback(GLFWwindow* window, double fXPos, double fYPos)
{
	getInstance()->cursorPositionCallbackBroadcaster(window, fXPos, fYPos);
}

void InputManager::mouse_callback(GLFWwindow* window, int iButton, int iAction, int iMods)
{
	getInstance()->mouseCallbackBroadcaster(window, iButton, iAction, iMods);
}

void InputManager::key_callback(GLFWwindow* window, int iKey, int iScancode, int iAction, int iMods)
{
	getInstance()->keyCallbackBroadcaster(window, iKey, iScancode, iAction, iMods);
}

void InputManager::charCallbackBroadcaster(GLFWwindow* window, unsigned int uiChar)
{
	int iSize = m_listeners.size();
	for (int i = 0; i < iSize; ++i)
	{
		m_listeners.at(i)->onCharacterTyped(uiChar);		
	}
}

void InputManager::scrollCallbackBroadcaster(GLFWwindow* window, double fXOffset, double fYOffset)
{
	int iSize = m_listeners.size();
	for (int i = 0; i < iSize; ++i)
	{
		m_listeners.at(i)->onScroll(fXOffset, fYOffset);
	}
}

void InputManager::cursorEnterCallbackBroadcaster(GLFWwindow* window, int iEntered)
{
	int iSize = m_listeners.size();
	if (iEntered == GL_TRUE)
	{
		for (int i = 0; i < iSize; ++i)
		{
			m_listeners.at(i)->onCursorEnter();
		}
	}
	else
	{
		for (int i = 0; i < iSize; ++i)
		{
			m_listeners.at(i)->onCursorExit();		
		}
	}
}

void InputManager::cursorPositionCallbackBroadcaster(GLFWwindow* window, double fXPos, double fYPos)
{
	int iSize = m_listeners.size();
	for (int i = 0; i < iSize; ++i)
	{
		m_listeners.at(i)->onCursorMoved(fXPos, fYPos);	
	}
}

void InputManager::mouseCallbackBroadcaster(GLFWwindow* window, int iButton, int iAction, int iMods)
{
	int iSize = m_listeners.size();
	if (iAction == GLFW_PRESS)
	{
		for (int i = 0; i < iSize; ++i)
		{
			m_listeners.at(i)->onMousePressed(iButton, iMods);		
		}
	}
	else
	{
		for (int i = 0; i < iSize; ++i)
		{
			m_listeners.at(i)->onMouseReleased(iButton, iMods);		
		}
	}
}

void InputManager::keyCallbackBroadcaster(GLFWwindow* window, int iKey, int iScancode, int iAction, int iMods)
{
	int iSize = m_listeners.size();
	if (iAction == GLFW_PRESS || iAction == GLFW_REPEAT)
	{	
		for (int i = 0; i < iSize; ++i)
		{
			m_listeners.at(i)->onKeyPressed(iKey, iScancode, iMods);			
		}
	}
	else
	{
		for (int i = 0; i < iSize; ++i)
		{
			m_listeners.at(i)->onKeyReleased(iKey, iScancode, iMods);		
		}
	}
}

void InputManager::clearListeners()
{
	m_listeners.clear();
}

void InputManager::addInputListener(InputListener* l)
{
	m_listeners.add(l);
}

int InputManager::removeInputListener(InputListener* l)
{
	return m_listeners.remove(l);
}
#include "System/Modules/KeyAction.h"

void KeyAction::onKeyPressed(int iKey, int iModifiers)
{
	for (std::pair<const int, std::string>& binding : m_pressBindings)
	{
		if (binding.first == iKey)
		{
			onAction(binding.second);
		}
	}
}

void KeyAction::onKeyReleased(int iKey, int iModifiers)
{
	for (std::pair<const int, std::string>& binding : m_releaseBindings)
	{
		if (binding.first == iKey)
		{
			onAction(binding.second);
		}
	}
}

void KeyAction::addAction(std::string sActionName)
{
	m_actions.insert(sActionName);
}

bool KeyAction::bindKeyToAction(int iKey, int iModifiers, int iAction, std::string sActionName)
{
	// Check the action exists
	if (m_actions.find(sActionName) == m_actions.end())
	{
		return false;
	}

	// Bind it, overwriting where necessary
	if (iAction == GLFW_PRESS)
	{
		if (m_pressBindings.find(iKey) == m_pressBindings.end())
		{
			m_pressBindings.emplace(iKey, sActionName);
		}
		else
		{
			m_pressBindings.at(iKey) = sActionName;
		}
		return true;
	}
	else if (iAction == GLFW_RELEASE)
	{
		if (m_releaseBindings.find(iKey) == m_releaseBindings.end())
		{
			m_releaseBindings.emplace(iKey, sActionName);
		}
		else
		{
			m_releaseBindings.at(iKey) = sActionName;
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool KeyAction::unbindKey(int iAction, std::string sActionName)
{
	// Check the action exists
	if (m_actions.find(sActionName) == m_actions.end())
	{
		return false;
	}
	
	// Unbind it
	if (iAction == GLFW_PRESS)
	{
		for (std::pair<const int, std::string>& binding : m_pressBindings)
		{
			if (binding.second == sActionName)
			{
				return true;
			}
		}
		return false;
	}
	else if (iAction == GLFW_RELEASE)
	{
		for (std::pair<const int, std::string>& binding : m_releaseBindings)
		{
			if (binding.second == sActionName)
			{
				return true;
			}
		}
		return false;
	}
	else
	{
		return false;
	}
}
#include "System/Modules/ControlSet.h"

ControlSet::ControlSet()
{
	m_movementMapping = nullptr;
}

ControlSet::~ControlSet()
{
}

void ControlSet::addMovementMapping(MovementMapping* mapping)
{
	m_movementMapping = mapping;
}

void ControlSet::addMouseMapping(int iButton, int iEventType, int iModifiers, MouseAction* action)
{
	// Search for the mapping. If it existed, overwrite the action.
	for (MouseMapping& mapping : m_mouseMappings)
	{
		if (mapping.iButton == iButton)
		{
			if (mapping.iEventType == iEventType)
			{
				if (mapping.iModifiers == iModifiers)
				{
					mapping.action = action; 
					return;
				}
			}
		}
	}

	// If the mapping did not already exist, create it and push it on to the mappings vector
	MouseMapping mapping;
	mapping.iButton = iButton;
	mapping.iEventType = iEventType;
	mapping.iModifiers = iModifiers;
	mapping.action = action;
	m_mouseMappings.push_back(mapping);
}

void ControlSet::addKeyMapping(int iKey, int iEventType, int iModifiers, KeyAction* action)
{
	// Search for the mapping. If it existed, overwrite the action.
	for (KeyMapping& mapping : m_keyMappings)
	{
		if (mapping.iKey == iKey)
		{
			if (mapping.iEventType == iEventType)
			{
				if (mapping.iModifiers == iModifiers)
				{
					mapping.action = action;
					return;
				}
			}
		}
	}

	// If the mapping did not already exist, create it and push it on to the mappings vector
	KeyMapping mapping;
	mapping.iKey = iKey;
	mapping.iEventType = iEventType;
	mapping.iModifiers = iModifiers;
	mapping.action = action;
	m_keyMappings.push_back(mapping);
}

void ControlSet::removeMouseMapping(int iButton, int iEventType, int iModifiers)
{
	unsigned uiIndexOffset = 0;
	for (MouseMapping& mapping : m_mouseMappings)
	{
		if (mapping.iButton == iButton)
		{
			if (mapping.iEventType == iEventType)
			{
				if (mapping.iModifiers == iModifiers)
				{
					m_mouseMappings.erase(m_mouseMappings.begin() + uiIndexOffset);
					return;
				}
			}
		}
		++uiIndexOffset;
	}
}

void ControlSet::removeKeyMapping(int iKey, int iEventType, int iModifiers)
{
	unsigned uiIndexOffset = 0;
	for (KeyMapping& mapping : m_keyMappings)
	{
		if (mapping.iKey == iKey)
		{
			if (mapping.iEventType == iEventType)
			{
				if (mapping.iModifiers == iModifiers)
				{
					m_keyMappings.erase(m_keyMappings.begin() + uiIndexOffset);
					return;
				}
			}
		}
		++uiIndexOffset;
	}
}

bool ControlSet::hasMovementMapping()
{
	return m_movementMapping != nullptr;
}

bool ControlSet::hasMouseMapping(const int& iButton, const int& iEventType, const int& iModifiers)
{
	for (MouseMapping& mapping : m_mouseMappings)
	{
		if (mapping.iButton == iButton)
		{
			if (mapping.iEventType == iEventType)
			{
				if (mapping.iModifiers == iModifiers)
				{
					if (mapping.action != nullptr)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
		}
	}
	return false;
}

bool ControlSet::hasKeyMapping(const int& iKey, const int& iEventType, const int& iModifiers)
{
	for (KeyMapping& mapping : m_keyMappings)
	{
		if (mapping.iKey == iKey)
		{
			if (mapping.iEventType == iEventType)
			{
				if (mapping.iModifiers == iModifiers)
				{
					if (mapping.action != nullptr)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
		}
	}
	return false;
}

MovementMapping* ControlSet::getMovementMapping()
{
	return m_movementMapping;
}

MouseAction* ControlSet::getMouseAction(const int& iButton, int iEventType, const int& iModifiers)
{
	for (MouseMapping& mapping : m_mouseMappings)
	{
		if (mapping.iButton == iButton)
		{
			if (mapping.iEventType == iEventType)
			{
				if (mapping.iModifiers == iModifiers)
				{
					return mapping.action;
				}
			}
		}
	}
	return nullptr;
}

KeyAction* ControlSet::getKeyAction(const int& iKey, int iEventType, const int& iModifiers)
{
	for (KeyMapping& mapping : m_keyMappings)
	{
		if (mapping.iKey == iKey)
		{
			if (mapping.iEventType == iEventType)
			{
				if (mapping.iModifiers == iModifiers)
				{
					return mapping.action;
				}
			}
		}
	}
	return nullptr;
}
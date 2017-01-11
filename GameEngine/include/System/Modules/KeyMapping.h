/**
A KeyMapping binds together a key code, event type code, modifiers bitmask and KeyAction.

@author Nathan */

#ifndef KEY_MAPPING_H
#define KEY_MAPPING_H

#include "System/Modules/KeyAction.h"

struct KeyMapping
{
	int iKey;
	int iEventType;
	int iModifiers;
	KeyAction* action;
};

#endif
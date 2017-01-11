/**
A MouseMapping binds together a mouse code, event type code, modifiers bitmask and 
MouseAction.

@author Nathan */

#ifndef MOUSE_MAPPING_H
#define MOUSE_MAPPING_H

#include "System/Modules/MouseAction.h"

struct MouseMapping
{
	int iButton;
	int iEventType;
	int iModifiers;
	MouseAction* action;
};

#endif
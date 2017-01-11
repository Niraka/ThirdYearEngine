/**
The names of the modules. 

If a new module is added, its name must be added to this file aswell. 

@author Nathan */

#ifndef MODULES_H
#define MODULES_H

enum Modules
{
	COMMAND,       // System: For receiving and processing commands 
	WINDOW,		   // System: For creation and management of a window and a rendering target
	TIMING,		   // System: For time-related features
	AUDIO,		   // System: For managing all audio related functionality
	RESOURCE,	   // System: For the central storage and management of particular resources
	EVENTS,        // System: For launching system-wide events of arbitrary types

	GUI,		   // Scene : For creating user interfaces
	PHYSICS,	   // Scene : For performing physics calculations 
	ACTING,		   // Scene : For creating models, animations, actors and other renderable objects
	ENTITY,		   // Scene : For binding together components to form game world entities
	AI,			   // Scene : For the creation and binding together of AI for entities
	PARTICLE,	   // Scene : For the creation and rendering of particle effects

	SCRIPTING,	   // Game  : For the creation and management of scripts that trigger actions within the gamec
	EDITOR,		   // Game  : A game world editor
};

#endif
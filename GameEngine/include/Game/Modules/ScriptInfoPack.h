/**
A ScriptInfoPack contains pointers to modules and other useful info that can be used to execute
commands from Scripts. 

Expected usage is that the pack will be created via the ScriptingModule and then passed as
a reference to a Script object when it is its turn to execute.

@author Nathan */

#ifndef SCRIPT_INFO_PACK_H
#define SCRIPT_INFO_PACK_H

#include "System/Modules/ResourceModule.h"
#include "System/Modules/TimingModule.h"
#include "System/Modules/WindowModule.h"
#include "Scene/Modules/GUIModule.h"
#include "Scene/Modules/PhysicsModule.h"
#include "Scene/Modules/ActingModule.h"
#include "Scene/Modules/EntityModule.h"
#include "Scene/Modules/AIModule.h"
#include "Game/Modules/ScriptTimerRegistrar.h"
#include "Game/Modules/ScriptActionTerminal.h"
#include "Game/Modules/ScriptingNumberGenerator.h"
#include "System/Modules/AudioModule.h"

struct ScriptInfoPack
{
	std::shared_ptr<WindowModule>   windowModule;
	std::shared_ptr<TimingModule>   timingModule;
	std::shared_ptr<ResourceModule> resourceModule;
	std::shared_ptr<GUIModule>      guiModule;
	std::shared_ptr<PhysicsModule>  physicsModule;
	std::shared_ptr<ActingModule>   actingModule;
	std::shared_ptr<EntityModule>   entityModule;
	std::shared_ptr<AIModule>       aiModule;
	std::shared_ptr<LoggerNode>     loggerNode;
	std::shared_ptr<AudioModule>    audioModule;
	ScriptTimerRegistrar*           timerRegistrar;
	ScriptActionTerminal*           actionTerminal;
	ScriptingNumberGenerator*       numberGenerator;
};

#endif
#include "System/Services/ModuleWatcherService.h"

ModuleWatcherService::ModuleWatcherService() :
Service(0)
{
}

ModuleWatcherService::ModuleWatcherService(unsigned int uiInterval) :
Service(uiInterval)
{

}

ModuleWatcherService::~ModuleWatcherService()
{
}

bool ModuleWatcherService::onStart()
{
	return true;
}

bool ModuleWatcherService::onStop()
{
	return true;
}

void ModuleWatcherService::onUpdate()
{

}
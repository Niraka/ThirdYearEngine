#include "System/Services/ResourceCleanerService.h"

ResourceCleanerService::ResourceCleanerService() :
Service(0)
{
}

ResourceCleanerService::ResourceCleanerService(unsigned int uiInterval) :
Service(uiInterval)
{

}

ResourceCleanerService::~ResourceCleanerService()
{
}

bool ResourceCleanerService::onStart()
{
	return true;
}

bool ResourceCleanerService::onStop()
{
	return true;
}

void ResourceCleanerService::onUpdate()
{

}
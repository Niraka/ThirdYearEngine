#include "System/Services/ResourceUsageTrackerService.h"

ResourceUsageTrackerService::ResourceUsageTrackerService() :
Service(0)
{
}

ResourceUsageTrackerService::ResourceUsageTrackerService(unsigned int uiInterval) :
Service(uiInterval)
{

}

ResourceUsageTrackerService::~ResourceUsageTrackerService()
{
}

bool ResourceUsageTrackerService::onStart()
{
	return true;
}

bool ResourceUsageTrackerService::onStop()
{
	return true;
}

void ResourceUsageTrackerService::onUpdate()
{

}
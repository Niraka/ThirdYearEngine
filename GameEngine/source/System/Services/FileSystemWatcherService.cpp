#include "System/Services/FileSystemWatcherService.h"

FileSystemWatcherService::FileSystemWatcherService() :
Service(0)
{
}

FileSystemWatcherService::FileSystemWatcherService(unsigned int uiInterval) :
Service(uiInterval)
{

}

FileSystemWatcherService::~FileSystemWatcherService()
{
}

bool FileSystemWatcherService::onStart()
{
	return true;
}

bool FileSystemWatcherService::onStop()
{
	return true;
}

void FileSystemWatcherService::onUpdate()
{

}
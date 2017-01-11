#include "System/Modules/ResourceModule.h"

ResourceModule::ResourceModule()
{
	addServiceDependency(Services::LOGGER);
}

ResourceModule::~ResourceModule()
{
}

void ResourceModule::onUpdate()
{
}

bool ResourceModule::start()
{
	if (m_loggerNode)
	{
		m_loggerNode->log("Resource module launching");
	}

	buildTypeIds();

	if (m_loggerNode)
	{
		m_loggerNode->log("Resource module successfully launched");
	}

	return true;
}

bool ResourceModule::stop()
{
	if (m_loggerNode)
	{
		m_loggerNode->log("Resource module shutting down");
	}

	if (m_loggerNode)
	{
		m_loggerNode->log("Resource module successfully shut down");
	}
	m_loggerNode = nullptr;
	return true;
}

void ResourceModule::buildTypeIds()
{
	// Cache each resource types name and assign it an id. The id 0 is reserved to indicate an unsupported
	// resource type.
	std::string sType;

	sType = typeid(Texture).name();
	m_resourceIds.emplace(sType, 1);

	sType = typeid(Image).name();
	m_resourceIds.emplace(sType, 2);

	sType = typeid(sf::SoundBuffer).name();
	m_resourceIds.emplace(sType, 3);

	// Output information about the supported resources
	if (m_loggerNode)
	{
		m_loggerNode->log("Supported resources: \n   Textures\n   Image\n   sf::SoundBuffer" );
	}
}

unsigned int ResourceModule::createResource(unsigned int uiResourceTypeId)
{
	switch (uiResourceTypeId)
	{
	case 1:
		return m_textures.createResource();
	case 2:
		return m_images.createResource();
	case 3:
		return m_soundBuffers.createResource();
	default:
		return 0;
	}
}

bool ResourceModule::deleteResource(unsigned int uiResourceTypeId, unsigned int uiResourceId)
{
	switch (uiResourceTypeId)
	{
	case 1:
		return m_textures.deleteResource(uiResourceId);
	case 2:
		return m_images.deleteResource(uiResourceId);
	case 3:
		return m_soundBuffers.deleteResource(uiResourceId);
	default:
		return false;
	}
}

void ResourceModule::serviceDependencyBecameAvailable(Services serviceName, std::shared_ptr<void> service)
{
	if (serviceName == Services::LOGGER)
	{
		std::shared_ptr<LoggerService> loggerService = std::static_pointer_cast<LoggerService>(service);
		m_loggerNode = loggerService->createLoggerNode("RM");
	}
}

void ResourceModule::serviceDependencyBecameUnavailable(Services serviceName)
{
	if (serviceName == Services::LOGGER)
	{
		m_loggerNode = nullptr;
	}
}
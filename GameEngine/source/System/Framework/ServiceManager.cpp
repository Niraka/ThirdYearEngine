#include "System/Framework/ServiceManager.h"

ServiceManager::ServiceManager()
{
}

ServiceManager::~ServiceManager()
{
}

bool ServiceManager::startService(Services service)
{
	// Check the service is not already active. If it is, stop it first
	if (m_services.find(service) != m_services.end())
	{
		stopService(service);
	}

	// Start the new service
	switch (service)
	{
	case Services::FILE_SYSTEM_WATCHER:
		m_services.emplace(service, std::make_shared<FileSystemWatcherService>(1000));
		break;
	case Services::LOGGER:
		m_services.emplace(service, std::make_shared<LoggerService>(500));
		break;
	case Services::MODULE_WATCHER:
		m_services.emplace(service, std::make_shared<ModuleWatcherService>(1000));
		break;
	case Services::RESOURCE_CLEANER:
		m_services.emplace(service, std::make_shared<ResourceCleanerService>(1000));
		break;
	case Services::RESOURCE_USAGE_TRACKER:
		m_services.emplace(service, std::make_shared<ResourceUsageTrackerService>(1000));
		break;
	default:
		return false;
	}

	// Notify existing modules and services that the new service has been launched
	onServiceStarted(service, m_services.at(service));
	if (m_serviceLifetimeListener)
	{
		m_serviceLifetimeListener->onServiceStarted(service, m_services.at(service));
	}

	// Initialise the new service
	if (m_services.at(service)->start())
	{
		return true;
	}
	else
	{
		std::cout << "FATAL: Service '" << serviceAsString(service) << "' failed to start" << std::endl;
		return false;
	}
}

bool ServiceManager::stopService(Services service)
{
	// Check the service exists
	if (m_services.find(service) != m_services.end())
	{
		onServiceStopped(service);
		if (m_serviceLifetimeListener)
		{
			m_serviceLifetimeListener->onServiceStopped(service);
		}
		m_services.at(service)->stop();
		m_services.erase(service);
		return true;
	}
	else
	{
		return false;
	}
}

void ServiceManager::bindServiceLifetimeListener(ServiceLifetimeListener* l)
{
	m_serviceLifetimeListener = l;
}

void ServiceManager::onServiceStarted(Services serviceName, std::shared_ptr<Service> service)
{
	// For each active service, check if it is interested in the service starting
	for (const std::pair<Services, std::shared_ptr<Service>>& p : m_services)
	{
		if (p.second->hasServiceDependency(serviceName))
		{
			p.second->serviceDependencyBecameAvailable(serviceName, service);
		}
	}
	
	// Check whether the newly started up service is interested in any existing services
	for (const std::pair<Services, std::shared_ptr<Service>>& p : m_services)
	{
		if (service->hasServiceDependency(p.first))
		{
			service->serviceDependencyBecameAvailable(p.first, p.second);
		}
	}
}

void ServiceManager::onServiceStopped(Services serviceName)
{
	// For each active service, check if it is interested in the service stopping
	for (const std::pair<Services, std::shared_ptr<Service>>& p : m_services)
	{
		if (p.second->hasServiceDependency(serviceName))
		{
			p.second->serviceDependencyBecameUnavailable(serviceName);
		}
	}
}

void ServiceManager::onModuleStarted(Modules moduleName, std::shared_ptr<Module> module)
{
	// For each active service, check if it is interested in the module starting
	for (const std::pair<Services, std::shared_ptr<Service>>& p : m_services)
	{
		if (p.second->hasModuleDependency(moduleName))
		{
			p.second->moduleDependencyBecameAvailable(moduleName, module);
		}
	}
	
	// Check whether the newly started up module is interested in any existing services
	for (const std::pair<Services, std::shared_ptr<Service>>& p : m_services)
	{
		if (module->hasServiceDependency(p.first))
		{
			module->serviceDependencyBecameAvailable(p.first, p.second);
		}
	}
}

void ServiceManager::onModuleStopped(Modules moduleName)
{
	// For each active service, check if it is interested in the module stopping
	for (const std::pair<Services, std::shared_ptr<Service>>& p : m_services)
	{
		if (p.second->hasModuleDependency(moduleName))
		{
			p.second->moduleDependencyBecameUnavailable(moduleName);
		}
	}
}

std::string ServiceManager::serviceAsString(Services service)
{
	switch (service)
	{
	case Services::FILE_SYSTEM_WATCHER:
		return "file_system_watcher";
	case Services::LOGGER:
		return "logger";
	case Services::MODULE_WATCHER:
		return "module_watcher";
	case Services::RESOURCE_CLEANER:
		return "resource_cleaner";
	case Services::RESOURCE_USAGE_TRACKER:
		return "resource_usage_tracker";
	default:
		return "unknown_service";
	}
}
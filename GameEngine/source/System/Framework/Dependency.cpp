#include "System/Framework/Dependency.h"

void Dependency::addModuleDependency(Modules moduleName)
{
	if (!hasModuleDependency(moduleName))
	{
		m_moduleDependencies.push_back(moduleName);
	}
}

void Dependency::addServiceDependency(Services serviceName)
{
	if (!hasServiceDependency(serviceName))
	{
		m_serviceDependencies.push_back(serviceName);
	}
}

bool Dependency::hasModuleDependency(Modules moduleName)
{
	for (Modules& m : m_moduleDependencies)
	{
		if (m == moduleName)
		{
			return true;
		}
	}
	return false;
}

bool Dependency::hasServiceDependency(Services serviceName)
{
	for (Services& s : m_serviceDependencies)
	{
		if (s == serviceName)
		{
			return true;
		}
	}
	return false;
}

void Dependency::moduleDependencyBecameAvailable(Modules moduleName, std::shared_ptr<void> module)
{
}

void Dependency::serviceDependencyBecameAvailable(Services serviceName, std::shared_ptr<void> service)
{
}

void Dependency::moduleDependencyBecameUnavailable(Modules moduleName)
{
}

void Dependency::serviceDependencyBecameUnavailable(Services serviceName)
{
}
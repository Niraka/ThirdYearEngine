#include "System/Modules/MaterialLibraryManager.h"

MaterialLibraryManager::MaterialLibraryManager()
{
}

MaterialLibraryManager::~MaterialLibraryManager()
{
}

bool MaterialLibraryManager::hasLibrary(std::string sName)
{
	return m_libraries.find(sName) != m_libraries.end();
}

std::shared_ptr<MaterialLibrary> MaterialLibraryManager::getLibrary(std::string sName)
{
	if (hasLibrary(sName))
	{
		return m_libraries.at(sName);
	}
	else
	{
		return nullptr;
	}
}

bool MaterialLibraryManager::loadLibrary(std::string sName)
{
	// Check the name is available
	if (hasLibrary(sName))
	{
		return false;
	}

	// Load and store the library
	std::shared_ptr<MaterialLibrary> lib = std::make_shared<MaterialLibrary>();
	if (m_libraryLoader.loadMaterialLibrary(sName, lib))
	{
		m_libraries.emplace(sName, lib);
		return true;
	}
	else
	{
		return false;
	}
}

void MaterialLibraryManager::unloadLibrary(std::string sName)
{
	m_libraries.erase(sName);
}
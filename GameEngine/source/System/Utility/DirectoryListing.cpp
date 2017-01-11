#include "System/Utility/DirectoryListing.h"

DirectoryListing* DirectoryListing::m_instance;
bool DirectoryListing::m_bInstanceExists;

DirectoryListing::DirectoryListing()
{
	// Add directory mappings here
	m_directories.emplace("scenes", ".\\..\\data\\scenes\\");
	m_directories.emplace("entities", ".\\..\\data\\entity_specs\\");
	m_directories.emplace("textures", ".\\..\\data\\textures\\");
	m_directories.emplace("materials", ".\\..\\data\\materials\\");
	m_directories.emplace("meshes", ".\\..\\data\\meshes\\");
	m_directories.emplace("shaders", ".\\..\\data\\shaders\\");
	m_directories.emplace("models", ".\\..\\data\\models\\");
	m_directories.emplace("scripts", ".\\..\\data\\scripts\\");
	m_directories.emplace("audio", ".\\..\\data\\audio\\");
	m_directories.emplace("fonts", ".\\..\\data\\fonts\\");
	m_directories.emplace("interfaces", ".\\..\\data\\interfaces\\");
	m_directories.emplace("images", ".\\..\\data\\images\\");

	m_bInstanceExists = true;
}

DirectoryListing::~DirectoryListing()
{
	m_bInstanceExists = false;
}

DirectoryListing* DirectoryListing::getInstance()
{
	if (m_bInstanceExists)
	{
		return m_instance;
	}
	else
	{
		m_instance = new DirectoryListing();
		return m_instance;
	}
}

std::string DirectoryListing::getDirectory(std::string sName)
{
	if (m_directories.find(sName) != m_directories.end())
	{
		return m_directories.at(sName);
	}
	else
	{
		return std::string();
	}
}
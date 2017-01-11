#include "System/Modules/MaterialLibrary.h"

MaterialLibrary::MaterialLibrary()
{
}

MaterialLibrary::~MaterialLibrary()
{
}

bool MaterialLibrary::hasMaterial(const std::string& sName)
{
	return m_materialLibrary.find(sName) != m_materialLibrary.end();
}

const Material& MaterialLibrary::getMaterial(const std::string& sName)
{
	return m_materialLibrary.at(sName);
}

void MaterialLibrary::addMaterial(std::string sName, Material m)
{
	if (hasMaterial(sName))
	{
		m_materialLibrary.at(sName) = m;
	}
	else
	{
		m_materialLibrary.emplace(sName, m);
	}
}

unsigned int MaterialLibrary::getNumMaterials() const
{
	return m_materialLibrary.size();
}
#include "Scene/Modules/ModelManager.h"

ModelManager::ModelManager()
{
}

ModelManager::~ModelManager()
{
}

bool ModelManager::createModel(ModelInfo info)
{
	std::shared_ptr<Model> model = std::make_shared<Model>();

	// Create storage
	// Load and bind mesh - we are not allowing reuse of meshes at this point
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
	if (!m_meshLoader.loadMesh(info.sMeshFile, mesh))
	{
		return false;
	}
	model->setMesh(mesh);

	// Load and bind the material library. This may or may not match the default material library. It is up
	// to the user to decide
	if (m_materialLibraryManager.hasLibrary(info.sMaterialLibrary))
	{
		model->setMaterialLibrary(m_materialLibraryManager.getLibrary(info.sMaterialLibrary));
	}
	else
	{
		if (m_materialLibraryManager.loadLibrary(info.sMaterialLibrary))
		{
			model->setMaterialLibrary(m_materialLibraryManager.getLibrary(info.sMaterialLibrary));
		}
		else
		{
			return false;
		}
	}

	// Store the model
	if (m_models.find(info.sModelName) == m_models.end())
	{
		m_models.emplace(info.sModelName, model);
		return true;
	}
	else
	{
		return false;
	}
}

void ModelManager::deleteModel(std::string sName)
{
	if (m_models.find(sName) != m_models.end())
	{
		m_models.at(sName) = nullptr;
	}
}

std::shared_ptr<Model> ModelManager::getModel(std::string sName)
{
	if (m_models.find(sName) != m_models.end())
	{
		return m_models.at(sName);
	}
	else
	{
		return nullptr;
	}
}

bool ModelManager::modelExists(std::string sName) const
{
	return m_models.find(sName) != m_models.end();
}
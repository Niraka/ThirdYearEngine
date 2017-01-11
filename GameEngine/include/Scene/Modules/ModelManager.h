/**
The ModelManager is responsible for loading, unloading and storing Models. 

@author Nathan */

#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include "Scene/Modules/MeshLoader.h"
#include "Scene/Modules/Model.h"
#include "Scene/Modules/ModelInfo.h"
#include "System/Modules/TextureManager.h"
#include "System/Modules/MaterialLibraryManager.h"

#include <map>
#include <string>

class ModelManager
{
	private:
		std::map<std::string, std::shared_ptr<Model>> m_models;
		MeshLoader m_meshLoader;
		TextureManager m_textureManager;
		MaterialLibraryManager m_materialLibraryManager;

	protected:

	public:
		/**
		Constructs a ModelManager. */
		ModelManager();

		/**
		Destructs a ModelManager. */
		~ModelManager();

		/**
		Creates a model using the given ModelInfo. This function will fail if any of the
		requested data was unavailable.
		@param info The model info
		@return True if the model was successfully created, false otherwise */
		bool createModel(ModelInfo info);

		/**
		Deletes a model with the given name. Note that the model will not actually
		be removed from memory until ALL references to it are released. 
		@param sName The name of the model to unload */
		void deleteModel(std::string sName);

		/**
		Returns a pointer to the desired Model or a nullptr if such a model did not
		exist.
		@param sName The name of the model to get
		@return A shared pointer to a Model, or a nullptr */
		std::shared_ptr<Model> getModel(std::string sName);

		/**
		Returns true if a Model with the given name exists. 
		@param sName The name of the Model to query
		@return True if the Model existed, false otherwise */
		bool modelExists(std::string sName) const;
};

#endif
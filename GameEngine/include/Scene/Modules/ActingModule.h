/**
The ActingModule handles the Actors, Meshes, Textures, Animations and Models. 

@author Nathan */

#ifndef ACTING_MODULE_H
#define ACTING_MODULE_H

#include "Scene/Modules/Actor.h"
#include "Scene/Modules/ModelManager.h"
#include "Scene/Modules/AnimationManager.h"
#include "System/Framework/Module.h"
#include "Scene/modules/ModelInfo.h"
#include "System/Utility/DirectoryListing.h"
#include "System/Services/LoggerService.h"

#include <tinyxml2.h>
#include <memory>

class ActingModule :
	public Module
{
	private:
		ModelManager m_modelManager;
		AnimationManager m_animationManager;
		std::shared_ptr<LoggerNode> m_loggerNode;

	protected:
		/**
		Updates the Acting Module. */
		void onUpdate();

	public:
		/**
		Construts a default ActingModule. */
		ActingModule();
		
		/**
		Destructs the ActingModule. */
		~ActingModule();

		/**
		Starts up the module.
		@return True if the module started up successfully, false otherwise */
		bool start();

		/**
		Stops the module.
		@return True if the module stopped successfully, false otherwise */
		bool stop();

		/**
		Creates and returns an Actor using the given Model. If the Model did  not exist, the 
		Actor is not created and a nullptr is returned instead. A reference to the Actor is
		not stored internally.
		@param sModel The name of the Model to use
		@return A shared pointer to an Actor */
		std::shared_ptr<Actor> createActor(std::string sModel);

		/**
		Loads a model using the given ModelInfo.
		@param info The model info */
		void loadModel(ModelInfo info);

		/**
		Loads a set of models. This function is a convenience function that has no performance
		benefit over individual calls to loadModel(ModelInfo).
		@param infos A vector of ModelInfo objects */
		void loadModels(std::vector<ModelInfo> infos);
		
		/**
		Loads a set of models from a given XML file. The given directory should not include the
		".\\data\\models\\" parent directory as this will be automatically prepended. If the file could
		not be found, this function will fail silently.
		@param sFile The file to load the model info from */
		void loadModelsFromFile(std::string sFile);

		/**
		This function is called when a service becomes available that is a dependency of this class. Note that
		the pointer is delivered as a void pointer and must first be cast to the correct service using a static
		pointer cast.
		@param serviceName The name of the service
		@param service A shared pointer to the new service */
		void serviceDependencyBecameAvailable(Services serviceName, std::shared_ptr<void> service);

		/**
		This function is called when a service that is a dependency of this class becomes unavailable.
		@param serviceName The name of the service */
		void serviceDependencyBecameUnavailable(Services serviceName);
};

#endif
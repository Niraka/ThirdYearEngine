/**
Manages the creation and storage of entities.

Entities are added to the game by inserting them in to groups. A pointer to these groups is then
provided to the Scene.

Note that the index of an entity is not synonymous with its id.

@author Nathan */

#ifndef ENTITY_MODULE_H
#define ENTITY_MODULE_H

#include <map>
#include <memory>

#include "Scene/Modules/Entity.h"
#include "Scene/Modules/EntityMap.h"
#include "Scene/Modules/EntityGroup.h"
#include "Scene/Modules/EntitySpecification.h"

#include "Scene/Modules/ActingModule.h"
#include "Scene/Modules/PhysicsModule.h"
#include "Scene/Modules/AIModule.h"
#include "System/Modules/CommandModule.h"
#include "System/Modules/WindowModule.h"
#include "System/Modules/AudioModule.h"
#include "System/Services/LoggerService.h"

#include "System/Framework/Module.h"
#include "System/Modules/Renderable.h"
#include "System/Utility/VectorInd.h"
#include "System/Utility/DirectoryListing.h"
#include "System/Utility/XMLDescriptor.h"

class EntityModule :
	public Module,
	public CommandListener,
	public Renderable,
	public SceneManagerListener
{
	private:
		const std::string m_sXMLDEEntitySpec;
		const std::string m_sXMLDEName;
		const std::string m_sXMLDEComponents;
		const std::string m_sXMLDEActor;
		const std::string m_sXMLDEPhysics;
		const std::string m_sXMLDEAI;
		const std::string m_sXMLDEAudio;
		const std::string m_sXMLDEComponentConfig;
		const std::string m_sXMLDEModelName;

		std::map<std::string, EntitySpecification> m_specifications;
		std::map<std::string, std::shared_ptr<EntityGroup>> m_entityGroups;
		VectorSim<std::shared_ptr<EntityGroup>> m_renderableGroups;
		VectorInd<std::shared_ptr<Entity>> m_entities;
		std::shared_ptr<CommandNode> m_commandNode;
		std::shared_ptr<WindowModule> m_windowModule;
		std::shared_ptr<ActingModule> m_actingModule;
		std::shared_ptr<AudioModule> m_audioModule;
		std::shared_ptr<PhysicsModule> m_physicsModule;
		std::shared_ptr<AIModule> m_aiModule;
		std::shared_ptr<LoggerNode> m_loggerNode;
		XMLDescriptor m_xmlDescriptor;
		StringUtils m_stringUtils;
		EntityMap m_map;

		bool m_bRememberSpec;

		void buildEntitySpec(std::string& sSpecName, EntitySpecification& spec, tinyxml2::XMLElement* e);

	protected:
		/**
		Updates the EntityModule. */
		void onUpdate();

	public:
		/**
		Constructs an EntityModule. */
		EntityModule();

		/**
		Destructs an EntityModule. */
		~EntityModule();

		/**
		Starts up the module.
		@return True if the module started up successfully, false otherwise */
		bool start();

		/**
		Stops the module.
		@return True if the module stopped successfully, false otherwise */
		bool stop();

		//////////////////////////////////////////////////////////

		bool addEntitySpecification(std::string sSpecName, EntitySpecification spec);
		bool loadEntitySpecifications(std::string sSpecFile);
		bool entitySpecificationExists(const std::string& sSpecName);
		bool removeEntitySpecification(std::string sSpecName);
		const EntitySpecification& getEntitySpecification(const std::string& sSpecName) const;

		unsigned int createEntity(const std::string& sSpecName, const std::string& sGroupName = "");
		unsigned int createEntity(const EntitySpecification& spec, const std::string& sGroupName = "");
		std::shared_ptr<Entity> getEntity(unsigned int uiEntityIndex);
		bool entityExists(unsigned int uiEntityIndex);
		bool deleteEntity(unsigned int uiEntityIndex);

		void addEntityToGroup(const std::string& sGroupName, unsigned int uiEntityIndex);
		void removeEntityFromGroup(const std::string& sGroupName, unsigned int uiEntityIndex);

		bool createEntityGroup(const std::string& sGroupName);
		bool entityGroupExists(const std::string& sGroupName);
		bool deleteEntityGroup(const std::string& sGroupName);

		void setEntityGroupRenderable(const std::string& sGroupName, bool bRenderable);

		void resetEntitySpecifications();
		void resetEntities();
		void resetAll();

		//////////////////////////////////////////////////////////

		/**
		This function is called when a module becomes available that is a dependency of this class. Note that
		the pointer is delivered as a void pointer and must first be cast to the correct module using a
		static pointer cast.
		@param moduleName The name of the module
		@param module A shared pointer to the new module */
		void moduleDependencyBecameAvailable(Modules moduleName, std::shared_ptr<void> module);

		/**
		This function is called when a module that is a dependency of this class becomes unavailable.
		@param moduleName The name of the module */
		void moduleDependencyBecameUnavailable(Modules moduleName);

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

		/**
		Called by the CommandModule when a command associated with the CommandNode this class is listening
		to is executed.
		@param sCommandName The name of the command
		@param args A vector of strings containing the command arguments */
		void onCommandReceived(std::string sCommandName, std::vector<std::string> args);

		/**
		Renders to the window. Use the shader manager to activate the correct shader.
		@param shaderManager A reference to the ShaderManager
		@param data Miscellaneous data that can be used for rendering calculations */
		void render(ShaderManager& shaderManager, const RenderData& data);

		/**
		This function is called whenever the active scene is changed.
		@param sNewScene The name of the new scene
		@param sOldScene The name of the old scene */
		void onSceneChanged(std::string sNewScene, std::string sOldScene);
};

#endif
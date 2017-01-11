#include "Scene/Modules/EntityModule.h"

EntityModule::EntityModule() :
m_sXMLDEEntitySpec("entity_spec"),
m_sXMLDEName("name"),
m_sXMLDEComponents("components"),
m_sXMLDEActor("actor"),
m_sXMLDEPhysics("physics"),
m_sXMLDEAudio("audio"),
m_sXMLDEComponentConfig("component_config"),
m_sXMLDEModelName("model_name")
{
	addModuleDependency(Modules::COMMAND);
	addModuleDependency(Modules::WINDOW);
	addModuleDependency(Modules::ACTING);
	addModuleDependency(Modules::RESOURCE);
	addModuleDependency(Modules::AUDIO);
	addModuleDependency(Modules::PHYSICS);
	addServiceDependency(Services::LOGGER);

	m_xmlDescriptor.addElement(m_sXMLDEEntitySpec);
	m_xmlDescriptor.addElement(m_sXMLDEName);
	m_xmlDescriptor.addElement(m_sXMLDEComponents);
	m_xmlDescriptor.addElement(m_sXMLDEActor);
	m_xmlDescriptor.addElement(m_sXMLDEPhysics);
	m_xmlDescriptor.addElement(m_sXMLDEAudio);
	m_xmlDescriptor.addElement(m_sXMLDEComponentConfig);
	m_xmlDescriptor.addElement(m_sXMLDEModelName);

	// Insert an unused entity at position 0 of the entities vector to reserve the 0 index. This index
	// is used to report "no index"
	m_entities.add(std::make_shared<Entity>());

	m_bRememberSpec = true;
}

EntityModule::~EntityModule()
{
}

void EntityModule::onUpdate()
{
}

bool EntityModule::addEntitySpecification(std::string sSpecName, EntitySpecification spec)
{
	if (!entitySpecificationExists(sSpecName))
	{
		m_specifications.emplace(sSpecName, spec);
		return true;
	}
	else
	{
		return false;
	}
}

void EntityModule::buildEntitySpec(std::string& sSpecName, EntitySpecification& spec, tinyxml2::XMLElement* e)
{
	// How this works:
	// 1) Step down one level
	// 2) Parse everything on that level until an element with children is found
	// 3) Repeat 1-2 until no more elements are found on all levels below the starting level
	tinyxml2::XMLElement* eCrnt = e->FirstChildElement();
	for (; eCrnt != nullptr; eCrnt = eCrnt->NextSiblingElement())
	{
		// Check if the element has child elements
		if (eCrnt->FirstChildElement() == nullptr)
		{
			std::string sName = eCrnt->Name();
			std::string sText = eCrnt->GetText();
			if (m_xmlDescriptor.hasElement(sName))
			{
				if (sName == m_sXMLDEName)
				{
					sSpecName = sText;
				}
				else if (sName == m_sXMLDEActor)
				{
					spec.bUseActor = m_stringUtils.toBool(sText);
				}
				else if (sName == m_sXMLDEPhysics)
				{
					spec.bUsePhysics = m_stringUtils.toBool(sText);
				}
				else if (sName == m_sXMLDEAudio)
				{
					spec.bUseAudio = m_stringUtils.toBool(sText);
				}
				else if (sName == m_sXMLDEModelName)
				{
					spec.sModelName = sText;
				}
			}
		}
		else
		{
			buildEntitySpec(sSpecName, spec, eCrnt);
		}
	}
}

bool EntityModule::loadEntitySpecifications(std::string sSpecFile)
{
	// Generate the full path and attempt to open the document
	std::string sFullPath = DirectoryListing::getInstance()->getDirectory("entities") + sSpecFile;
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError loadError = xmlDoc.LoadFile(sFullPath.c_str());
	if (loadError == tinyxml2::XMLError::XML_NO_ERROR)
	{
		// Cycle through and build each spec
		for (tinyxml2::XMLElement* e = xmlDoc.FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
		{
			if (e->Name() == m_sXMLDEEntitySpec)
			{
				std::string sSpecName;
				EntitySpecification spec;	
				buildEntitySpec(sSpecName, spec, e);
				if (!entitySpecificationExists(sSpecName))
				{
					m_specifications.emplace(sSpecName, spec);
				}				
			}
		}

		if (m_loggerNode)
		{
			m_loggerNode->log("Successfully loaded entity specifications");
		}

		return true;
	}
	else
	{
		if (m_loggerNode)
		{
			m_loggerNode->log("Failed to load entity specifications");
		}

		return false;
	}
}

bool EntityModule::removeEntitySpecification(std::string sSpecName)
{
	return m_specifications.erase(sSpecName) == 1;
}

bool EntityModule::entitySpecificationExists(const std::string& sSpecName)
{
	return m_specifications.find(sSpecName) != m_specifications.end();
}

const EntitySpecification& EntityModule::getEntitySpecification(const std::string& sSpecName) const
{
	return m_specifications.at(sSpecName);
}

unsigned int EntityModule::createEntity(const std::string& sSpecName, const std::string& sGroupName)
{
	if (entitySpecificationExists(sSpecName))
	{
		return createEntity(getEntitySpecification(sSpecName), sGroupName);
	}
	else
	{
		return 0;
	}
}

unsigned int EntityModule::createEntity(const EntitySpecification& spec, const std::string& sGroupName)
{
	std::shared_ptr<Entity> entity;
	if (m_bRememberSpec)
	{
		entity = std::make_shared<Entity>(spec);
	}
	else
	{
		entity = std::make_shared<Entity>();
	} 

	// Store the entity and add it to a group if required
	unsigned int uiIndex = m_entities.add(entity);
	entity->setIndex(uiIndex);
	addEntityToGroup(sGroupName, uiIndex);

	// Parse the specification and create the Entity as required
	if (spec.bUseActor && m_actingModule)
	{
		entity->attachActor(m_actingModule->createActor(spec.sModelName));
	}
	if (spec.bUsePhysics && m_physicsModule)
	{
		entity->attachPhysicsNode(m_physicsModule->createNode(
			std::to_string(uiIndex), 
			glm::vec3(1.0), 
			HitRegionTypes::HITBOX, 
			entity->getPosition(), 
			glm::vec3(0.0), 
			3.0, glm::vec3(0.0), 
			entity->getOrienation(), 
			glm::vec3(0.0), 
			true, 
			true));
	}
	if (spec.bUseAudio && m_audioModule)
	{
		entity->attachSoundNode(m_audioModule->createSoundNode());
	}

	m_map.addToken(entity->getEntityToken());

	return uiIndex;
}

std::shared_ptr<Entity> EntityModule::getEntity(unsigned int uiEntityIndex)
{
	return m_entities.get(uiEntityIndex);
}

bool EntityModule::entityExists(unsigned int uiEntityIndex)
{
	return m_entities.exists(uiEntityIndex);
}

bool EntityModule::deleteEntity(unsigned int uiEntityIndex)
{
	// Prevent deletion of index 0 - this is a reserved spot for indicating "no index"
	if (uiEntityIndex == 0)
	{
		return false;
	}
	else
	{
		m_map.removeToken(m_entities.get(uiEntityIndex)->getEntityToken());
		return m_entities.remove(uiEntityIndex);
	}
}

void EntityModule::addEntityToGroup(const std::string& sGroupName, unsigned int uiEntityIndex)
{
	if (sGroupName == "")
	{
		return;
	}

	if (entityExists(uiEntityIndex))
	{
		if (entityGroupExists(sGroupName))
		{
			m_entityGroups.at(sGroupName)->entities.add(m_entities.get(uiEntityIndex));
		}
		else
		{
			createEntityGroup(sGroupName);
			m_entityGroups.at(sGroupName)->entities.add(m_entities.get(uiEntityIndex));
		}
	}
}

void EntityModule::removeEntityFromGroup(const std::string& sGroupName, unsigned int uiEntityIndex)
{
	if (entityGroupExists(sGroupName))
	{
		m_entityGroups.at(sGroupName)->entities.remove(m_entities.get(uiEntityIndex));
	}
}

bool EntityModule::createEntityGroup(const std::string& sGroupName)
{
	if (sGroupName == "")
	{
		return false;
	}

	if (!entityGroupExists(sGroupName))
	{
		m_entityGroups.emplace(sGroupName, std::make_shared<EntityGroup>());
		return true;
	}
	else
	{
		return false;
	}
}

bool EntityModule::entityGroupExists(const std::string& sGroupName)
{
	return m_entityGroups.find(sGroupName) != m_entityGroups.end();
}

bool EntityModule::deleteEntityGroup(const std::string& sGroupName)
{
	if (entityGroupExists(sGroupName))
	{
		m_entityGroups.erase(sGroupName);
		return true;
	}
	else
	{
		return false;
	}
}

void EntityModule::setEntityGroupRenderable(const std::string& sGroupName, bool bRenderable)
{
	if (entityGroupExists(sGroupName))
	{
		if (bRenderable)
		{
			if (!m_renderableGroups.contains(m_entityGroups.at(sGroupName)))
			{
				m_renderableGroups.add(m_entityGroups.at(sGroupName));
			}
		}
		else
		{
			if (m_renderableGroups.contains(m_entityGroups.at(sGroupName)))
			{
				m_renderableGroups.remove(m_entityGroups.at(sGroupName));
			}
		}
	}
}

void EntityModule::resetEntitySpecifications()
{
	m_specifications.clear();
}

void EntityModule::resetEntities()
{
	m_entities.clear();
	for (std::pair<const std::string, std::shared_ptr<EntityGroup>> group : m_entityGroups)
	{
		group.second->entities.clear();
	}
	m_entities.add(std::make_shared<Entity>());
}

void EntityModule::resetAll()
{
	m_entities.clear();
	m_entityGroups.clear();
	m_specifications.clear();
	m_entities.add(std::make_shared<Entity>());
}

bool EntityModule::start()
{
	if (m_loggerNode)
	{
		m_loggerNode->log("Entity module launching");
	}

	if (m_loggerNode)
	{
		m_loggerNode->log("Entity module successfully launched");
	}
	return true;
}

bool EntityModule::stop()
{
	return true;
}

void EntityModule::moduleDependencyBecameAvailable(Modules moduleName, std::shared_ptr<void> module)
{
	if (moduleName == Modules::COMMAND)
	{
		std::shared_ptr<CommandModule> commandModule = std::static_pointer_cast<CommandModule>(module);
		if (commandModule)
		{
			m_commandNode = commandModule->createCommandNode();
			m_commandNode->addCommandListener(this);
		}
	}
	else if (moduleName == Modules::WINDOW)
	{
		std::shared_ptr<WindowModule> windowModule = std::static_pointer_cast<WindowModule>(module);
		if (windowModule)
		{
			m_windowModule = windowModule;
			m_windowModule->createShaders("multi_light");
			m_windowModule->createShaders("skybox");
			m_windowModule->addSceneManagerListener(this);
		}
	}
	else if (moduleName == Modules::PHYSICS)
	{
		m_physicsModule = std::static_pointer_cast<PhysicsModule>(module);
	}
	else if (moduleName == Modules::ACTING)
	{
		m_actingModule = std::static_pointer_cast<ActingModule>(module);
	}
	else if (moduleName == Modules::AUDIO)
	{
		m_audioModule = std::static_pointer_cast<AudioModule>(module);
	}
}

void EntityModule::moduleDependencyBecameUnavailable(Modules moduleName)
{
	if (moduleName == Modules::COMMAND)
	{
		m_commandNode = nullptr;
	}
	else if (moduleName == Modules::ACTING)
	{
		m_actingModule = nullptr;
		unsigned int uiCrnt = 0;
		unsigned int uiSize = m_entities.size();
		for (; uiCrnt < uiSize; ++uiCrnt)
		{
			m_entities.get(uiCrnt)->attachActor(nullptr);
		}
	}
	else if (moduleName == Modules::AUDIO)
	{
		m_audioModule = nullptr;
		unsigned int uiCrnt = 0;
		unsigned int uiSize = m_entities.size();
		for (; uiCrnt < uiSize; ++uiCrnt)
		{
			m_entities.get(uiCrnt)->attachSoundNode(nullptr);
		}
	}
	else if (moduleName == Modules::PHYSICS)
	{
		m_physicsModule = nullptr;
	}
}

void EntityModule::serviceDependencyBecameAvailable(Services serviceName, std::shared_ptr<void> service)
{
	if (serviceName == Services::LOGGER)
	{
		std::shared_ptr<LoggerService> logger = std::static_pointer_cast<LoggerService>(service);
		if (logger)
		{
			m_loggerNode = logger->createLoggerNode("EN");
		}
	}
}

void EntityModule::serviceDependencyBecameUnavailable(Services serviceName)
{
	if (serviceName == Services::LOGGER)
	{
		m_loggerNode = nullptr;
	}
}

void EntityModule::onCommandReceived(std::string sCommandName, std::vector<std::string> args)
{
}

void EntityModule::render(ShaderManager& shaderManager, const RenderData& data)
{
	shaderManager.activateShader("multi_light");
	
	unsigned int uiCrnt = 0;
	unsigned int uiSize = m_renderableGroups.size();
	unsigned int uiCrntGroup = 0;
	unsigned int uiSizeGroup = 0;
	for (; uiCrnt < uiSize; ++uiCrnt)
	{
		VectorSim<std::shared_ptr<Entity>>& entities = m_renderableGroups.at(uiCrnt)->entities;
		uiCrntGroup = 0;
		uiSizeGroup = entities.size();
		for (; uiCrntGroup < uiSizeGroup; ++uiCrntGroup)
		{
			entities.at(uiCrntGroup)->render(shaderManager, data);
		}
	}
}

void EntityModule::onSceneChanged(std::string sNewScene, std::string sOldScene)
{
	std::shared_ptr<Scene> oldScene = m_windowModule->getScene(sOldScene);
	if (oldScene)
	{
		oldScene->removeRenderable(this);
	}

	std::shared_ptr<Scene> newScene = m_windowModule->getScene(sNewScene);
	if (newScene)
	{
		newScene->addRenderable(this, 17, RenderModes::PER_CAMERA);
	}
}
#include "Scene/Modules/ActingModule.h"

ActingModule::ActingModule()
{
	addServiceDependency(Services::LOGGER);
}

ActingModule::~ActingModule()
{
}

void ActingModule::onUpdate()
{
}

bool ActingModule::start()
{	
	if (m_loggerNode)
	{
		m_loggerNode->log("Acting module launching..");
	}

	// Load some models for testing purposes
	//loadModelsFromFile("models.xml");

	if (m_loggerNode)
	{
		m_loggerNode->log("Acting module successfully launched");
	}
	return true;
}

bool ActingModule::stop()
{
	if (m_loggerNode)
	{
		m_loggerNode->log("Acting module shutting down..");
	}

	if (m_loggerNode)
	{
		m_loggerNode->log("Acting module successfully shut down");
	}
	m_loggerNode = nullptr;

	return true;
}

std::shared_ptr<Actor> ActingModule::createActor(std::string sModel)
{
	if (m_modelManager.modelExists(sModel))
	{
		std::shared_ptr<Actor> actor = std::make_shared<Actor>();
		actor->setModel(m_modelManager.getModel(sModel));
		return actor;
	}
	else
	{
		return nullptr;
	}
}

void ActingModule::loadModel(ModelInfo info)
{
	if (m_modelManager.createModel(info))
	{
		if (m_loggerNode)
		{
			m_loggerNode->log("Created model: " + info.sModelName);
		}
	}
	else
	{
		if (m_loggerNode)
		{
			m_loggerNode->log("Failed to create model: " + info.sModelName);
		}
	}
}

void ActingModule::loadModels(std::vector<ModelInfo> infos)
{
	for (ModelInfo& info : infos)
	{
		loadModel(info);
	}
}

void ActingModule::loadModelsFromFile(std::string sFile)
{
	std::vector<ModelInfo> infos;

	// Attempt to open the file
	tinyxml2::XMLDocument doc;
	std::string sFullPath = DirectoryListing::getInstance()->getDirectory("models") + sFile;
	int iLoadResult = doc.LoadFile(sFullPath.c_str());
	if (iLoadResult == tinyxml2::XML_NO_ERROR)
	{
		tinyxml2::XMLElement* eName = nullptr;
		tinyxml2::XMLElement* eMesh = nullptr;
		tinyxml2::XMLElement* eMaterial = nullptr;
		for (tinyxml2::XMLElement* e = doc.FirstChildElement("model"); e != nullptr; e = e->NextSiblingElement("model"))
		{
			// Grab the nodes
			eName = e->FirstChildElement("name");
			eMesh = e->FirstChildElement("mesh");
			eMaterial = e->FirstChildElement("material");

			// Extract model info from each element
			ModelInfo info;	
			if (eName)
			{
				info.sModelName = eName->GetText();
			}
			if (eMesh)
			{
				info.sMeshFile = eMesh->GetText();
			}
			if (eMaterial)
			{
				info.sMaterialLibrary = eMaterial->GetText();
			}

			// Deposit the info
			infos.push_back(info);
		}
	}
	else
	{
		if (m_loggerNode)
		{
			m_loggerNode->log("Failed to open model file :" + sFullPath);
		}
		return;
	}

	// Load the models
	if (infos.size() > 0)
	{
		loadModels(infos);
	}
}

void ActingModule::serviceDependencyBecameAvailable(Services serviceName, std::shared_ptr<void> service)
{
	if (serviceName == Services::LOGGER)
	{
		std::shared_ptr<LoggerService> logger = std::static_pointer_cast<LoggerService>(service);
		if (logger)
		{
			m_loggerNode = logger->createLoggerNode("AC");
		}
	}
}

void ActingModule::serviceDependencyBecameUnavailable(Services serviceName)
{
	if (serviceName == Services::LOGGER)
	{
		m_loggerNode = nullptr;
	}
}
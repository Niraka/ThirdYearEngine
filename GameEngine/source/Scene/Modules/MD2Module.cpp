#include "Scene\Modules\MD2Module.h"
#include "Scene\Modules\MD2Model.h"

MD2Module::MD2Module()
{
	addServiceDependency(Services::LOGGER);
}

MD2Module::~MD2Module()
{

}

bool MD2Module::start()
{
	if (m_loggerNode)
	{
		m_loggerNode->log("MD2 Module launching");
	}

	//Module startup actions

	if (m_loggerNode)
	{
		m_loggerNode->log("MD2 Module succesfully luanched");
	}
	return true;
}

bool MD2Module::stop()
{
	return true;
}

void MD2Module::render()
{
	std::map<std::string, MD2Model*>::iterator mapIt;

	for (mapIt = m_models.begin(); mapIt != m_models.end(); ++mapIt)
	{
		mapIt->second->render();
	}
}

void MD2Module::update()
{
	
}

void MD2Module::onUpdate()
{
	std::map<std::string, MD2Model*>::iterator mapIt;

	for (mapIt = m_models.begin(); mapIt != m_models.end(); ++mapIt)
	{
		mapIt->second->update();
	}
}

void MD2Module::moduleDependencyBecameAvailable(Modules moduleName, std::shared_ptr<void> module)
{

}

void MD2Module::serviceDependencyBecameAvailable(Services serviceName, std::shared_ptr<void> service)
{
	if (serviceName == Services::LOGGER)
	{
		std::shared_ptr<LoggerService> loggerService = std::static_pointer_cast<LoggerService>(service);
		if (loggerService)
		{
			m_loggerNode = loggerService->createLoggerNode("MD");
		}
	}
}

void MD2Module::moduleDependencyBecameUnavailable(Modules moduleName)
{
	
}

void MD2Module::serviceDependencyBecameUnavailable(Services serviceName)
{
	if (serviceName == Services::LOGGER)
	{
		m_loggerNode = nullptr;
	}
}

void MD2Module::createModel(std::string idName, const char modelFile)
{
	MD2Loader loader;
	MD2Model* newModel = new MD2Model;
	loader.load(&modelFile, &newModel->m_mdl);
	m_models.insert(std::pair<std::string, MD2Model*>(idName, newModel));
}
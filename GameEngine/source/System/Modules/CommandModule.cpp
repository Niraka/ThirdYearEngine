#include "System/Modules/CommandModule.h"

CommandModule::CommandModule()
{
	m_uiNextId = 0;
	setInputStream(&std::cin);
	addServiceDependency(Services::LOGGER);
}

CommandModule::~CommandModule()
{
	m_commandNodes.clear();
	m_bRunning = false;
}

void CommandModule::run()
{
	if (m_loggerNode)
	{
		m_loggerNode->log("Command module listening..");
	}

	while (m_bRunning)
	{
		// Check the validity of the input stream - default to std::cin
		// if there were any issues
		if (m_inputStream == nullptr)
		{
			m_inputStream = &std::cin;
		}

		// Wait for a command
		std::string s;
		getline(*m_inputStream, s);

		// Deposit the command
		m_mutex.lock();
		m_pendingCommands.push(s);
		m_mutex.unlock();
	}

	if (m_loggerNode)
	{
		m_loggerNode->log("Command module stopped..");
	}

	m_self = nullptr;
}

void CommandModule::setInputStream(std::istream* stream)
{
	if (stream != nullptr)
	{
		m_inputStream = stream;
	}
}

void CommandModule::interpretCommand(std::string& s)
{
	// Check the command is not empty
	if (s.empty())
	{
		return;
	}
	
	// Split the command in to name and arguments, using spaces as the splitter
	std::vector<std::string> data = m_stringUtils.splitString(s, ' ');
	std::string sName = data.at(0);
	data.erase(data.begin());
	unsigned int uiParamCount = data.size();
	bool bCommandRecognised = false;
	bool bCommandArgsRecognised = false;

	// Search for any command with the desired name and parameter count. There may be more than one
	for (const std::pair<unsigned int, CommandNodeInfo>& p : m_commandNodes)
	{
		std::map<std::string, std::set<unsigned int>>::const_iterator commandIterator = p.second.commandMappings.find(sName);
		if (commandIterator != p.second.commandMappings.end())
		{
			bCommandRecognised = true;
			std::set<unsigned int>::const_iterator paramIterator = commandIterator->second.find(uiParamCount);
			if (paramIterator != commandIterator->second.end())
			{
				p.second.node->receiveCommand(sName, data);
				bCommandArgsRecognised = true;
			}
		}
	}

	// Output some feedback
	if (!bCommandRecognised)
	{
		if (m_loggerNode)
		{
			m_loggerNode->log("Unknown command '" + sName + "'");
		}
	}
	else
	{
		if (!bCommandArgsRecognised)
		{
			if (m_loggerNode)
			{
				m_loggerNode->log("Command '" + sName + "' does not take " + std::to_string(uiParamCount) + " arguments");
			}
		}
	}	
}

void CommandModule::onUpdate()
{
	// Parse all waiting commands
	m_mutex.lock();
	std::string s;
	while (!m_pendingCommands.empty())
	{
		s = m_pendingCommands.front();
		m_pendingCommands.pop();

		interpretCommand(s);
	}
	m_mutex.unlock();
}

std::shared_ptr<CommandNode> CommandModule::createCommandNode()
{
	// Create a node, info object and id
	std::shared_ptr<CommandNode> node = std::make_shared<CommandNode>();
	unsigned int uiId = m_uiNextId;
	CommandNodeInfo info;

	// Configure the node so that it can communicate with the command module
	info.node = node;
	m_commandNodes.emplace(uiId, info);
	node->m_uiId = uiId;
	node->m_commandNodeListener = this;

	// Increment the id counter
	++m_uiNextId;

	return node;
}

bool CommandModule::start()
{
	if (m_loggerNode)
	{
		m_loggerNode->log("Command module launching");
	}
	m_bRunning = true;

	m_commandNode = createCommandNode();
	m_commandNode->addCommand("help", 0);
	m_commandNode->addCommandListener(this);

	// Store a self-pointer so that the threaded component of this module can hold itself in
	// memory until it has finished executing
	m_self = shared_from_this();
	std::thread thread = std::thread(&CommandModule::run, this);
	thread.detach();

	if (m_loggerNode)
	{
		m_loggerNode->log("Command module successfully launched");
	}
	return true;
}

bool CommandModule::stop()
{
	if (m_loggerNode)
	{
		m_loggerNode->log("Command module shutting down..");
	}

	m_bRunning = false;
	setInputStream(nullptr);
	m_commandNode = nullptr;

	if (m_loggerNode)
	{
		m_loggerNode->log("Command module successfully shut down");
	}
	m_loggerNode = nullptr;

	return true;
}

void CommandModule::onNodeDestruction(unsigned int uiId)
{
	// If a node with the given Id existed, remove its Id and command mappings
	if (m_commandNodes.find(uiId) != m_commandNodes.end())
	{
		m_commandNodes.erase(uiId);
	}
}

void CommandModule::onCommandAdded(unsigned int uiId, std::string sCommandName, unsigned int uiNumParams)
{
	// If a node with the given Id existed, add the command
	if (m_commandNodes.find(uiId) != m_commandNodes.end())
	{
		// Add the command name
		m_commandNodes.at(uiId).commandMappings.emplace(sCommandName, std::set<unsigned int>());

		// Add the command paramater count
		m_commandNodes.at(uiId).commandMappings.at(sCommandName).emplace(uiNumParams);
	}
}

void CommandModule::onCommandRemoved(unsigned int uiId, std::string sCommandName, unsigned int uiNumParams)
{
	// If a node with the given Id existed, find and remove the command
	if (m_commandNodes.find(uiId) != m_commandNodes.end())
	{
		// Check that the command exists within the node
		if (m_commandNodes.at(uiId).commandMappings.find(sCommandName) != m_commandNodes.at(uiId).commandMappings.end())
		{
			// If it did, remove the version with the correct parameter count
			m_commandNodes.at(uiId).commandMappings.at(sCommandName).erase(uiNumParams);
		}
	}
}

void CommandModule::onCommandReceived(std::string sCommandName, std::vector<std::string> args)
{
	if (sCommandName == "help")
	{
		if (m_loggerNode)
		{
			// Create a string over multiple lines that lists each of the available commands
			std::string s;
			s = "Available commands:";
			for (const std::pair<unsigned int, CommandNodeInfo>& p : m_commandNodes)
			{
				for (const std::pair<std::string, std::set<unsigned int>>& command : p.second.commandMappings)
				{
					s += "\n  " + command.first;
				}
			}
			m_loggerNode->log(s);
		}
	}
}

void CommandModule::serviceDependencyBecameAvailable(Services serviceName, std::shared_ptr<void> service)
{
	if (serviceName == Services::LOGGER)
	{
		std::shared_ptr<LoggerService> loggerService = std::static_pointer_cast<LoggerService>(service);
		if (loggerService)
		{
			m_loggerNode = loggerService->createLoggerNode("CO");
		}
	}
}

void CommandModule::serviceDependencyBecameUnavailable(Services serviceName)
{
	if (serviceName == Services::LOGGER)
	{
		m_loggerNode = nullptr;
	}
}
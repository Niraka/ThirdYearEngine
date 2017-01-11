#include "System/Modules/CommandNode.h"

CommandNode::CommandNode()
{
}

CommandNode::~CommandNode()
{
	if (m_commandNodeListener)
	{
		m_commandNodeListener->onNodeDestruction(m_uiId);
	}
}

void CommandNode::addCommandListener(CommandListener* l)
{
	m_commandListeners.add(l);
}

void CommandNode::removeCommandListener(CommandListener* l)
{
	m_commandListeners.remove(l);
}

void CommandNode::addCommand(std::string sCommandName, unsigned int uiNumParams)
{
	if (m_commandNodeListener)
	{
		m_commandNodeListener->onCommandAdded(m_uiId, sCommandName, uiNumParams);
	}
}

void CommandNode::removeCommand(std::string sCommandName, unsigned int uiNumParams)
{	
	if (m_commandNodeListener)
	{
		m_commandNodeListener->onCommandRemoved(m_uiId, sCommandName, uiNumParams);
	}
}

void CommandNode::receiveCommand(std::string sCommandName, std::vector<std::string> args)
{
	int iSize = m_commandListeners.size();
	for (int i = 0; i < iSize; ++i)
	{
		m_commandListeners.at(i)->onCommandReceived(sCommandName, args);
	}
}
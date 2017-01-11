/**
The information required to detail a CommandNode as stored on the CommandModule. The info
is used to determine whether a command exists on a node.

@author Nathan */

#ifndef COMMAND_NODE_INFO_H
#define COMMAND_NODE_INFO_H

#include <map>
#include <set>
#include <string>
#include <memory>

#include "System/Modules/CommandNode.h"

struct CommandNodeInfo
{
	std::shared_ptr<CommandNode> node;
	std::map<std::string, std::set<unsigned int>> commandMappings;
};

#endif
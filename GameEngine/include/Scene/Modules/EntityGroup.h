/**
An EntityGroup simply stores a group of Entities. 

@author Nathan */

#ifndef ENTITY_GROUP_H
#define ENTITY_GROUP_H

#include "System/Utility/VectorSim.h"
#include "Scene/Modules/Entity.h"

struct EntityGroup
{
	VectorSim<std::shared_ptr<Entity>> entities;
};

#endif
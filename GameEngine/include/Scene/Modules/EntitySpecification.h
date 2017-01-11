/**
An EntitySpecification stores details on how to construct a particular type of Entity.

The specification may be added to the EntityModule under a specific name, and from there on
may be referenced to build entities with this specification.

@author Nathan */

#ifndef ENTITY_INFO_H
#define ENTITY_INFO_H

#include <glm\glm.hpp>
#include <string>

struct EntitySpecification
{
	// Which components are enabled
	bool bUseActor;
	bool bUsePhysics;
	bool bUseAi;
	bool bUseAudio;

	// Configuration for those components
	std::string sModelName;

	EntitySpecification()
	{
		bUseActor = false;
		bUsePhysics = false;
		bUseAudio = false;
		bUseAi = false;
	}
};

#endif
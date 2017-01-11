/**
EntityFlags are a set of arbitrary flags that are attached to an Entity that define its
traits.

These traits can be used by other modules to perform actions on a specific set of entites. Note
that it is possible to have flags that seem to conflict with each other, as the way that the
flags are used are entirely up to the reader.

Example flags may include:
- IsMovable
- IsStructure
- IsBiological
- IsFlying

@author Nathan */

#ifndef ENTITY_FLAGS_H
#define ENTITY_FLAGS_H

struct EntityFlags
{
	enum Flags
	{
		IS_PLAYER,
		IS_NPC,
		IS_MOVABLE,
		IS_STRUCTURE,
		IS_BIOLOGICAL,
		CAN_EMIT_SOUND,
		CAN_EMIT_LIGHT,
		CAN_FLY
	};

	bool bIsPlayer;
	bool bIsNPC;
	bool bIsMovable;
	bool bIsStructure;
	bool bIsBiological;
	bool bCanEmitSound;
	bool bCanEmitLight;
	bool bCanFly;
};

#endif
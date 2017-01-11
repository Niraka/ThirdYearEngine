#include "Scene/Modules/EntityToken.h"

EntityToken::EntityToken()
{
	m_position = glm::vec3(0, 0, 0);
	m_scale = glm::vec3(1, 1, 1);
	m_orientation = glm::vec3(1, 1, 1);
}

EntityToken::~EntityToken()
{
}

void EntityToken::setFlag(EntityFlags::Flags flag, bool bValue)
{
	switch (flag)
	{
	case EntityFlags::IS_PLAYER:
		m_flags.bIsPlayer = bValue;
		break;
	case EntityFlags::IS_NPC:
		m_flags.bIsNPC = bValue;
		break;
	case EntityFlags::IS_MOVABLE:
		m_flags.bIsMovable = bValue;
		break;
	case EntityFlags::IS_STRUCTURE:
		m_flags.bIsStructure = bValue;
		break;
	case EntityFlags::IS_BIOLOGICAL:
		m_flags.bIsBiological = bValue;
		break;
	case EntityFlags::CAN_EMIT_SOUND:
		m_flags.bCanEmitSound = bValue;
		break;
	case EntityFlags::CAN_EMIT_LIGHT:
		m_flags.bCanEmitLight = bValue;
		break;
	case EntityFlags::CAN_FLY:
		m_flags.bCanFly = bValue;
		break;
	default:
		break;
	}
}

bool EntityToken::getFlag(EntityFlags::Flags flag)
{
	switch (flag)
	{
	case EntityFlags::IS_PLAYER:
		return m_flags.bIsPlayer;
	case EntityFlags::IS_NPC:
		return m_flags.bIsNPC;
	case EntityFlags::IS_MOVABLE:
		return m_flags.bIsMovable;
	case EntityFlags::IS_STRUCTURE:
		return m_flags.bIsStructure;
	case EntityFlags::IS_BIOLOGICAL:
		return m_flags.bIsBiological;
	case EntityFlags::CAN_EMIT_SOUND:
		return m_flags.bCanEmitSound;
	case EntityFlags::CAN_EMIT_LIGHT:
		return m_flags.bCanEmitLight;
	case EntityFlags::CAN_FLY:
		return m_flags.bCanFly;
	default:
		return false;
	}
}

const glm::vec3& EntityToken::getOrientation() const
{
	return m_orientation;
}

const glm::vec3& EntityToken::getPosition() const
{
	return m_position;
}

const glm::vec3& EntityToken::getScale() const
{
	return m_scale;
}

void EntityToken::setOrientation(glm::vec3 orientation)
{
	m_orientation = orientation;
}

void EntityToken::setPosition(glm::vec3 position)
{
	m_position = position;
}

void EntityToken::setScale(glm::vec3 scale)
{
	m_scale = scale;
}

void EntityToken::rotate(glm::vec3 rotation)
{
	m_orientation += rotation;
}

void EntityToken::move(glm::vec3 distance)
{
	m_position += distance;
}

void EntityToken::scale(glm::vec3 scale)
{
	m_scale += scale;
}
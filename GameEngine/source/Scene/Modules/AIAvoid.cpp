#include "Scene\Modules\AIAvoid.h"

AIAvoid::AIAvoid()
{


}

AIAvoid::~AIAvoid()
{


}

bool AIAvoid::start()
{
	if (b_avoid == true)
	{
		return true;
	}
}

bool AIAvoid::stop()
{
	return false;
}

void AIAvoid::initialise()
{
	
}

void AIAvoid::onUpdate(AIRequestedNode node)
{
	if (m_map->getNearestWithFlag(glm::vec3(0.0,0.0,0.0), EntityFlags::IS_NPC)->getPosition().length() ==
		m_map->getNearestWithFlag(glm::vec3(0.0, 0.0, 0.0), EntityFlags::IS_STRUCTURE)->getPosition().length() - 1)
	{
		node.rotate = glm::vec3(-1.0,0.0,0.0);
	}
		
}

float AIAvoid::getSpeed()
{
	return f_velocity;
}

void AIAvoid::setSpeed(float f_vel)
{
	f_velocity = f_vel;
}
#include "Scene\Modules\AISeek.h"

AISeek::AISeek()
{
	
}

AISeek::~AISeek()
{

}

bool AISeek::start()
{
	if (b_seek == true)
	{
		return true;
	}
}
bool AISeek::stop()
{
	return false;
}
void AISeek::initialise()
{

}

void AISeek::onUpdate(AIRequestedNode& node)
{
	if (b_seek == true)
	{
		glm::vec3 p_value; //player vec 3 position
		glm::vec3 e_value; //NPC enemy vec3 position

		for (EntityToken* it : m_token)
		{
			p_value = m_map->getNearestWithFlag(glm::vec3(0.0, 0.0, 0.0), EntityFlags::IS_PLAYER)->getPosition();
			e_value = m_map->getNearestWithFlag(glm::vec3(0.0, 0.0, 0.0), EntityFlags::IS_NPC)->getPosition();

		}
		glm::vec3 aiSeekdirection = glm::normalize(p_value - e_value);
		node.distance += aiSeekdirection * f_velocity;
	}
	
	
}

float AISeek::getSpeed()
{
	return f_velocity;
}

void AISeek::setSpeed(float f_vel)
{
	f_velocity = f_vel;
}


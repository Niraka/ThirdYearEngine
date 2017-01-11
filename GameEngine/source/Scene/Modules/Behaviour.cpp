#include "Scene\Modules\Behaviour.h"

Behaviour::Behaviour()
{
	b_wander = true;
	b_seek = false;
	b_avoid = false;

	f_velocity = 0.5f;
}

Behaviour::~Behaviour()
{

}

bool Behaviour::start()
{
	return true;
}
bool Behaviour::stop()
{
	return false;
}
void Behaviour::initialise()
{

}

void Behaviour::onUpdate(AIRequestedNode& node)
{

	
}

float Behaviour::getSpeed()
{
	return f_velocity;
}

void Behaviour::setSpeed(float f_vel)
{
	f_velocity = f_vel;
}



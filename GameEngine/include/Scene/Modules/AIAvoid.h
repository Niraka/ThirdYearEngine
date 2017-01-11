/**
The AI Avoid class is an ai state behaviour that allow the AI actors to avoid obstacles
like walls, or other objects while wandering or seeking

This class inherits from the behaviour class and its called real time in between states inorder to allow smooth
roaming

@author Austin */

#ifndef AIAVOID_H
#define AIAVOID_H

#include "Scene\Modules\Behaviour.h"
#include "Scene\Modules\EntityMap.h"
class AIAvoid : public Behaviour
{
private:
	EntityMap* m_map;
protected:
	
public:
	AIAvoid();
	~AIAvoid();

	void initialise();

	bool start();


	bool stop();


	//void reset();

	void onUpdate(AIRequestedNode node);

	float getSpeed();

	void setSpeed(float f_vel);
};
#endif
/**
The Behaviour class is the base class for all of the ai state behaviours,
it serves as a handler for each behaviour enabling smooth transition when switching
between states.

@author Austin */

#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include <iostream>
#include "Scene\Modules\AIRequestedNode.h"


class Behaviour
{
private:

protected:
	float f_velocity;

public:
	Behaviour();
	~Behaviour();
	bool b_wander;
	bool b_seek;
	bool b_avoid;
	
	enum m_Behaviours{WANDER, SEEK, AVOID};
	virtual void initialise();
	virtual bool start();
	virtual bool stop();
	//virtual void reset();
	virtual void onUpdate(AIRequestedNode& node);
	virtual float getSpeed();
	virtual void setSpeed(float f_vel);



};
#endif
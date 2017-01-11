/**
The AI Wander class is an ai state behaviour that allow the AI actors to free roam
the 3d world until they spot an object to chase or avoid

This class inherits from the behaviour class
roaming

@author Austin */
#ifndef AIWANDER_H
#define AIWANDER_H

#include "Scene\Modules\Behaviour.h"
#include "glm\glm.hpp"
#include "Scene\Modules\AIDirection.h"
#include "Scene\Modules\AIRequestedNode.h"

class AIWander : public Behaviour
{
private:

	AIDirection m_dir; //!<An object variable that enables access to the AIDirection Structure 
	


protected:
	glm::vec3 v_values; //!<A vec3 variable that stores the directional values based on the direction
	int i_direction;	//!<An integral variable that holds the direction of the movement
public:
	AIWander();
	~AIWander();

	/**
	Initialises variables */
	void initialise();

	/**
	Returns a boolean that starts the behaviour */
	bool start();

	/**
	Returns a boolean that stop the behaviour */
	bool stop();

	//void reset();

	/**
	Updates all the behaviours based on the requested node */
	void onUpdate(AIRequestedNode& node);

	/**
	Returns a random directional movement each time its called and sets the direction */
	void Wander();

	/**
	This returns a vector in an directional movement */
	glm::vec3 getMovement();

	/**
	This sets a point to any of the 8 directions 
	@param i_dir An inetgral value between 1-8 for directions
	@param b_check This accepts a boolean value of true or false inorder to flag the direction that is been set
	*/
	void setDirection(int i_dir, bool b_check);

	float getSpeed();
	void setSpeed(float f_vel);

	

};
#endif
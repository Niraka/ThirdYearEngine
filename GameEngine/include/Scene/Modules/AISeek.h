/**
The AI seek class is an ai state behaviour that allow the AI actors chase the player when its in its line of sight

This class inherits from the behaviour class and its called real time in between states inorder to allow smooth
roaming

@author Austin */
#ifndef AISEEK_H
#define AISEEK_H

#include "Scene\Modules\Behaviour.h"
#include "Scene\Modules\EntityToken.h"
#include "Scene\Modules\Entity.h"
#include "Scene\Modules\EntityMap.h"
#include <vector>

class AISeek : public Behaviour
{
private:
	std::vector<EntityToken*> m_token;
	Entity* m_entity;
	EntityMap* m_map;
protected:
	//!<Holds the directional speed of the entity
public:
	

	AISeek();
	~AISeek();

	void initialise();
	/**
	Returns a boolean that starts the behaviour */
	bool start();
	/**
	Updates all the behaviours based on the requested node */
	void onUpdate(AIRequestedNode& node);
	/**
	Returns a boolean that stop the behaviour */
	bool stop();
	//void reset();
	float getSpeed();
	void setSpeed(float f_vel);
};
#endif

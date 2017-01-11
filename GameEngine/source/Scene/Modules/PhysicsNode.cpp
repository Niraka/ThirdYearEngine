#include "Scene\Modules\PhysicsNode.h"
#include "Scene\Modules\HitBall.h"
#include "Scene\Modules\HitBoxOO.h"
#include "Scene\Modules\PhysicsListener.h"
#include "Scene\Modules\PhysicsModule.h"
#include "Scene\Modules\CollisionEvent.h"

PhysicsNode::PhysicsNode()
{
}

PhysicsNode::~PhysicsNode()
{
}

PhysicsNode::PhysicsNode(PhysicsModule* physMod, std::string name, glm::vec3 exts, HitRegionTypes regTyp, glm::vec3 pos, glm::vec3 vel, float maxSpd, glm::vec3 acc, glm::vec3 rot, glm::vec3 rotV, bool m, bool c)
{
	m_parentModule = physMod;
	m_idName = name;
	m_position = pos;
	m_velocity = vel;
	m_maxSpeed = maxSpd;
	m_acceleration = acc;
	m_moveable = m;
	m_collideable = c;
	m_rotation = rot;
	m_rotationalVel = rotV;

	this->addHitRegion(regTyp, pos, exts);
}

void PhysicsNode::setSize(glm::vec3 sz)
{
	m_hitBox->setSize(sz);
}

glm::vec3 PhysicsNode::getSize()
{
	return m_hitBox->getSize();
}


std::string PhysicsNode::getName()
{
	return m_idName;
}

void PhysicsNode::setPosition(glm::vec3 pos)
{
	pos.x = m_parentModule->m_mathsUtils.clamp(m_parentModule->getMinPos().x, m_parentModule->getMaxPos().x - 1, pos.x);
	pos.y = m_parentModule->m_mathsUtils.clamp(m_parentModule->getMinPos().y, m_parentModule->getMaxPos().y - 1, pos.y);		//Clamp XYZ value to whithin legal bounds, max allowed position is max - 1 to prevent cubegrid issues that would arise on objects at the absolute max position
	pos.z = m_parentModule->m_mathsUtils.clamp(m_parentModule->getMinPos().z, m_parentModule->getMaxPos().z - 1, pos.z);
	m_position = pos;
	m_hitBox->setCentre(pos);		//Move hitbox to match our new position
}


void PhysicsNode::setVelocity(glm::vec3 vel)
{
	vel.x = m_parentModule->m_mathsUtils.clamp(-m_maxSpeed, m_maxSpeed, vel.x);
	vel.y = m_parentModule->m_mathsUtils.clamp(-m_maxSpeed, m_maxSpeed, vel.y);
	vel.z = m_parentModule->m_mathsUtils.clamp(-m_maxSpeed, m_maxSpeed, vel.z);
	m_velocity = vel;
}


void PhysicsNode::setAcceleration(glm::vec3 acc)
{
	m_acceleration = acc;
}


glm::vec3 PhysicsNode::getPosition()
{
	return m_position;
}


glm::vec3 PhysicsNode::getVelocity()
{
	return m_velocity;
}


glm::vec3 PhysicsNode::getAcceleration()
{
	return m_acceleration;
}

glm::vec3 PhysicsNode::getRotation()
{
	return m_rotation;
}

void PhysicsNode::setRotation(glm::vec3 r)
{
	m_rotation = r;
	m_hitBox->setRotation(r);
}

glm::vec3 PhysicsNode::getRotationalVelocity()
{
	return m_rotationalVel;
}

void PhysicsNode::setRotationalVelocity(glm::vec3 rv)
{
	m_rotationalVel = rv;
}

void PhysicsNode::update(float dt)
{
	if (dt > 1)		//If more than a second has passed
	{
		dt = 1;		//Set dt to 1 second - useful when debugging
	}

	glm::vec3 oldPos = m_position;		//save the position we are currently at
	if (m_moveable)		//if this node can move
	{
		this->setPosition(m_velocity*dt);	//move in the direction of our velocity
		this->setVelocity(m_velocity += m_acceleration*dt);	//increase our velocity by our acceleration
		this->setRotation(m_rotation + m_rotationalVel*dt);	//increase rotation by our rotational velocity
	}
	if (m_collideable)	//if this node is currently able to collide
	{
		CollisionEvent cEvent = this->checkCollisions();
		if (cEvent.m_intersect)		//if we collided with anything
		{
			m_position = oldPos;		//put this node back to it's old position
			m_parentModule->m_loggerNode->log("Node: " + m_idName + " has had a collision with node: " + cEvent.m_collideWith->getParent()->getName());	//Log the collision
		}
		this->informCollision();
	}
	if (oldPos != m_position)		//if the position was updated
	{
		this->informMovement();		//inform the listeners
	}
	
}


bool PhysicsNode::checkMoveable()
{
	return m_moveable;
}

bool PhysicsNode::checkCollideable()
{
	return m_collideable;
}

void PhysicsNode::setMoveable(bool m)
{
	m_moveable = m;
}

void PhysicsNode::setCollideable(bool c)
{
	m_collideable = c;
}

void PhysicsNode::toggleMoveable()
{
	m_moveable = !m_moveable;
}

void PhysicsNode::toggleCollideable()
{
	m_collideable = !m_collideable;
}

void PhysicsNode::addHitRegion(HitRegionTypes typ, glm::vec3 cent, glm::vec3 sz, glm::vec3 rot)
{
	switch (typ)
	{
	case(HitRegionTypes::HITBALL):
	{
		std::shared_ptr<HitRegion> newBall = std::make_shared<HitBall>(this, cent, sz.x);
		m_hitBox = newBall;
							
		break;
	}
	case(HitRegionTypes::HITBOX):
	{
		std::shared_ptr<HitRegion> newBoxOO = std::make_shared<HitBoxOO>(this, cent, sz, rot);
		m_hitBox = newBoxOO;
		
		break;
	}

	}
}

std::shared_ptr<HitRegion> PhysicsNode::getHitRegion()
{
	return m_hitBox;
}

void PhysicsNode::informCollision()
{
	int i = 0;
	int iSize = m_listenerVec.size();

	for (; i < iSize; ++i)
	{
		m_listenerVec.at(i)->onCollision(m_idName);
	}
}

void PhysicsNode::informMovement()
{
	int i = 0;
	int iSize = m_listenerVec.size();

	for (; i < iSize; ++i)
	{
		m_listenerVec.at(i)->onPositionChanged(m_idName);
	}
}

void PhysicsNode::addListener(PhysicsListener* l)
{
	m_listenerVec.add(l);
}

void PhysicsNode::removeListener(PhysicsListener* l)
{
	m_listenerVec.remove(l);
}

CollisionEvent PhysicsNode::checkCollisions()
{
	VectorSim<std::shared_ptr<PhysicsNode>> checkNodes(m_parentModule->getReleventNodes(this));	//ask the physics module for all the relevant nodes
	
	CollisionEvent collEvent;

	int i = 0;
	int vecSize = checkNodes.size();
	for (; i < vecSize; ++i)	//iterate through the checking nodes
	{
		collEvent = (this->collide(checkNodes.at(i)));		//perform a collison check against each node
		if (collEvent.m_intersect)		//if a collison occured
		{
			return collEvent;		//if collision occured, return true;
		}
	}

	collEvent = CollisionEvent(false);		//No collision
	return collEvent;	//if the checking made no collisions, return false
}

CollisionEvent PhysicsNode::collide(std::shared_ptr<PhysicsNode> other)
{
	glm::vec3 unitDistVec = m_parentModule->m_mathsUtils.asUnit(other->getPosition() - m_position); //Get the unit vector from this to other
	if (m_parentModule->m_mathsUtils.dotProduct(m_velocity, unitDistVec) < 0)	//If this node is moving away from the other node
	{
		return CollisionEvent(false);	//Return false - no collision possible
	}

	return m_hitBox->collide(other->getHitRegion());
}
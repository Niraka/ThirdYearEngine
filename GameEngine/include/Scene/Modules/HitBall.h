#ifndef HITBALL_H
#define HITBALL_H

#include "Scene\Modules\HitRegion.h"

/*
@class HitBall
* A Spherical bounding region for representing an object's collison
* @author Wade
*/
class HitBall: public HitRegion
{
private:

protected:
	float m_radius;	//!< The radius of the sphere region

public:
	/**
	* Deafult constructor
	*/
	HitBall();		

	/**
	* Destructor
	*/
	~HitBall();

	/*
	* Construct a HitBall from given parameters
	@param c The centre co-ordinate of the new HitBall
	@param r The radius of the new HitBall
	*/
	HitBall(PhysicsNode* physNode, glm::vec3 c, float r);

	/**
	* Set the size (radius) of the hitball, not that only the X component is used
	@param sz A vector with X component equal to the desiered new radius
	*/
	void setSize(glm::vec3 sz);

	/**
	* Get the current size of the ball, note that even thoguh a vector is returned, only the x component is relevant
	@return A vector with X component equal to The radius of the ball */
	glm::vec3 getSize();

	/**
	Set the rotation of the hitball
	As rotating a ball makes no difference, this function currently does nothing
	*/
	void setRotation(glm::vec3 rot);

	/**
	Get the current rotation of the ball
	As rotating a ball makes no difference, this function currently always returns 0,0,0
	*/
	glm::vec3 getRotation();

	/**
	Perform a collision check with a generic HitRegionType
	@param other A shared pointer to the hitregion to test collisions with
	@return A collision event object with all relevant information about the collision
	*/
	CollisionEvent collide(std::shared_ptr<HitRegion> other);

	/**
	Perform a collision check with a HitBall
	@param other A shared pointer to the HitBall to test collisions with
	@return A collision event object with all relevant information about the collision
	*/
	CollisionEvent collide(std::shared_ptr<HitBall> other);

	/**
	Perform a collision check with a HitBoxOO
	@param other A shared pointer to the HitBoxOO to test collisions with
	@return A collision event object with all relevant information about the collision
	*/
	CollisionEvent collide(std::shared_ptr<HitBoxOO> other);

	/**
	Perform a collision check with a HitboxxOO of zero rotation - treating it as a AABB for easier calculation
	@param other A shared pointer to the hitregion to test collisions with
	@return A collision event object with all relevant information about the collision
	*/
	CollisionEvent collideWithAABB(std::shared_ptr<HitBoxOO> other);

};

#endif
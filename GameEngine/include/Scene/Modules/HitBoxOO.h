#ifndef HITBOXOO_H
#define HITBOXOO_H

#include "Scene\Modules\HitRegion.h"
/**
* @class HitBoxOO 
* A object-oriented bounding box
* @author Wade
*/
class HitBoxOO : public HitRegion
{
private:

protected:
	glm::vec3 m_extents;		//!< The X Y Z distance, from the centre, this hitbox extends to

	//NOTE: Always apply rotations in XYZ order, to undo, undo in ZYX order
	float m_XRotate;			//!< The rotation around the X axis for the box
	float m_YRotate;			//!< The rotation around the Y axis for the box
	float m_ZRotate;			//!< The rotation around the Z axis for the box

public:
	/*
	* Default Constructor
	*/
	HitBoxOO();

	/*
	* Destructor
	*/
	~HitBoxOO();

	/*
	* Construct a HitBoxOO with given parameters
	@param c The centre co-ordinate of the box
	@param e The extents of the box
	@param r The rotations of the box
	*/
	HitBoxOO(PhysicsNode* physNode, glm::vec3 c, glm::vec3 e, glm::vec3 r);

	/*
	* Get a vector with components equal to the xyz extents of the HitBoxOO
	@return Thge extents of the box
	*/
	glm::vec3 getSize();

	/**
	* Set the box to a new size
	@param sz The new vector extents of the box */
	void setSize(glm::vec3 sz);

	/*
	*Set the rotations of the box - completely overwrites exsiting values
	@param x The new X roation
	@param y The new Y rotation
	@param z The new Z rotation
	*/
	void setRotation(glm::vec3 rot);

	/*
	* Get the current XYZ rotations of the box
	@return A vector with components equal to the 3 rotations */
	glm::vec3 getRotation();

	/**
	Return the maximum of the three extents
	@return The value of the longest extent
	*/
	float getMax();

	/**
	Perform a collision check with a generic HitRegionType
	@param other A shared pointer to the hitregion to test collisions with
	@return A collision event object with all relevant information about the collision
	*/
	CollisionEvent collide(std::shared_ptr<HitRegion> other);

	/**
	Perform a collision check with a HitBall
	@param other A shared pointer to the Hitball to test collisions with
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
	Perform a collision check with a HitBoxOO, where both have zero rotation, so can be treated as AABB's to save calculation time
	@param other A shared pointer to the HitBoxOO to test collisions with
	@return A collision event object with all relevant information about the collision
	*/
	CollisionEvent collideAsTwoAA(std::shared_ptr<HitBoxOO> other);	
	
	/**
	Perform a collision check with a HitBall, where this box has zero rotation, so can be treated as an AABB
	@param other A shared pointer to the HitBall to test collisions with
	@return A collision event object with all relevant information about the collision
	*/
	CollisionEvent collideWithBallAsAA(std::shared_ptr<HitBall> other);	



};
#endif
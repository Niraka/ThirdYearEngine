#ifndef HITREGION_H
#define HITREGION_H

/*A generic bounding region to be inherited by all region types
* @author Wade
*/

#include <glm\glm.hpp>
#include <memory>
#include <vector>

class HitBall;
class HitBoxOO;
class PhysicsNode;
class CollisionEvent;

class HitRegion
{
private:

protected:
	glm::vec3 m_centre;			//!< The 3D co-ordinate of the centre of this hit region, relative to the node it belongs to
	bool m_active;				//!< Is this hitregion currently active?
	PhysicsNode* m_parentNode;	//!< Pointer to the node that created this hitregion

public:
	/**
	Construct a HitRegion */
	HitRegion();

	/**
	Destruct a Hitregion */
	~HitRegion();

	/**
	Set the centre of the hit region
	@param newCent The new centre of the hit region*/
	void setCentre(glm::vec3 newCent);


	/**
	Return the current centre of the hit region
	@return The centre co-ordinate of the hit region*/
	glm::vec3 getCentre();

	/**
	Return the current satte of this HitRegion
	@return The state of this hitregion, active or not*/
	bool getActive();

	/**
	Set the active state of this hitregion#
	@param act The new state of thie hitregion*/
	void setActive(bool act);

	/**
	Get a pointer to the physics node this hitregion belongs to
	@return A pointer to the physicsNode that created this hitregion
	*/
	PhysicsNode* getParent();

	/**
	Virtual function to be defined by each HitRegion type
	@param sz The vector of extents to set the HitRegion's size to*/
	virtual void setSize(glm::vec3 sz) = 0;

	/** 
	Virtual function to be defined by each HitRegion type
	@return The vector extents of the HitRegion */
	virtual glm::vec3 getSize() = 0;

	/**
	Virtual function to be defined in each HitRegion type
	Perform a collision check with a generic HitRegion Type
	@param other A shared pointer to the hitregion to test collisions with
	@return A collision event object with all relevant information about the collision
	*/
	virtual CollisionEvent collide(std::shared_ptr<HitRegion> other) = 0;

	/**
	Virtual function to be defined in each HitRegion type
	Perform a collision check with a HitBall
	@param other A shared pointer to the HitBall to test collisions with
	@return A collision event object with all relevant information about the collision
	*/
	virtual CollisionEvent collide(std::shared_ptr<HitBall> other) = 0;

	/**
	Virtual function to be defined in each HitRegion type
	Perform a collision check with aHitBoxOO
	@param other A shared pointer to the HitBoxOO to test collisions with
	@return A collision event object with all relevant information about the collision
	*/
	virtual CollisionEvent collide(std::shared_ptr<HitBoxOO> other) = 0;

	/**
	Virtual function to be defined in each HitRegion type
	Sets the rotation of the HitRegion
	@param rot The new vector of rotation
	*/
	virtual void setRotation(glm::vec3 rot) = 0;

	/**
	Virtual function to be defined in each HitRegion type
	Get the current rotation of the HitRegion
	@return The vector of rotation for the HitRegion
	*/
	virtual glm::vec3 getRotation() = 0;

	/**
	Tests a seperation axis for two HitRegions, to see if the axis seperates them
	@param testAxis The seperating axis to test
	@param pointsA A Vector of points that construct HitRegionA
	@param PointsB A Vector of points that construct HitRegionB
	@param CentreA The vector centre of HitRegionA
	@param CentreB The vector centre of HitRegionB
	*/
	bool testThisAxis(glm::vec4 testAxis, std::vector<glm::vec4> pointsA, std::vector<glm::vec4> pointsB, glm::vec3 centreA, glm::vec3 centreB);
};


#endif
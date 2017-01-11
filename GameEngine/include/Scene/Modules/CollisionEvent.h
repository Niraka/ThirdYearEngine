#ifndef COLLISIONEVENT_H
#define COLLISIONEVENT_H

#include <glm\glm.hpp>
#include <memory>

/**
@class CollisionEvent
* An object that is returned after a collision check
* It contains all the relevant infomation about the collision 
* @author Wade
*/

class HitRegion;

class CollisionEvent
{
	private:

	protected:

	public:
		/**
		* Default empty constructor
		*/
		CollisionEvent();
		/**
		* Destructor
		*/
		~CollisionEvent();
		/**
		* Construct a CollisionEvent with given parameters
		@param intersect whether the two objects being tested intersect
		@param unitNormal The unit vector of the collision normal - if a collision occured, otherwise defaults to 0,0,0
		@param depth The absolute depth of penatration that occured - if the objects collided - otherwise defaults to 0
		*/
		CollisionEvent(bool intersect, glm::vec4 unitNormal = glm::vec4(0,0,0,1), float depth = 0, std::shared_ptr<HitRegion> collideBox = nullptr);

		bool m_intersect; //<! Did a collision occur?
		glm::vec4 m_unitNormal;	//!< The unit vector of the collision normal - if a collision occured
		float m_depth;			//!< The absolute depth of penatration that occured - if the objects collided
		std::shared_ptr<HitRegion> m_collideWith;	//!< Pointer to the hitbox thatw as collided with, if any

};

#endif
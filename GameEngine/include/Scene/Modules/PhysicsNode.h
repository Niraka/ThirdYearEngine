/**
A physics node.

This class is currently only being used as a demonstration of componentism and will be fully
implemented as part of the PhysicsModule in assignment 2 if selected. 

@author Nathan + Wade */

#ifndef PHYSICS_NODE_H
#define PHYSICS_NODE_H

#include <glm\glm.hpp>
#include "Scene\Modules\HitRegion.h"
#include "System\Utility\VectorSim.h"
#include "Scene\Modules\Mesh.h"

#include <map>
#include <memory>

enum HitRegionTypes { HITBOX, HITBALL };

class PhysicsListener;
class PhysicsModule;

class PhysicsNode
{
	private:
		std::shared_ptr<HitRegion> m_hitBox;			//!<A pointer to the hitboxe to use for this node
		VectorSim<PhysicsListener*> m_listenerVec;		//!< Vector containing pointers to all listeners this node reports to

	protected:
		glm::vec3 m_position;						//!< Vector position of this node (central)
		glm::vec3 m_velocity;						//!< Vector velocity this node is moving at
		glm::vec3 m_acceleration;					//!< Vector acceleration to increase velocity by
		glm::vec3 m_rotation;						//!< Vector containing rotation about each axis (XYZ)
		glm::vec3 m_rotationalVel;					//!< Vector rotational velocity around each axis
		std::string m_idName;						//!< The uniques identification name to refer to this node by
		float m_maxSpeed;							//!< The maximum speed in any axis this node can travel at
		bool m_moveable;							//!< Can this node be moved?
		bool m_collideable;							//!< Does this node have active collisions?
		


	public:
		/**
		Constructs a default PhysicsNode. */
		PhysicsNode();

		/**
		Destructs a PhysicsNode. */
		~PhysicsNode();

		PhysicsModule* m_parentModule;				//!< Pointer to the commanding physics module

		/**
		Construct a PhysicsNode with given parameteres
		@param physMod Pointer to the physics module creating this node
		@param name The name for this module
		@param boundMesh The mesh this physicsNode is surrounding
		@param regTyp The type of hit box this node should use (Box or ball)
		@param pos The central position of this node
		@param vel The velocity of this node
		@param maxSpd The maximum speed of this node
		@param acc The acceleration of this node
		@param rot The rotation of this node
		@param rotV The rotational velocity of this node
		@param m The moveable state of this node
		@param c The collideable state of this node
		*/
		PhysicsNode(PhysicsModule* physMod, std::string name, glm::vec3 exts, HitRegionTypes regTyp, glm::vec3 pos, glm::vec3 vel, float maxSpd, glm::vec3 acc, glm::vec3 rot, glm::vec3 rotV, bool m, bool c);


		/**
		Get the name of this node
		@return The name of the module as a string
		*/
		std::string getName();

		/**
		Sets the position of the PhysicsNode.
		@param pos The position */
		void setPosition(glm::vec3 pos);

		/**
		Sets the velocity of the PysicsNode
		@param vel The new Velocity	*/
		void setVelocity(glm::vec3 vel);

		/**
		Sets the acceleration of the PhysicsNode
		@param acc The new acceleration	*/
		void setAcceleration(glm::vec3 acc);

		/**
		Get the current position of the physicsNode
		@return The position of this Node */
		glm::vec3 getPosition();

		/**
		Get the current velocity of the PhysicsNode
		@return The velocity of the node */
		glm::vec3 getVelocity();

		/**
		Get the current acceleration of the PhyscisNode
		@return The acceleration of the node */
		glm::vec3 getAcceleration();

		/**
		Get the current rotation about XYZ of this object
		@return The rotation about each axis as a vector
		*/
		glm::vec3 getRotation();

		/**
		Set the rotation to a new value
		@param r The enw rotation to set this node to
		*/
		void setRotation(glm::vec3 r);

		/**
		Get the current rotation velocity, as vector
		@param a vector with components equal to the three rotations
		*/
		glm::vec3 getRotationalVelocity();

		/**
		Set the rotational velocity to a new value
		@param rv The new velocity to set this node to
		*/
		void setRotationalVelocity(glm::vec3 rv);


		/**
		Set the size of the hitbox this physicsNode contains
		@param sz The new extents of the hitregion this node contains*/
		void setSize(glm::vec3 sz);

		/**
		Get the current extents of the hitbox this contains
		@return The extents of the hitregion of this node*/
		glm::vec3 getSize();

		/**
		Update the velocity and position based on current acceleration and velocity
		@param dt The time in seconds since last update */
		void update(float dt);

		/*Get the current moveable state
		@return The current moveable state of this node*/
		bool checkMoveable();

		/*Get the current collideable state
		@return The current collideable state of this node*/
		bool checkCollideable();
		
		/*Set the current moveable state to an explicit value
		@param m The new state of moveable*/
		void setMoveable(bool m);

		/*Set the current Collideable State to an explicit value
		@param c The new state of Collideable*/
		void setCollideable(bool c);

		/*Toggles Moveable to the opposite of the current state*/
		void toggleMoveable();
		
		/*Toggles Collideable to the opposite of the current state*/
		void toggleCollideable();

		/**
		Add a new hitbox to this Node		
		@param typ The type of region to make (BALL, AABOX, or OOBOX)
		@param cent The centre for the hitregion, relative to the node
		@param sz The size of the region, for boxes, this vector will become the extents, for spheres, only the x component is used as the radius
		@param rot The rotation of the region, only used for OOBoxes, defaults to 0,0,0
		@param */		
		void addHitRegion(HitRegionTypes typ, glm::vec3 cent, glm::vec3 sz, glm::vec3 rot = glm::vec3(0,0,0));

		/* Get a shared_ptr to the hitregion*/
		std::shared_ptr<HitRegion>getHitRegion();

		/**
		Inform all listeners that a collison has occured
		*/
		void informCollision();

		/**
		Inform all listeners that movement has occured
		*/
		void informMovement();

		/**
		Register a new listener to this node, this listener will then be informed when an event occurs to this node
		@param l A pointer to the listener to add
		*/
		void addListener(PhysicsListener* l);

		/**
		Remove a listener from this node
		@param l A pointer to the listener to remove
		*/
		void removeListener(PhysicsListener* l);

		/**
		Asks the PhysicsModule for relevant nodes and checks our collision with all of them
		@return A collision event to the collided item, or a false item if no collison occured
		*/
		CollisionEvent checkCollisions();
		
		/*Check collisions between this node and other
		@return true if their hitboxes collide*/
		CollisionEvent collide(std::shared_ptr<PhysicsNode> other);

		
};

#endif
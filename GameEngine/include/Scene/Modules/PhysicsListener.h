#ifndef PHYSICSLISTENER_H
#define PHYSICSLISTENER_H

/*
@class PhysicsListener
* A class that is informed by physics nodes when a collision occurs to the relevant node
*@author Wade
*/
#include <memory>
#include <string>

class PhysicsNode;

class PhysicsListener
{
	private:

	protected:

	public:
		/**
		Construct a PhysicsListener
		*/
		PhysicsListener();

		/**
		Destruct a PhysicsListener */
		~PhysicsListener();

		/**
		Perform actions based on the collision
		@param nodeName The name of the physics node that had a collision
		*/
		virtual void onCollision(std::string nodeName) = 0;
		
		/**
		Perform actions based on the movement
		@param nodeName The name of the physics node that has moved
		*/
		virtual void onPositionChanged(std::string nodeName) = 0;

		/**
		Register this to the given node
		@param listenNode A shared pointer to the node this listener wants to listen to
		*/
		void registerMe(std::shared_ptr<PhysicsNode> listenNode);
};

#endif
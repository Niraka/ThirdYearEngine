/**
An AI requested node class.


@author Austin */
#ifndef AI_REQUESTED_NODE_H
#define AI_REQUESTED_NODE_H

#include "glm\glm.hpp"

class AIRequestedNode 
{
	private:

	protected:
	
	public:
		AIRequestedNode();//!<Default Constructor
		~AIRequestedNode();

		glm::vec3 distance;//!<Stores and acts as a parser for the AI entity directional movement
		glm::vec3 rotate;//!<Stores and acts as a parser for the AI entity rotational movement
};
#endif
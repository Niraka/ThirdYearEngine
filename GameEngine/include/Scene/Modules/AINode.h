/**
An AI node.

A class that creates ai nodes that are then passed to the Entity class

@author Austin */

#ifndef AI_NODE_H
#define AI_NODE_H

#include <memory>
#include <vector>
#include "Scene\Modules\Behaviour.h"
#include "Scene/Modules/AIRequestedNode.h"
#include "glm\glm.hpp"



class AINode
{
	private:
		std::vector<std::shared_ptr<Behaviour>> m_behaviours;//!<Vector to hold all the AI Behaviours
	

	protected:
		glm::vec3 m_position;//!<Holds the position of the AI Node

	public:
		AINode();
		~AINode();

		/**
		Sets the position of the AI Node 
		@param position The position of the AI node*/
		void setPosition(glm::vec3 position);

		/**
		Adds an AI Behaviour to the AINode 
		@param AIb The behaviour state to add*/
		void addAIBehaviour(Behaviour::m_Behaviours AIb);

		void initialiseAIBehaviour();
		/**
		removes an AI Behaviour
		@param AIb The behaviour state to remove*/
		void removeAIBehaviour(Behaviour::m_Behaviours AIb);
		/**
		Function that starts the current AI behaviour */
		void startAIBehaviour();
		/**
		Function that terminates the current AI behaviour */
		void stopAIBehaviour();
		/**
		Returns an AI requested node that is then been sent to the entity class */
		AIRequestedNode processAI();

		/**
		Gets the position of the AI Node */
		glm::vec3 getPosition();
};

#endif
/**
An EntityMap stores a collection of EntityTokens.

@author Nathan */

#ifndef ENTITY_MAP_H
#define ENTITY_MAP_H

#include <vector>
#include "Scene/Modules/EntityToken.h"
#include "System/Utility/MathsUtils.h"

class EntityMap
{
	private:
		MathsUtils m_mathsUtils;
		std::vector<EntityToken*> m_tokens;

	protected:
		int i;
	public:
		/**
		Constructs an EntityMap. */
		EntityMap();

		/**
		Destructs the EntityMap. */
		~EntityMap();

		/**
		Adds a token to the map. This function should ONLY be called by the EntityModule.
		@param token The token to add */
		void addToken(EntityToken* token);

		/**
		Removes a token from the map.
		@param token The token to remove */
		void removeToken(EntityToken* token);

		EntityToken* getEntityToken();
		/**
		Returns a pointer to the nearest EntityToken to the given point. Returns a nullptr
		if there were no entities.
		@param position The position of the point 
		@return A pointer to an EntityToken, or a nullptr */
		const EntityToken* getNearest(glm::vec3 position);

		/**
		Returns a pointer to the nearest EntityToken to the given point that also has the desired flag.
		Returns a nullptr if there were no entites. 
		@param position The position of the point
		@param flag The required flag
		@return A pointer to an EntityToken, or a nullptr */
		const EntityToken* getNearestWithFlag(glm::vec3 position, EntityFlags::Flags flag);
};

#endif
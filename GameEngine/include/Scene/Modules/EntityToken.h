/**
EntityTokens store information about an Entity.

Tokens are stored on an EntityMap, an object whose purpose is purely to avoid
cyclical inclusion.

@author Nathan */

#ifndef ENTITY_TOKEN_H
#define ENTITY_TOKEN_H

#include "Scene/Modules/EntityFlags.h"
#include <glm\glm.hpp>

class EntityToken
{
	// Make the setter functions private and have the Entity in complete
	// control of setting them. This prevents de-sync from misuse of this
	// class's intended purpose
	friend class Entity;

	private:
		EntityFlags m_flags;
		glm::vec3 m_position;
		glm::vec3 m_scale;
		glm::vec3 m_orientation;

		/**
		Sets the value of an EntityFlag to the given value.
		@param flag The flag to set
		@param bValue The value to assign to the flag */
		void setFlag(EntityFlags::Flags flag, bool bValue);

		/**
		Sets the absolute orientation.
		@param orientation The orientation */
		void setOrientation(glm::vec3 orientation);

		/**
		Sets the absolute position.
		@param position The position */
		void setPosition(glm::vec3 position);

		/**
		Sets the absolute scale.
		@param scale The scale */
		void setScale(glm::vec3 scale);

		/**
		Rotates the Entity relative to its current orientation. 
		@param rotation The rotation to apply */
		void rotate(glm::vec3 rotation);

		/**
		Moves the Entity relative to its current position. 
		@param distance The distance to move */
		void move(glm::vec3 distance);

		/**
		Scales the Entity relative to its current scale.
		@param scale The scale to apply */
		void scale(glm::vec3 scale);

	protected:

	public:
		EntityToken();
		~EntityToken();

		/**
		Gets the value of an EntityFlag. 
		@param flag The flag to read
		@return The value of the desired EntityFlag */
		bool getFlag(EntityFlags::Flags flag);

		/**
		Gets the orientation.
		@return The orientation */
		const glm::vec3& getOrientation() const;

		/**
		Gets the position. 
		@return The position */
		const glm::vec3& getPosition() const;

		/**
		Gets the scale.
		@return The scale */
		const glm::vec3& getScale() const;
};

#endif
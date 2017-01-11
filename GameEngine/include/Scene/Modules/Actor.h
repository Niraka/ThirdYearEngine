/**
An Actor is the combination a pointer to a model and a set of transformation
data.

For example: A forest may contain 10 Actors that all point to the same Model,
but utilise different position, rotation and scaling data.

@author Nathan */

#ifndef ACTOR_H
#define ACTOR_H

#include <memory>
#include <glm\glm.hpp>

#include "Scene/Modules/Model.h"
#include "System/Modules/Renderable.h"

class Actor :
	public Renderable
{
	private:
		static const glm::vec3 m_worldX;
		static const glm::vec3 m_worldY;
		static const glm::vec3 m_worldZ;

		std::shared_ptr<Model> m_model;
		glm::vec3 m_position;
		glm::vec3 m_scale;
		glm::vec3 m_orientation;
		glm::mat4 m_modelMatrix;
		bool m_bVisible;

		void buildModelMatrix();

	protected:

	public:
		/**
		Creates a default Actor. */
		Actor();

		/**
		Creates an Actor using the given model. 
		@param model A shared pointer to the desired model */
		Actor(std::shared_ptr<Model> model);

		/**
		Destructs an Actor. */
		~Actor();

		/**
		Updates all animations playing on this Actor. */
		void updateAnimations();

		/**
		Sets the visibility of the Actor. 
		@param bVisible True to make the Actor visible */
		void setVisible(bool bVisible);

		/**
		Returns the visibility of the Actor. 
		@return True if the Actor is visible, false otherwise */
		bool isVisible() const;

		/**
		Moves the Actor relative to its current position. 
		@param distance The distance to move */
		void move(glm::vec3 distance);

		/**
		Sets the absolute position of the Actor. 
		@param pos The position of the Actor */
		void setPosition(const glm::vec3& pos);

		/**
		Retrieves the position of the Actor.
		@return The position of the Actor */
		glm::vec3 getPosition() const;

		/**
		Scales the Actor relative to its current scale.
		@param scale The scale to apply */
		void scale(glm::vec3 scale);

		/**
		Sets the absolute scale of the Actor. 
		@param scale The scale of the Actor */
		void setScale(glm::vec3 scale);

		/**
		Retrieves the scale of the Actor. 
		@return The scale of the Actor */
		glm::vec3 getScale() const;

		/**
		Rotates the Actor relative to its current orientation. 
		@param rotation The rotation to apply */
		void rotate(glm::vec3 rotation);

		/**
		Sets the absolute orientation of the Actor. 
		@param orientation The orientation of the Actor */
		void setOrientation(glm::vec3 orientation);

		/**
		Retrieves the orientation of the Actor. 
		@return The orientation of the Actor */
		glm::vec3 getOrienation() const;

		/**
		Sets the Model this Actor is using. Setting this value to a nullptr will remove the
		current Model.
		@param model A shared pointer to the desired Model */
		void setModel(std::shared_ptr<Model> model);
		
		/**
		Renders to the window. Use the shader manager to activate the correct shader.
		@param shaderManager A reference to the ShaderManager
		@param data Miscellaneous data that can be used for rendering calculations */
		void render(ShaderManager& shaderManager, const RenderData& data);
};

#endif
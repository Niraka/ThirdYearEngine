/**
A point light. 

A point light emits light in all directions from the specified position.

@author Nathan */

#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "System/Modules/Light.h"

class PointLight :
	public Light
{
	private:
		static const std::string m_sPrefix;
		static const std::string m_sColourSuffix;
		static const std::string m_sPositionSuffix;
		glm::vec3 m_position;

	protected:
	public:
		/**
		Constructs a PointLight. */
		PointLight();

		/**
		Constructs a PointLight with the given colour.
		@param rgb The colour */
		PointLight(glm::vec3 rgb);

		/**
		Destructs a PointLight. */
		~PointLight();

		/**
		Sets the position of the light. 
		@param pos The position */
		void setPosition(glm::vec3 pos);

		/**
		Posts the lights configuration to the given shader. If the given shader was a nullptr,
		this function does nothing.
		@param shader A pointer to the shader to post to
		@param sTargIndex The target light index, as a string */
		void postConfigToShader(Shader* shader, const std::string& sTargIndex);
};

#endif
/**
An Ambient light.

Ambient lights emit their light absolutely everywhere. They are not restricted by position
or direction.

Keep in mind that ambient lights can very easily drown out other light if there are multiple
in use at once.

@author Nathan */

#ifndef AMBIENT_LIGHT_H
#define AMBIENT_LIGHT_H

#include "System/Modules/Light.h"

class AmbientLight :
	public Light
{
	private:
		static const std::string m_sPrefix;
		static const std::string m_sColourSuffix;

	protected:

	public:
		/**
		Constructs an AmbientLight. */
		AmbientLight();

		/**
		Constructs an AmbientLight with the given colour.
		@param rgb The colour */
		AmbientLight(glm::vec3 rgb);

		/**
		Destructs a AmbientLight. */
		~AmbientLight(); 
		
		/**
		Posts the lights configuration to the given shader. If the given shader was a nullptr,
		this function does nothing. 
		@param shader A pointer to the shader to post to
		@param sTargIndex The target light index, as a string */
		void postConfigToShader(Shader* shader, const std::string& sTargIndex);
};

#endif
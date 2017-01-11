/**
A SpotLight. 

A spotlight creates a focused light in a target direction.

@author Nathan */

#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "System/Modules/Light.h"
#include "System/Modules/SpotLightStyles.h"

class SpotLight :
	public Light
{
	private:
		static const std::string m_sPrefix;
		static const std::string m_sColourSuffix;
		static const std::string m_sPositionSuffix;
		static const std::string m_sFacingPositionSuffix;
		static const std::string m_sConeAngleSuffix;

		float m_fConeAngle;
		glm::vec3 m_position;
		glm::vec3 m_facingPosition;
		SpotLightStyle m_style;


	protected:
	
	public:
		/**
		Constructs a SpotLight. */
		SpotLight();

		/**
		Constructs a SpotLight with the given colour.
		@param rgb The colour */
		SpotLight(glm::vec3 rgb);

		/**
		Destructs a SpotLight. */
		~SpotLight();

		/**
		Sets the position of the light. 
		@param pos The position of the light */
		void setPosition(glm::vec3 pos);

		/**
		Sets the position that the light is facing. This is used in conjunction with the current
		position to determine light direction. 
		@param pos The position of the light */
		void setFacingPosition(glm::vec3 pos);

		/**
		Sets the spot light cone angle in degrees. By default this value is 90. This value must be
		between 10 and 170 degrees (inclusive).
		@param fAngle The angle, in degrees */
		void setConeAngle(float fAngle);

		/**
		Sets the spot light style. Defaults to CIRCLE_COSINE. 
		@param style The falloff style to use */
		void setStyle(SpotLightStyle style);

		/**
		Returns the position of the spot light. 
		@return The position */
		glm::vec3 getPosition() const;

		/**
		Returns the position this spot light is facing. 
		@return The facing position */
		glm::vec3 getFacingPosition() const;

		/**
		Gets the cones angle, in degrees 
		@return The cones angle */
		float getConeAngle() const;

		/**
		Gets the style. 
		@return The style */
		SpotLightStyle getStyle() const;

		/**
		Posts the lights configuration to the given shader. If the given shader was a nullptr,
		this function does nothing.
		@param shader A pointer to the shader to post to
		@param sTargIndex The target light index, as a string */
		void postConfigToShader(Shader* shader, const std::string& sTargIndex);
};

#endif
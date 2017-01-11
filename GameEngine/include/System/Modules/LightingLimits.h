/**
The LightingLimits defines the limitations of the lighting shaders used by this 
engine.

The main purpose of this class is to reduce the presence of magic numbers.

@author Nathan */

#ifndef LIGHTING_LIMITS_H
#define LIGHTING_LIMITS_H

class LightingLimits
{
	private:
		const unsigned int m_uiMaxAmbientLights = 3;
		const unsigned int m_uiMaxPointLights = 10;
		const unsigned int m_uiMaxSpotLights = 10;

	protected:

	public:
		/**
		Returns the maximum number of ambient lights supported by the engine. 
		@return The maximum number of ambient lights */
		unsigned int getMaxAmbientLights() const;
		
		/**
		Returns the maximum number of point lights supported by the engine. 
		@return The maximum number of point lights */
		unsigned int getMaxPointLights() const;
		
		/**
		Returns the maximum number of spot lights supported by the engine. 
		@return The maximum number of spot lights */
		unsigned int getMaxSpotLights() const;
};

#endif
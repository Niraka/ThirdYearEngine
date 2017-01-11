/**
The base class for a Light.

@author Nathan */

#ifndef LIGHT_H
#define LIGHT_H

#include <glm\glm.hpp>
#include "System/Modules/Shader.h"
#include "System/Modules/LightListener.h"
#include "System/Utility/VectorSim.h"
#include "System/Utility/MathsUtils.h"
#include "System/Utility/HasId.h"
#include "System/Utility/HasModificationFlag.h"

class Light :
	public HasId<int>,
	public HasModificationFlag
{
	private:
		MathsUtils m_mathsUtils;
		VectorSim<LightListener*> m_lightListeners;
		bool m_bEnabled;
		glm::vec3 m_rgb;

	protected:
		/**
		Constructs a Light. */
		Light();
		/**
		Destructs a Light. */
		~Light();

	public:
		void removeLightListener(LightListener* l);
		void addLightListener(LightListener* l);

		/**
		Sets the RGB colour of the light. Values should be specified in the
		0-1 region. Values exceeding this bracket are clamped to the nearest
		boundary instead.
		@param rgb The colour */
		void setColour(glm::vec3 rgb);

		/**
		Returns the colour. Values are in the 0-1 region.
		@return The colour */
		glm::vec3 getColour() const;

		/**
		Enables or disables the light.
		@param True to enable, false to disable */
		void setEnabled(bool bEnabled);

		/**
		Returns the enabled state of the light.
		@return True if the light is enabled, false otherwise */
		bool isEnabled() const;

		/**
		Posts the lights configuration to the given shader. If the given shader was a nullptr,
		this function does nothing.
		@param shader A pointer to the shader to post to
		@param sTargIndex The target light index, as a string */
		virtual void postConfigToShader(Shader* shader, const std::string& sTargIndex) = 0;
};

#endif
#include "System/Modules/Light.h"

Light::Light()
{
	m_bEnabled = false;
	m_rgb = glm::vec3(0.f);
}

Light::~Light()
{
}

void Light::setEnabled(bool bEnabled)
{
	if (bEnabled && !m_bEnabled)
	{
		m_bEnabled = bEnabled;

		unsigned int uiCrnt = 0;
		unsigned int uiSize = m_lightListeners.size();
		for (; uiCrnt < uiSize; ++uiCrnt)
		{
			m_lightListeners.at(uiCrnt)->onLightEnabled(getId());
		}
	}
	else if (!bEnabled && m_bEnabled)
	{
		m_bEnabled = bEnabled;

		unsigned int uiCrnt = 0;
		unsigned int uiSize = m_lightListeners.size();
		for (; uiCrnt < uiSize; ++uiCrnt)
		{
			m_lightListeners.at(uiCrnt)->onLightDisabled(getId());
		}
	}
}

bool Light::isEnabled() const
{
	return m_bEnabled;
}

void Light::setColour(glm::vec3 rgb)
{
	// Clamp the values between 0 and 1
	rgb.r = m_mathsUtils.clamp(0.f, 1.f, rgb.r);
	rgb.g = m_mathsUtils.clamp(0.f, 1.f, rgb.g);
	rgb.b = m_mathsUtils.clamp(0.f, 1.f, rgb.b);
	
	m_rgb = rgb;

	m_bModifiedFlag = true;
}

glm::vec3 Light::getColour() const
{
	return m_rgb;
}

void Light::removeLightListener(LightListener* l)
{
	m_lightListeners.remove(l);
}

void Light::addLightListener(LightListener* l)
{
	m_lightListeners.add(l);
}
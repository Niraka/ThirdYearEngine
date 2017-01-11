#include "System/Modules/LightingLimits.h"

unsigned int LightingLimits::getMaxAmbientLights() const
{
	return m_uiMaxAmbientLights;
}

unsigned int LightingLimits::getMaxPointLights() const
{
	return m_uiMaxPointLights;
}

unsigned int LightingLimits::getMaxSpotLights() const
{
	return m_uiMaxSpotLights;
}
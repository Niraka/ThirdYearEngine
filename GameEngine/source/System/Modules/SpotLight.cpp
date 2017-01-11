#include "System/Modules/SpotLight.h"

const std::string SpotLight::m_sPrefix = "spotLights[";
const std::string SpotLight::m_sColourSuffix = "].vColour";
const std::string SpotLight::m_sPositionSuffix = "].vPosition";
const std::string SpotLight::m_sFacingPositionSuffix = "].vTargetPosition";
const std::string SpotLight::m_sConeAngleSuffix = "].fSpotCutOff";

SpotLight::SpotLight()
{
	m_fConeAngle = 90.f;
	m_style = SpotLightStyle::CIRCLE_COSINE;
	m_position = glm::vec3(0, 5, 0);
	m_facingPosition = glm::vec3(0, 0, 0);
}

SpotLight::SpotLight(glm::vec3 rgb)
{
	setColour(rgb);
	m_fConeAngle = 90.f;
	m_style = SpotLightStyle::CIRCLE_COSINE;
	m_position = glm::vec3(0, 5, 0);
	m_facingPosition = glm::vec3(0, 0, 0);
}

SpotLight::~SpotLight()
{
}

void SpotLight::setPosition(glm::vec3 pos)
{
	if (pos != m_position)
	{
		m_position = pos;
		m_bModifiedFlag = true;
	}
}

void SpotLight::setFacingPosition(glm::vec3 pos)
{
	if (pos != m_facingPosition)
	{
		m_facingPosition = pos;
		m_bModifiedFlag = true;
	}
}

void SpotLight::setConeAngle(float fAngle)
{
	if (fAngle != m_fConeAngle)
	{
		m_fConeAngle = fAngle;
		m_bModifiedFlag = true;
	}
}

void SpotLight::setStyle(SpotLightStyle style)
{
	if (style != m_style)
	{
		m_style = style;
		m_bModifiedFlag = true;
	}
}

glm::vec3 SpotLight::getPosition() const
{
	return m_position;
}

glm::vec3 SpotLight::getFacingPosition() const
{
	return m_facingPosition;
}

float SpotLight::getConeAngle() const
{
	return m_fConeAngle;
}

SpotLightStyle SpotLight::getStyle() const
{
	return m_style;
}

void SpotLight::postConfigToShader(Shader* shader, const std::string& sTargIndex)
{
	if (shader)
	{
		std::string sColourKey = m_sPrefix + sTargIndex + m_sColourSuffix;
		std::string sPositionKey = m_sPrefix + sTargIndex + m_sPositionSuffix;
		std::string sFacingPositionKey = m_sPrefix + sTargIndex + m_sFacingPositionSuffix;
		std::string sAngleKey = m_sPrefix + sTargIndex + m_sConeAngleSuffix;
		shader->postVec3(sColourKey, getColour());
		shader->postVec3(sPositionKey, m_position);
		shader->postVec3(sFacingPositionKey, m_facingPosition);
		shader->postFloat(sAngleKey, m_fConeAngle);
	}
}

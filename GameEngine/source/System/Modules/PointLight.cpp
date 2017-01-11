#include "System/Modules/PointLight.h"

const std::string PointLight::m_sPrefix = "pointLights[";
const std::string PointLight::m_sColourSuffix = "].vColour";
const std::string PointLight::m_sPositionSuffix = "].vPosition";

PointLight::PointLight()
{
	m_position = glm::vec3(0.f);
}

PointLight::PointLight(glm::vec3 rgb)
{
	setColour(rgb);
	m_position = glm::vec3(0.f);
}

PointLight::~PointLight()
{
}

void PointLight::setPosition(glm::vec3 pos)
{
	m_position = pos;
}

void PointLight::postConfigToShader(Shader* shader, const std::string& sTargIndex)
{
	if (shader)
	{
		std::string sColourKey = m_sPrefix + sTargIndex + m_sColourSuffix;
		std::string sPositionKey = m_sPrefix + sTargIndex + m_sPositionSuffix;
		shader->postVec3(sColourKey, getColour());
		shader->postVec3(sPositionKey, m_position);
	}
}
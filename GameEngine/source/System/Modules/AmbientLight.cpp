#include "System/Modules/AmbientLight.h"

const std::string AmbientLight::m_sPrefix = "ambientLights[";
const std::string AmbientLight::m_sColourSuffix = "].vColour";

AmbientLight::AmbientLight()
{
}

AmbientLight::AmbientLight(glm::vec3 rgb)
{
	setColour(rgb);
}

AmbientLight::~AmbientLight()
{
}

void AmbientLight::postConfigToShader(Shader* shader, const std::string& sTargIndex)
{
	if (shader)
	{
		std::string sColourKey = m_sPrefix + sTargIndex + m_sColourSuffix;
		shader->postVec3(sColourKey, getColour());
	}
}
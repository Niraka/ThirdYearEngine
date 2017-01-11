/**
A Material defines a series of parameters that describe the reflective behaviour of a surface.

@author Nathan */

#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm\glm.hpp>
#include <string>
#include <memory>
#include "System/Modules/Texture.h"
#include "System/Modules/IlluminationModels.h"

struct Material
{
	glm::vec3 vReflectivityA;
	glm::vec3 vReflectivityD;
	glm::vec3 vReflectivityS;
	std::shared_ptr<Texture> ambientMap;
	std::shared_ptr<Texture> diffuseMap;
	std::shared_ptr<Texture> specularMap;
	float fShininess;
	glm::vec3 transmissionFilter;
	float fNi;
	IlluminationModels illuminationModel;

	Material()
	{
		vReflectivityA = glm::vec3(1.f);
		vReflectivityD = glm::vec3(1.f);
		vReflectivityS = glm::vec3(1.f);
		fShininess = 100.f;
		transmissionFilter = glm::vec3(1.f);
		fNi = 1.f;
		illuminationModel = IlluminationModels::COLOUR_ON_AMBIENT_OFF;
	}
};

#endif
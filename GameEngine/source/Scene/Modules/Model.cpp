#include "Scene/Modules/Model.h"

const std::string Model::m_sSUUsingTexture("bUsingTexture");
const std::string Model::m_sSUAmbientTexture("ambientTexture");
const std::string Model::m_sSUDiffuseTexture("diffuseTexture");
const std::string Model::m_sSUSpecularTexture("specularTexture");
const std::string Model::m_sSUReflectionA("activeMaterial.vReflectionA");
const std::string Model::m_sSUReflectionD("activeMaterial.vReflectionD");
const std::string Model::m_sSUReflectionS("activeMaterial.vReflectionS");
const std::string Model::m_sSUShininess("activeMaterial.fShininess");
const std::string Model::m_sSUMatM("mM");
const std::string Model::m_sSUMatV("mV");
const std::string Model::m_sSUMatP("mP");
const std::string Model::m_sSUMatVM("mVM");
const std::string Model::m_sSUMatPVM("mPVM");
const std::string Model::m_sSUMatNormal("mNormalMatrix");

Model::Model()
{
	m_mesh = nullptr;
	m_materialLibrary = nullptr;
}

Model::~Model()
{
}

void Model::setMesh(std::shared_ptr<Mesh> mesh)
{
	m_mesh = mesh;
}

void Model::setMaterialLibrary(std::shared_ptr<MaterialLibrary> materialLibrary)
{
	m_materialLibrary = materialLibrary;
}

void Model::render(ShaderManager& shaderManager, const RenderData& data, const glm::mat4& modelMatrix)
{
	// Check that the minimum requirements are valid before rendering:
	// 1) Shader is available
	// 2) Mesh exists and is valid
	Shader* shader = shaderManager.getShader("multi_light");
	if (!shader)
	{
		return;
	}
	if (!m_mesh || !m_mesh->isValid())
	{
		return;
	}

	// Switch the shader in to the correct state
	shaderManager.activateShader("multi_light");
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);


	// Generate and post the relevant matrices the the shader
	// (Normal matrix, M, V, P, VM, PVM)
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));
	shader->postMat3(m_sSUMatNormal, normalMatrix);

	glm::mat4 matrix = modelMatrix;
	shader->postMat4(m_sSUMatM, matrix);
	shader->postMat4(m_sSUMatV, data.viewMatrix);
	shader->postMat4(m_sSUMatP, data.projMatrix);

	matrix = data.viewMatrix * matrix;
	shader->postMat4(m_sSUMatVM, matrix);

	matrix = data.projMatrix * matrix;
	shader->postMat4(m_sSUMatPVM, matrix);

	// Bind the vertex array and initialise some variables
	glBindVertexArray(m_mesh->getArrayId());
	MeshGroup* group = nullptr;
	bool bUsingTex = false;

	// Render each group
	unsigned int uiGroupIndex = 0;
	unsigned int uiNumGroups = m_mesh->getNumGroups();
	for (; uiGroupIndex < uiNumGroups; ++uiGroupIndex)
	{
		group = m_mesh->getGroup(uiGroupIndex);

		// Switch material if there was one		
		if (group->sMaterialName != "" && m_materialLibrary)
		{
			const Material& material = m_materialLibrary->getMaterial(group->sMaterialName);
			shader->postVec3(m_sSUReflectionA, material.vReflectivityA);
			shader->postVec3(m_sSUReflectionD, material.vReflectivityD);
			shader->postVec3(m_sSUReflectionS, material.vReflectivityS);
			shader->postFloat(m_sSUShininess, material.fShininess);

			if (material.diffuseMap)
			{
				bUsingTex = true;
				shader->postBool(m_sSUUsingTexture, bUsingTex);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, material.diffuseMap->getId());
				shader->postUnsignedInt(m_sSUDiffuseTexture, 0);
			}
			else
			{
				bUsingTex = false;
				shader->postBool(m_sSUUsingTexture, bUsingTex);
			}
		}

		// Render each part in this group
		unsigned int uiNumParts = group->uiParts;
		for (unsigned int uiPartIndex = 0; uiPartIndex < uiNumParts; ++uiPartIndex)
		{
			glDrawElements(GL_TRIANGLES,
				group->uiIndicesThisPart.at(uiPartIndex),
				GL_UNSIGNED_INT,
				(void*)(group->uiIndicesOffset.at(uiPartIndex) * sizeof(GLuint)));
		}
	}

	// Unbind
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
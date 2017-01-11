/**
A Model is a combination of a Mesh and MaterialLibrary.

@author Nathan */

#ifndef MODEL_ENGINE_H
#define MODEL_ENGINE_H

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <map>
#include <memory>

#include "Scene/Modules/Mesh.h"
#include "System/Modules/MaterialLibrary.h"
#include "System/Modules/RenderData.h"
#include "System/Modules/ShaderManager.h"

class Model
{
	private:
		static const std::string m_sSUUsingTexture;
		static const std::string m_sSUAmbientTexture;
		static const std::string m_sSUDiffuseTexture;
		static const std::string m_sSUSpecularTexture;
		static const std::string m_sSUReflectionA;
		static const std::string m_sSUReflectionD;
		static const std::string m_sSUReflectionS;
		static const std::string m_sSUShininess;
		static const std::string m_sSUMatM;
		static const std::string m_sSUMatV;
		static const std::string m_sSUMatP;
		static const std::string m_sSUMatVM;
		static const std::string m_sSUMatPVM;
		static const std::string m_sSUMatNormal;

		std::shared_ptr<Mesh> m_mesh;
		std::shared_ptr<MaterialLibrary> m_materialLibrary;

	protected:

	public:	
		/**
		Constructs an empty Model. */
		Model();

		/**
		Destructs a Model. */
		~Model();

		/**
		Sets the material library that this Model will use. 
		@param materialLibrary A shared pointer to the desired MaterialLibrary */
		void setMaterialLibrary(std::shared_ptr<MaterialLibrary> materialLibrary);

		/**
		Sets the mesh of the model.
		@param mesh A shared pointer to the mesh */
		void setMesh(std::shared_ptr<Mesh> mesh);
		
		/**
		Renders the Model to the Window.
		@param shaderManager A reference to the ShaderManager
		@param data Miscellaneous data that can be used for rendering calculations
		@param modelMatrix A const reference to a model matrix */
		void render(ShaderManager& shaderManager, const RenderData& data, const glm::mat4& modelMatrix);
};

#endif
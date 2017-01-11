/**
The ShaderManager is a component of the WindowModule and is responsible for the production
and storage of Shader objects.

Only one shader may be activated at any time. Note that when a shader is deactivated, the uniform
values it was last provided remain intact.

@author Nathan */

#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include <map>

#include "System/Modules/Shader.h"
#include "System/Utility/DirectoryListing.h"

class ShaderManager
{
	private:
		const std::string m_sVertexShaderExtension;
		const std::string m_sFragmentShaderExtension;
		std::map<std::string, std::shared_ptr<Shader>> m_shaders;
		
		/**
		Compiles a shader. 
		@param sShaderFile The shader file, excluding extension and parent folder
		@param shaderType A GLenum indicating the shader type being compiled
		@param shaderId A reference to the location to store the genertated shader id
		@return True if the shader successfully compiled */
		bool compileShader(std::string sShaderFile, GLint shaderType, GLuint& shaderId);

		/**
		Links the given shaders.
		@param uiProgId A reference to the id of the program to link the shaders to
		@param uiVertShaderId A reference to the id of the vertex shader to link
		@param uiFragShaderId A reference to the id of the fragment shader to link
		@return True if the shaders successfully linked, false otherwise */
		bool linkShaders(GLuint& uiProgId, GLuint& uiVertShaderId, GLuint& uiFragShaderId);

	protected:

	public:
		/**
		Constructs a default ShaderManager. */
		ShaderManager();

		/**
		Destructs a ShaderManager. */
		~ShaderManager();

		/**
		Queries the existance a Shader object with the given name
		@return True if a Shader with the given name existed */
		bool shaderExists(std::string sShaderName);

		/**
		Creates a Shader with the given name. If any of the shaders fail to load or compile, or the name
		was already in use, this function will fail. Note that the shader name is also the name of the
		file that the shaders will be loaded from once the appropriate file extensions have been appended.
		This has been done to enforce naming consistency. Example usage:
		Shader name: "skybox"
		Vertex shader: ".\\data\\shaders\\skybox.vert"
		Fragment shader: ".\\data\\shaders\\skybox.frag"
		@param sShaderName The name of the shader
		@return True if the shaders were successfully created, false otherwise */
		bool createShaders(std::string sShaderName);

		/**
		Returns a pointer to a Shader, or a nullptr if no Shader with that name existed.
		@param sShaderName The name of the shader to get 
		@return A pointer to the desired shader, or a nullptr */
		Shader* getShader(std::string sShaderName);

		/**
		Activates the shader with the given name. If another shader was already active, the new shader 
		will replace it. If no such shader existed, this function does nothing.
		@param sShaderName The name of the shader to activate */
		void activateShader(std::string sShaderName);
};

#endif
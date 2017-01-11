/**
A Shader stores information about and provides a single means of interacting with a
GLSL shader program.

Each shader should be given a unique name that describes the kind of operations it
performs. For example, "skybox" or "deferred_lighting"

@author Nathan */

#ifndef SHADER_H
#define SHADER_H

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <map>
#include <string>

class Shader
{
	private:
		std::map<std::string, GLuint> m_uniformMappings;
		GLuint m_uiProgramId;
		std::string m_sName;

		/**
		Constructs a Shader. */
		Shader();

	protected:

	public:
		/**
		Constructs a Shader with the given name.
		@param sName The name of the shader */
		Shader(std::string sName);

		/**
		Destructs a Shader. */
		~Shader();

		/**
		Returns the name of the Shader.
		@return The name of the Shader */
		std::string getName() const;

		/**
		Sets the shader program Id. Changing the program id will reset the internal
		uniform variable mappings.
		@pram uiId The id of the GLSL shader program this Shader represents */
		void setShaderProgramID(GLuint uiId);

		/**
		Gets the shader program Id.
		@return The shader program Id */
		GLuint getShaderProgramId() const;

		/**
		Posts an integer value to the GLSL shader. This function is suitable for integers and enum values. 
		@param sName A const reference to the name of the value to set 
		@param i A const reference to the integer to post */
		void postInt(const std::string& sName, const int& i);

		/**
		Posts an unsigned integer value to the GLSL shader.
		@param sName A const reference to the name of the value to set
		@param ui A const reference to the unsigned integer to post */
		void postUnsignedInt(const std::string& sName, const unsigned int& ui);

		/**
		Posts a float value to the GLSL shader. 
		@param sName A const reference to the name of the value to set 
		@param f A const reference to the float to post */
		void postFloat(const std::string& sName, const float& f);
		
		/**
		Posts a boolean value to the GLSL shader.
		@param sName A const reference to the name of the value to set
		@param b A const reference to the boolean to post */
		void postBool(const std::string& sName, const bool& b);
		
		/**
		Posts a glm::vec2 value to the GLSL shader.
		@param sName A const reference to the name of the value to set
		@param v A const reference to the vector to post */
		void postVec2(const std::string& sName, const glm::vec2& v);
		
		/**
		Posts a glm::vec3 value to the GLSL shader.
		@param sName A const reference to the name of the value to set
		@param v A const reference to the vector to post */
		void postVec3(const std::string& sName, const glm::vec3& v);
		
		/**
		Posts a glm::mat3 value to the GLSL shader.
		@param sName A const reference to the name of the value to set
		@param m A const reference to the matrix to post */
		void postMat3(const std::string& sName, const glm::mat3& m);
		
		/**
		Posts a glm::mat4 value to the GLSL shader.
		@param sName A const reference to the name of the value to set
		@param m A const reference to the matrix to post */
		void postMat4(const std::string& sName, const glm::mat4& m);
};

#endif
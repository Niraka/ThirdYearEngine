#include "System/Modules/Shader.h"

Shader::Shader()
{
}

Shader::Shader(std::string sName)
{
	m_sName = sName;	
	m_uiProgramId = 0;
}

Shader::~Shader()
{
}

std::string Shader::getName() const
{
	return m_sName;
}

void Shader::setShaderProgramID(GLuint uiId)
{
	m_uiProgramId = uiId;
	m_uniformMappings.clear();
}

GLuint Shader::getShaderProgramId() const
{
	return m_uiProgramId;
}

void Shader::postInt(const std::string& sName, const int& i)
{
	std::map<std::string, GLuint>::iterator itResult = m_uniformMappings.find(sName);
	if (itResult != m_uniformMappings.end())
	{
		glUniform1i(itResult->second, i);
	}
	else
	{
		std::pair<std::map<std::string, GLuint>::iterator, bool> result =
			m_uniformMappings.emplace(sName, glGetUniformLocation(m_uiProgramId, sName.c_str()));
		glUniform1i(result.first->second, i);
	}
}

void Shader::postUnsignedInt(const std::string& sName, const unsigned int& ui)
{
	std::map<std::string, GLuint>::iterator itResult = m_uniformMappings.find(sName);
	if (itResult != m_uniformMappings.end())
	{
		glUniform1ui(itResult->second, ui);
	}
	else
	{
		std::pair<std::map<std::string, GLuint>::iterator, bool> result =
			m_uniformMappings.emplace(sName, glGetUniformLocation(m_uiProgramId, sName.c_str()));
		glUniform1ui(result.first->second, ui);
	}
}

void Shader::postFloat(const std::string& sName, const float& f)
{
	std::map<std::string, GLuint>::iterator itResult = m_uniformMappings.find(sName);
	if (itResult != m_uniformMappings.end())
	{
		glUniform1f(itResult->second, f);
	}
	else
	{
		std::pair<std::map<std::string, GLuint>::iterator, bool> result =
			m_uniformMappings.emplace(sName, glGetUniformLocation(m_uiProgramId, sName.c_str()));
		glUniform1f(result.first->second, f);
	}
}

void Shader::postBool(const std::string& sName, const bool& b)
{
	std::map<std::string, GLuint>::iterator itResult = m_uniformMappings.find(sName);
	if (itResult != m_uniformMappings.end())
	{
		glUniform1i(itResult->second, b);
	}
	else
	{
		std::pair<std::map<std::string, GLuint>::iterator, bool> result =
			m_uniformMappings.emplace(sName, glGetUniformLocation(m_uiProgramId, sName.c_str()));
		glUniform1i(result.first->second, b);
	}
}

void Shader::postVec2(const std::string& sName, const glm::vec2& v)
{
	std::map<std::string, GLuint>::iterator itResult = m_uniformMappings.find(sName);
	if (itResult != m_uniformMappings.end())
	{
		glUniform2f(itResult->second, v.x, v.y);
	}
	else
	{
		std::pair<std::map<std::string, GLuint>::iterator, bool> result =
			m_uniformMappings.emplace(sName, glGetUniformLocation(m_uiProgramId, sName.c_str()));
		glUniform2f(result.first->second, v.x, v.y);
	}
}

void Shader::postVec3(const std::string& sName, const glm::vec3& v)
{
	std::map<std::string, GLuint>::iterator itResult = m_uniformMappings.find(sName);
	if (itResult != m_uniformMappings.end())
	{
		glUniform3f(itResult->second, v.x, v.y, v.z);
	}
	else
	{
		std::pair<std::map<std::string, GLuint>::iterator, bool> result =
			m_uniformMappings.emplace(sName, glGetUniformLocation(m_uiProgramId, sName.c_str()));
		glUniform3f(result.first->second, v.x, v.y, v.z);
	}
}

void Shader::postMat3(const std::string& sName, const glm::mat3& m)
{
	std::map<std::string, GLuint>::iterator itResult = m_uniformMappings.find(sName);
	if (itResult != m_uniformMappings.end())
	{
		glUniformMatrix3fv(itResult->second, 1, GL_FALSE, &m[0][0]);
	}
	else
	{
		std::pair<std::map<std::string, GLuint>::iterator, bool> result =
			m_uniformMappings.emplace(sName, glGetUniformLocation(m_uiProgramId, sName.c_str()));
		glUniformMatrix3fv(result.first->second, 1, GL_FALSE, &m[0][0]);
	}
}

void Shader::postMat4(const std::string& sName, const glm::mat4& m)
{
	std::map<std::string, GLuint>::iterator itResult = m_uniformMappings.find(sName);
	if (itResult != m_uniformMappings.end())
	{
		glUniformMatrix4fv(itResult->second, 1, GL_FALSE, &m[0][0]);
	}
	else
	{
		std::pair<std::map<std::string, GLuint>::iterator, bool> result =
			m_uniformMappings.emplace(sName, glGetUniformLocation(m_uiProgramId, sName.c_str()));
		glUniformMatrix4fv(result.first->second, 1, GL_FALSE, &m[0][0]);
	}
}

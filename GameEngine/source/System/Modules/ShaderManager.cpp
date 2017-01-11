#include "System/Modules/ShaderManager.h"

ShaderManager::ShaderManager() :
m_sVertexShaderExtension(".vert"),
m_sFragmentShaderExtension(".frag")
{
}

ShaderManager::~ShaderManager()
{
}

bool ShaderManager::compileShader(std::string sShaderFile, GLint shaderType, GLuint& shaderID)
{
	// Validate the type
	if (shaderType != GL_VERTEX_SHADER && shaderType != GL_FRAGMENT_SHADER)
	{
		return false;
	}

	// Attempt to open the file
	std::string sShaderPath = DirectoryListing::getInstance()->getDirectory("shaders") + sShaderFile;
	std::ifstream inStream(sShaderPath);
	if (!inStream.is_open())
	{
		return false;
	}

	// Read the shader code in to memory
	std::stringstream code;
	code << inStream.rdbuf();
	inStream.close();

	// Create an empty shader object (And verify that it succeeded)
	shaderID = glCreateShader(shaderType);
	if (shaderID == 0)
	{
		return false;
	}

	// Copy the code in to the shader object and compile it
	std::string codeStr(code.str());
	const GLchar* codeArray[] = { codeStr.c_str() };
	glShaderSource(shaderID, 1, codeArray, NULL);
	glCompileShader(shaderID);

	// Check that the compilation was successful
	GLint result;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		// Compile failed, get log
		int iLength = 0;
		std::string sLogString;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &iLength);
		if (iLength > 0) 
		{
			char * c_log = new char[iLength];
			int iWritten = 0;
			glGetShaderInfoLog(shaderID, iLength, &iWritten, c_log);
			sLogString = c_log;
			delete[] c_log;
		}

		std::string sMsg;
		sMsg += sLogString;
		std::cout << sMsg << std::endl;
		return false;
	}

	return true;
}

bool ShaderManager::linkShaders(GLuint& uiProgId, GLuint& uiVertShaderId, GLuint& uiFragShaderId)
{
	// Create an empty program object
	uiProgId = glCreateProgram();
	if (uiProgId == 0)
	{
		return false;
	}

	// Attach the shaders and link the program
	glAttachShader(uiProgId, uiVertShaderId);
	glAttachShader(uiProgId, uiFragShaderId);
	glLinkProgram(uiProgId);

	// Check that the linking was successful
	GLint result;
	glGetProgramiv(uiProgId, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool ShaderManager::shaderExists(std::string sShaderName)
{
	return m_shaders.find(sShaderName) != m_shaders.end();
}

bool ShaderManager::createShaders(std::string sShaderName)
{
	// If the name was already in use, return
	if (shaderExists(sShaderName))
	{
		return false;
	}

	// Create the shader
	std::shared_ptr<Shader> shader = std::make_shared<Shader>(sShaderName);
	GLuint uiVertShaderId = 0;
	GLuint uiFragShaderId = 0;
	GLuint uiProgId = 0;
	if (!compileShader(sShaderName + m_sVertexShaderExtension, GL_VERTEX_SHADER, uiVertShaderId))
	{
		return false;
	}
	if (!compileShader(sShaderName + m_sFragmentShaderExtension, GL_FRAGMENT_SHADER, uiFragShaderId))
	{
		return false;
	}
	if (!linkShaders(uiProgId, uiVertShaderId, uiFragShaderId))
	{
		return false;
	}

	// Store the shader
	shader->setShaderProgramID(uiProgId);
	m_shaders.emplace(sShaderName, shader);

	return true;
}

Shader* ShaderManager::getShader(std::string sShaderName)
{
	if (m_shaders.find(sShaderName) != m_shaders.end())
	{
		return m_shaders.at(sShaderName).get();
	}
	else
	{
		return nullptr;
	}
}

void ShaderManager::activateShader(std::string sShaderName)
{
	if (m_shaders.find(sShaderName) != m_shaders.end())
	{
		glUseProgram(m_shaders.at(sShaderName)->getShaderProgramId());
	}
}
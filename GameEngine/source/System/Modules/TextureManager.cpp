#include "System/Modules/TextureManager.h"

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

bool TextureManager::hasTexture(std::string sName)
{
	return m_textures.find(sName) != m_textures.end();
}

std::shared_ptr<Texture> TextureManager::getTexture(std::string sName)
{
	if (hasTexture(sName))
	{
		return m_textures.at(sName);
	}
	else
	{
		return nullptr;
	}
}

bool TextureManager::loadTexture(std::string sName)
{
	return false;
}

void TextureManager::unloadTexture(std::string sName)
{
	m_textures.erase(sName);
}
/**
Currently unused. Will be linked at a later date.

@author Nathan */

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <memory>
#include <string>

#include "System/Modules/TextureLoader.h"

class TextureManager
{
	private:
		std::map<std::string, std::shared_ptr<Texture>> m_textures;
		TextureLoader m_textureLoader;

	protected:

	public:
		TextureManager();
		~TextureManager();

		bool hasTexture(std::string sName);
		std::shared_ptr<Texture> getTexture(std::string sName);

		bool loadTexture(std::string sName);
		void unloadTexture(std::string sName);
};

#endif
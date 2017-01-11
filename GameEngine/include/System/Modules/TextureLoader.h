/**
Currently unused.

@author Nathan */

#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include "System/Modules/Texture.h"
#include "System/Utility/DirectoryListing.h"

#include <memory>
#include <string>

class TextureLoader
{
	private:
		std::string m_sTexturesDirectory;

	protected:

	public:
		/**
		Constructs a default TextureLoader. */
		TextureLoader();

		/**
		Destructs a TextureLoader. */
		~TextureLoader();

		/**
		*/
		bool loadTexture(std::string sFile, std::shared_ptr<Texture> tex);
};

#endif
#include "System/Modules/TextureLoader.h"

TextureLoader::TextureLoader()
{
	m_sTexturesDirectory = DirectoryListing::getInstance()->getDirectory("textures");
}

TextureLoader::~TextureLoader()
{
}

bool TextureLoader::loadTexture(std::string sFile, std::shared_ptr<Texture> tex)
{
	try
	{
		//std::string sFullPath = m_sTexturesDirectory + sFile;
		//Bitmap bmp = Bitmap::bitmapFromFile(sFullPath); 
		//tex = std::make_shared<Texture>(bmp);
		return true;
	}
	catch (...)
	{
		return false;
	}
}
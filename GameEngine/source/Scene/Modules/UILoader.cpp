#include "Scene/Modules/UILoader.h"
#include "Scene/Modules/GUIModule.h"
#include <fstream>
#include <sstream>


UILoader::UILoader()
{
}

UILoader::~UILoader()
{
}

UILoader::UILoader(std::shared_ptr<GUIModule> GMod, std::shared_ptr<ResourceModule> RMod)
{
	m_sInterfacesDirectory = DirectoryListing::getInstance()->getDirectory("interfaces");
	m_GUIModule = GMod;
	m_resource = RMod;
}

bool UILoader::load(std::string sFile)
{ 
	std::string imageDirectory = DirectoryListing::getInstance()->getDirectory("images");
	std::fstream uiFile(m_sInterfacesDirectory + sFile, std::ios_base::in);
	std::string line;		//A line of text to read

	std::string interfaceName;
	std::vector<std::shared_ptr<UIComponent>> components;

	if (!(uiFile.is_open()))		//if the file failed to open
	{
		return false;
	}
	else
	{
		while (std::getline(uiFile, line))
		{
			std::string s;
			std::istringstream iss(line);
			

			iss >> s;

			if (s == "N")
			{
				iss >> interfaceName;
			}
			else if (s == "I")
			{
				int xp, yp, wd, ht;
				std::string filename;
				std::string id;

				iss >> id;
				iss >> xp;
				iss >> yp;
				iss >> wd;
				iss >> ht;
				iss >> filename;

				Bitmap bmp;
				Bitmap::bitmapFromFile(bmp, imageDirectory + filename);						//Create a bitmap of the image we want
				std::shared_ptr<Texture> tex = std::make_shared<Texture>(bmp);					//Turn that bitmap into a texture

				unsigned int typeID = m_resource->getResourceTypeId<Image>();					//create an image resource
				unsigned int res = m_resource->createResource(typeID);
				Image* img = m_resource->getResource<Image>(typeID, res);

				img->setTexture(tex);			//set the image's texture to our loaded texture
				
				components.push_back(std::make_shared<UIImage>(id, img, xp, yp, wd, ht, m_GUIModule));			//add the new component to the module
			}
			else if (s == "T")
			{
				int xp, yp, wd, ht;
				std::string txt;
				std::string id;
				std::string filename;

				iss >> id;
				iss >> xp;
				iss >> yp;
				iss >> wd;
				iss >> ht;
				iss >> filename;
				iss >> txt;

				Bitmap bmp;
				Bitmap::bitmapFromFile(bmp, imageDirectory + filename);						//Create a bitmap of the image we want
				std::shared_ptr<Texture> tex = std::make_shared<Texture>(bmp);					//Turn that bitmap into a texture

				unsigned int typeID = m_resource->getResourceTypeId<Image>();					//create an image resource
				unsigned int res = m_resource->createResource(typeID);
				Image* img = m_resource->getResource<Image>(typeID, res);

				img->setTexture(tex);			//set the image's texture to our loaded texture
				
				components.push_back(std::make_shared<UIText>(id, img, xp, yp, wd, ht, txt, m_GUIModule));		//add the new component to the module
			}
			else if (s == "B")
			{
				int xp, yp, wd, ht;
				std::string filename;
				std::string id;

				iss >> id;
				iss >> xp;
				iss >> yp;
				iss >> wd;
				iss >> ht;
				iss >> filename;

				Bitmap bmp;
				Bitmap::bitmapFromFile(bmp, imageDirectory + filename);						//Create a bitmap of the image we want
				std::shared_ptr<Texture> tex = std::make_shared<Texture>(bmp);					//Turn that bitmap into a texture

				unsigned int typeID = m_resource->getResourceTypeId<Image>();					//create an image resource
				unsigned int res = m_resource->createResource(typeID);
				Image* buttImg = m_resource->getResource<Image>(typeID, res);

				buttImg->setTexture(tex);			//set the image's texture to our loaded texture

				components.push_back(std::make_shared<UIButton>(id, buttImg, xp, yp, wd, ht, m_GUIModule));			//add the component to the module
			}
		}

		uiFile.close();

		m_GUIModule->addComponentSet(interfaceName, components);
	}
	return true;
}
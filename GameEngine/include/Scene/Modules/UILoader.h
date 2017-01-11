/**
Handles the loading of a user interface file.

@author Nathan + Wade */

#ifndef UI_LOADER_H
#define UI_LOADER_H

#include <string>
#include <memory>
#include "System/Modules/Texture.h"
#include "System/Utility/DirectoryListing.h"

class GUIModule;
class ResourceModule;

class UILoader
{
	private:
		std::string m_sInterfacesDirectory;
		std::shared_ptr<GUIModule> m_GUIModule;						//!< Pointer to the GUI module to send UI component data to
		std::shared_ptr<ResourceModule> m_resource;	//!< Pointer to the resource module to get resources from
	protected:

	public:
		/**
		Constructs a default UILoader. */
		UILoader();

		/**
		Destructs a default UILoader. */
		~UILoader();

		/*Construct a UILoader from given parameteres
		@param GMod A pointer to the GUIModule
		@param RMod A pointer to the resource module */
		UILoader(std::shared_ptr<GUIModule> GMod, std::shared_ptr<ResourceModule> RMod);

		/**
		Loads a user interface from a given XML file. The file name should be exclude
		the parent directory (".\\data\\interfaces\\") as this is automatically prepended.
		@param sFile The name of the file to load
		@return True if the file was successfully parsed, false otherwise */
		bool load(std::string sFile);
};

#endif
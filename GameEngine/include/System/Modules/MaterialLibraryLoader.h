/**
The MaterialLibraryLoader is responsible for loading .mtl files in to MaterialLibrary
objects.

@author Nathan */

#ifndef MATERIAL_LIBRARY_LOADER_H
#define MATERIAL_LIBRARY_LOADER_H

#include <string>
#include <memory>

#include <vector>
#include <iostream>
#include <fstream>

#include "System/Modules/MaterialLibrary.h"
#include "System/Utility/DirectoryListing.h"
#include "System/Utility/StringUtils.h"
#include "System/Utility/MathsUtils.h"

class MaterialLibraryLoader
{
	private:
		std::string m_sMaterialsDirectory;
		std::string m_sTexturesDirectory;
		std::vector<std::string> m_info;
		MathsUtils m_mathsUtils;
		StringUtils m_stringUtils;

	protected:

	public:
		/**
		Constructs a MaterialLibraryLoader. */
		MaterialLibraryLoader();

		/**
		Destructs a MaterialLibraryLoader. */
		~MaterialLibraryLoader();

		/**
		Loads a material library from an .mtl file. If the file could not be found, this function
		does nothing. Note that the file should be given excluding its fixed parent directory as
		this is automatically prepended. For example, ".\\data\\materials\\my_mat.mtl" should be
		given as "my_mat.mtl".
		@param sFile The file to load the library from
		@param lib A shared pointer to the MaterialLibrary to populate 
		@return True if the library was successfully loaded */
		bool loadMaterialLibrary(std::string sFile, std::shared_ptr<MaterialLibrary> lib);

		/**
		Retrieves a vector of information relating to the most recent load Mesh call.
		@return An information vector */
		std::vector<std::string> getInfo() const;
};

#endif
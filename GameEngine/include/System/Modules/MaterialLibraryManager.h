#ifndef MATERIAL_LIBRARY_MANAGER_H
#define MATERIAL_LIBRARY_MANAGER_H

#include <map>
#include <string>

#include "System/Modules/MaterialLibraryLoader.h"
#include "System/Modules/MaterialLibrary.h"

class MaterialLibraryManager
{
	private:
		std::map<std::string, std::shared_ptr<MaterialLibrary>> m_libraries;
		MaterialLibraryLoader m_libraryLoader;

	protected:
	public:
		MaterialLibraryManager();
		~MaterialLibraryManager();

		bool hasLibrary(std::string sName);
		std::shared_ptr<MaterialLibrary> getLibrary(std::string sName);

		bool loadLibrary(std::string sName);
		void unloadLibrary(std::string sName);
};

#endif
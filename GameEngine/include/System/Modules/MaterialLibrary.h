/**
A material library is a convenience wrapper around a std::map of Material objects.

The library is intended to be awarded to a Model, which will use it during rendering
calls.

@author Nathan */

#ifndef MATERIAL_LIBRARY_H
#define MATERIAL_LIBRARY_H

#include "System/Modules/Material.h"
#include <string>
#include <map>

class MaterialLibrary
{
	private:
		std::map<std::string, Material> m_materialLibrary;

	protected:

	public:
		/**
		Constructs a MaterialLibrary. */
		MaterialLibrary();

		/**
		Destructs a MaterialLibrary. */
		~MaterialLibrary();

		/**
		Returns true if the library contained a Material with the given name.
		@param sName A const reference to the name of the Material to get
		@return True if the Material existed, false otherwise */
		bool hasMaterial(const std::string& sName);

		/**
		Retrieves a Material with the given name. 
		@param sName A const reference to the name of the Material to get 
		@return A const reference to a Material */
		const Material& getMaterial(const std::string& sName);
		
		/**
		Adds a Material to the library. If the name was already in use, the new Material
		will overwrite the old one.
		@param sName The name to store the Material under
		@param m The Material */
		void addMaterial(std::string sName, Material m);

		/**
		Returns the number of Materials in this library. 
		@return The number of Materials in this library */
		unsigned int getNumMaterials() const;
};

#endif
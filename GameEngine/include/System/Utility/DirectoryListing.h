/**
The DirectoryListing is a singleton read-only class that provides a central location for storing
directories used throughout the program.

This just makes it easier to track down and modify directories when necessary.

@author Nathan */

#ifndef DIRECTORY_LISTING_H
#define DIRECTORY_LISTING_H

#include <map>
#include <string>

class DirectoryListing
{
	private:
		static DirectoryListing* m_instance;
		static bool m_bInstanceExists;
		
		std::map<std::string, std::string> m_directories;

		DirectoryListing();
		~DirectoryListing();

	protected:

	public:
		/**
		Returns a pointer to the DirectoryListing object. If this is the first call to this function,
		the object is first constructed. 
		@return A pointer to the DirectoryListing object */
		static DirectoryListing* getInstance();

		/**
		Retrieves the path of the directory associated with the given name. Example usage:
		If internal storage contains the mapping "textures" & ".\\data\\textures\\", calling
		this function with the name "textures" will return the directory ".\\data\\textures\\".
		@param sName The name of the directory to get 
		@return The directory path, or an empty string */
		std::string getDirectory(std::string sName);
};

#endif
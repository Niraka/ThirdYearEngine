/**
The ResourceModule is responsible for storing and handing out references to resources.

To add a resource:
Resources must be manually added for the ResourceModule to be able to store them. To add one:
- Add a resource container to the module of the specified type
- Add the type to the buildTypeIds function
- Add the type to the create and delete resource functions, ensuring the correct id is used
  for the switch statement

They must also adhere to a set of requirements. The requirements are:
- An accessible copy constructor
- A lightweight constructor 

The purpose of the ResourceModule is to pack resources as closely as possible in memory to improve
the number of cache hits. Google this if you dont know what it is.

@author Nathan */

#ifndef RESOURCE_MODULE_H
#define RESOURCE_MODULE_H

#include <gl\glew.h>
#include "System/Modules/ResourceContainer.h"
#include "System/Framework/Module.h"
#include "System/Utility/VectorInd.h"
#include "System/Services/LoggerService.h"

#include "System/Modules/Texture.h"
#include "System/Modules/Image.h"
#include <SFML\Audio\SoundBuffer.hpp>

#include <map>
#include <string>
#include <memory>

class ResourceModule :
	public Module
{
	private:
		std::map<std::string, unsigned int> m_resourceIds;
		std::shared_ptr<LoggerNode> m_loggerNode;
	
		ResourceContainer<Texture> m_textures;
		ResourceContainer<Image> m_images;
		ResourceContainer<sf::SoundBuffer> m_soundBuffers;
		
		/**
		Generates the resource type ids. The ids can be retrieved using the getResourceTypeId
		function. Note that the names are implementation specific, and thus should only be
		compared relative to themselves (NOT hard-coded strings!).*/
		void buildTypeIds();

	protected:
		/**
		Updates the ResourceManager. */
		void onUpdate();

		/**
		Starts up the module.
		@return True if the module started up successfully, false otherwise */
		bool start();
		
		/**
		Stops the module.
		@return True if the module stopped successfully, false otherwise */
		bool stop();

	public:
		/**
		Constructs a ResourceModule. */
		ResourceModule();

		/**
		Destructs the ResourceModule, releasing all resources in the process. */
		~ResourceModule();

		/**
		Returns the id of the given resource type. Note that if you intend to access the resource module
		frequently, it is a very good idea to store the value returned by this function. A return value
		of 0 indicates that the resource did not exist.
		@return The id of the given resource type, or 0 */
		template <class T>
		unsigned int getResourceTypeId()
		{
			std::string sType = typeid(T).name();
			std::map<std::string, unsigned int>::iterator it = m_resourceIds.find(sType);
			if (it != m_resourceIds.end())
			{
				return it->second;
			}
			else
			{
				return 0;
			}
		}

		/**
		Queries the resource module to determine whether a resource type is currently supported. 
		@return True if the type is supported, false otherwise */
		template <class T>
		bool isResourceTypeSupported()
		{
			std::string sType = typeid(T).name();
			std::map<std::string, unsigned int>::iterator it = m_resourceIds.find(sType);
			if (it != m_resourceIds.end())
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		/**
		Creates a resource of the given type. Returns the id of the generated resource. An id of 0 indicates
		that the resource failed to create.
		@param uiResourceTypeId The id of the resource type to create
		@return The id of the generated resource */
		unsigned int createResource(unsigned int uiResourceTypeId);

		/**
		Retrieves a resource of the given type and id. If either the type or id did not correspond to a valid
		resource, this function returns a nullptr
		@param uiResourceTypeId The id of the resource type
		@param uiResourceId The id of the resource to get
		@return A pointer to a resource of the templated type, or a nullptr */
		template <class T>
		T* getResource(unsigned int uiResourceTypeId, unsigned int uiResourceId)
		{
			switch (uiResourceTypeId)
			{
			case 1:
				return (T*)m_textures.getResource(uiResourceId);
			case 2:
				return (T*)m_images.getResource(uiResourceId);
			case 3:
				return (T*)m_soundBuffers.getResource(uiResourceId);
			default:
				return nullptr;
			}
		}

		/**
		Deletes a resource of the given type and id. If either the type or id did not correspond to a valid
		resource, this function does nothing.
		@param uiResourceTypeId The id of the resource type
		@param uiResourceId The id of the resource to delete 
		@return True if a resource was deleted, false otherwise */
		bool deleteResource(unsigned int uiResourceTypeId, unsigned int uiResourceId);

		/**
		This function is called when a service becomes available that is a dependency of this class. Note that
		the pointer is delivered as a void pointer and must first be cast to the correct service using a static
		pointer cast.
		@param serviceName The name of the service
		@param service A shared pointer to the new service */
		void serviceDependencyBecameAvailable(Services serviceName, std::shared_ptr<void> service);

		/**
		This function is called when a service that is a dependency of this class becomes unavailable.
		@param serviceName The name of the service */
		void serviceDependencyBecameUnavailable(Services serviceName);
};

#endif
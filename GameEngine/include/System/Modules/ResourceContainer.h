/**
A container for storing a resource of a templated type as part of the ResourceModule.

@author Nathan */

#ifndef RESOURCE_CONTAINER_H
#define RESOURCE_CONTAINER_H

#include "System/Modules/ResourceTypeStats.h"
#include "System/Utility/VectorInd.h"

template <class T>
class ResourceContainer
{
	private:
		ResourceTypeStats m_stats;
		VectorInd<T> m_resources;

	protected:

	public:
		/**
		Constructs a ResourceContainer of the specified type. */
		ResourceContainer()
		{
			m_resources.reserve(50);
			m_resources.add(T());
		}

		/**
		Destructs the ResourceContainer. */
		~ResourceContainer()
		{
		}

		/**
		Creates a resource of the templated type and returns the unique id that it was allocated. 
		An id of 0 indicates that the resource failed to create. 
		@return The id of the generated resource */
		unsigned int createResource()
		{
			m_stats.uiTotalCreated += 1;
			return m_resources.add(T());
		}

		/**
		Retrieves a resource of the templated type using the given id.
		@param uiResourceId The id of the resource to get
		@return A pointer to the resource, or a nullptr if it did not exist */
		T* getResource(unsigned int uiResourceId)
		{
			if (m_resources.exists(uiResourceId))
			{
				m_stats.uiTotalAccess += 1;
				return &m_resources.get(uiResourceId);
			}
			else
			{
				return nullptr;
			}
		}

		/**
		Deletes a resource of the templated type. Note that it is not possible to delete the resource at
		index 0. Returns true on success.
		@param uiResourceId The id of the resource to delete
		@retun True if a resource was deleted, false otherwise */
		bool deleteResource(unsigned int uiResourceId)
		{
			if (uiResourceId == 0)
			{
				return false;
			}

			if (m_resources.remove(uiResourceId))
			{
				m_stats.uiTotalDeleted += 1;
				return true;
			}
			else
			{
				return false;
			}
		}

		/**
		Returns a constant reference to the resources stats. Tracked stats include (but are not limited to)
		number of creations, deletions and retrievals.
		@return A constant reference to the resources stats */
		const ResourceTypeStats& getStats()
		{
			return m_stats;
		}
};

#endif
/**
A mesh stores the geometry data for a model. 

@author Nathan */

#ifndef MESH_H
#define MESH_H

#include <gl\glew.h>
#include <glm\glm.hpp>
#include <vector>
#include <string>
#include <map>

#include "Scene/Modules/MeshGroup.h"

class Mesh
{
	friend class MeshLoader;

	private:
		GLuint m_uiVertexArrayId;                 // The id of the vertex array object
		GLuint m_uiVertexBufferId;                // The id of the vertex data
		GLuint m_uiNormalBufferId;                // The id of the normals data
		GLuint m_uiUvBufferId;                    // The id of the uv data
		GLuint m_uiIndicesBufferId;               // The id of the indices data

		std::string m_sDefaultMatLib;             // The name of the default material library
		std::vector<MeshGroup> m_groups;          // The groups

		glm::vec3 m_min;                          // The minimum XYZ point
		glm::vec3 m_max;                          // The maximum XYZ point
		glm::vec3 m_centre;                       // The centre XYZ point

	protected:

	public:
		/**
		Constructs a default Mesh. */
		Mesh();

		/**
		Destructs the Mesh. */
		~Mesh();

		/**
		Gets the minimum XYZ point of the mesh. This value is primarily intended for forming
		an AABB around the mesh geometry when used in conjunction with the maximum point.
		@return The minimum XYZ point */
		glm::vec3 getMin() const;

		/**
		Gets the maximum XYZ point of the mesh. This value is primarily intended for forming
		an AABB around the mesh geometry when used in conjunction with the minimum point. 
		@return The maximum XYZ point */
		glm::vec3 getMax() const;

		/**
		Gets the centre XYZ point of the mesh. This value is equivalent to the average of
		the minimum and maximum points. 
		@return The centre XYZ point */
		glm::vec3 getCentre() const;

		/**
		Retrieves a pointer to a MeshGroup at the given index.
		@param index The index of the group to get
		@return A pointer to a MeshGroup, or a nullpr if the index was out of range */
		MeshGroup* getGroup(unsigned int index);

		/**
		Returns the number of MeshGroups that make up this Mesh. 
		@return The number of MeshGroups that make up this Mesh */
		unsigned int getNumGroups();

		/**
		Gets the OpenGL vertex array id.
		@return The OpenGL vertex array id */
		GLuint getArrayId() const;

		/**
		Returns the validity of the Mesh
		@return True if the Mesh is valid, false if it was not */
		bool isValid() const;
};

#endif
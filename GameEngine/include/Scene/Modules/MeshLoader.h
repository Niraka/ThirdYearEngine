/**
The MeshLoader is responsible for loading a mesh from an .Obj file in to a Mesh object. 

Potential bug:
loader may be generating too many parts. some models seem to render in full even when missing parts?

@author Nathan */

#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <glm\glm.hpp>
#include <gl\glew.h>

#include "Scene/Modules/Mesh.h"
#include "Scene/Modules/MeshGroup.h"
#include "System/Utility/DirectoryListing.h"
#include "System/Utility/MathsUtils.h"

class MeshLoader
{
	private:
		enum VectorIndexes
		{
			VERTICES,
			UVS,
			NORMALS
		};

		std::string m_sMeshesDirectory;
		std::vector<std::string> m_info;
		MathsUtils m_mathsUtils;

		/**
		Converts the given string to an integer. If the string could not be successfully converted, 1
		is returned instead.
		@param sString A reference to the string to convert
		@return The converted integer, or 1 */
		int toInt(std::string& sString);

		/**
		Converts the given string to a float. If the string could not be successfully converted, 1 is
		returned instead.
		@param sString A reference tot he string to convert
		@return The converted float, or 1 */
		float toFloat(std::string& sString);
		
		/**
		Splits a string using the given split character.
		@param sString The string to split
		@param cSplitChar The character to split the string at
		@return A vector of strings */
		std::vector<std::string> splitString(std::string& sString, char cSplitChar);

		/**
		Resolves the indices of the loaded mesh such that OpenGL may correctly interpret them. See the class
		description for more information on this.
		@param vertices A reference to the vertices vector
		@param normals A reference to the normals vector
		@param indicesV A reference to the vertex indices vector
		@param indicesN A reference to the normals indices vector
		@return A single resolved indices vector */
		std::vector<unsigned int> resolveIndicesNoUvs(std::vector<float>& vertices,
							     std::vector<float>& normals,
								 std::vector<unsigned int>& indicesV,
								 std::vector<unsigned int>& indicesN);

		/**
		Resolves the indices of the loaded mesh such that OpenGL may correctly interpret them. See the class
		description for more information on this.
		@param vertices A reference to the vertices vector 
		@param uvs A reference to the uvs vector
		@param normals A reference to the normals vector
		@param indicesV A reference to the vertex indices vector
		@param indicesU A reference to the uvs indices vector
		@param indicesN A reference to the normals indices vector
		@return A single resolved indices vector */
		std::vector<unsigned int> resolveIndicesUvs(std::vector<float>& vertices,
							   std::vector<float>& uvs,
							   std::vector<float>& normals,
							   std::vector<unsigned int>& indicesV,
							   std::vector<unsigned int>& indicesU,
							   std::vector<unsigned int>& indicesN);

	protected:

	public:
		/**
		Constructs a default MeshLoader. */
		MeshLoader();

		/**
		Destructs a MeshLoader. */
		~MeshLoader();
		
		/**
		Loads a Mesh from the given file in to the provided mesh pointer. A Mesh is considered
		successfully loaded as long as the file opens and parses. Note that the given file name 
		should exclude the directory as this is automatically preprended. E.g:
		".\\data\\meshes\\environment\\my_mesh.obj" should be given as
		"environment\\my_mesh.obj". 
		@param sFile The file to load from
		@param mesh A shared pointer to the mesh to populate
		@return True if the Mesh loaded successfully, false otherwise */
		bool loadMesh(std::string sFile, std::shared_ptr<Mesh> mesh);

		/**
		Retrieves a vector of information relating to the most recent load Mesh call.
		@return An information vector */
		std::vector<std::string> getInfo() const;
};

#endif
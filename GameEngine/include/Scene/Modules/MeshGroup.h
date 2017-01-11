/**
A MeshGroup is a component of a Mesh that stores information about the vertices that are a part of
a group within a Mesh. 

Most Meshes only contain 1 group. But some require more.

@author Nathan */

#ifndef MESH_GROUP_H
#define MESH_GROUP_H

#include <string>
#include <vector>

struct MeshGroup
{
	std::string sGroupName;                      // The name of the group
	std::string sMaterialName;                   // The name of the material this group uses
	unsigned int uiParts;                        // The number of parts this group has
	std::vector<unsigned int> uiIndicesThisPart; // The number of indices in this part  
	std::vector<unsigned int> uiIndicesOffset;   // The number of indices to offset to reach the start of this part
};

#endif
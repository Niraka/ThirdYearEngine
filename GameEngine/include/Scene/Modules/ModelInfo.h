/**
A ModelInfo contains all of the information required to load a Model.

@author Nathan */

#ifndef MODEL_INFO_H
#define MODEL_INFO_H

#include <vector>
#include <string>

struct ModelInfo
{
	std::string sModelName;           // The name by which the model will be referred to. E.G: "crate"
	std::string sMeshFile;            // The mesh file name. E.G: "crate.obj"
	std::string sMaterialLibrary;     // The material library file name. E.G: "crate.mtl"
};

#endif
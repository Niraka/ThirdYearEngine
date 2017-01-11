/**
A cubemap is a render-able cube that is used to project textures on to a target surface. Typically they
are used as skyboxes.

@author Nathan */

#ifndef CUBE_MAP_H
#define CUBE_MAP_H

#include <cstdio>
#include <cmath>
#include <vector>
#include <glm\glm.hpp>

class CubeMap
{
	private:
		float m_fSize;

	public:
		/**
		Constructs a cubemap using the given size and texture files.
		@param fSize The size of the cubemap
		@param filePaths The paths to the cubemap textures */
		CubeMap(float fSize, std::vector<std::string> filePaths);

		/**
		Sets the position of the cubemap.
		@param pos The position */
		void setPosition(glm::vec3 pos);
};

#endif

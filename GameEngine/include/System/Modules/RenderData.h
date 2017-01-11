/**
The RenderData structure is an efficient way of passing data to all
renderables during a render call. 

Note that the data is passed around as a const reference, ensuring
that it will not be corrupted by any one renderable.

@author Nathan */

#ifndef RENDER_DATA_H
#define RENDER_DATA_H

#include <glm\glm.hpp>

struct RenderData
{
	glm::mat4 projMatrix;
	glm::mat4 viewMatrix;
};

#endif
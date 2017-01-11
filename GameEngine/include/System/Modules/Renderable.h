/**
Defines the necessary functions for a class to become Renderable.

@author Nathan */

#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "System/Modules/RenderData.h"
#include "System/Modules/ShaderManager.h"

class Renderable
{
	private:

	protected:

	public:
		/**
		Renders to the window. Use the shader manager to activate the correct shader.
		@param shaderManager A reference to the ShaderManager
		@param data Miscellaneous data that can be used for rendering calculations */
		virtual void render(ShaderManager& shaderManager, const RenderData& data) = 0;
};

#endif
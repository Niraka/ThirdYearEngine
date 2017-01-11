/**
tdogl::Texture

Copyright 2012 Thomas Dalling - http://tomdalling.com/

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

Represents an OpenGL texture.

@author Thomas Dalling, Nathan */

#pragma once

#include <GL\glew.h>
#include "System/Modules/Bitmap.h"

class Texture 
{
	private:	
		GLuint m_uiTextureId;
		GLfloat m_fWidth;
		GLfloat m_fHeight;

	public:
		/**
		Constructs an empty texture. */
		Texture();
		
		/**
		Creates a texture from a bitmap. The texture will be loaded upside down because tdogl::Bitmap pixel data is
		ordered from the top row down, but OpenGL expects the data to be from the bottom row up.
		@param bitmap The bitmap to load the texture from.
		@param minMagFiler (Optional) GL_NEAREST or GL_LINEAR. Defaults to LINEAR.
		@param wrapMode (Optional) GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, or GL_CLAMP_TO_BORDER. Defaults to GL_CLAMP_TO_EDGE. */
		Texture(const Bitmap& bitmap, GLint minMagFiler = GL_LINEAR, GLint wrapMode = GL_CLAMP_TO_EDGE);

		/**
		Deletes the texture object with glDeleteTextures. */
		~Texture();
		
		/**
		Initialises the texture from a bitmap. The texture will be loaded upside down because tdogl::Bitmap pixel
		data is ordered from the top row down, but OpenGL expects the data to be from the bottom row up.
		@param bitmap The bitmap to load the texture from.
		@param minMagFiler (Optional) GL_NEAREST or GL_LINEAR. Defaults to LINEAR.
		@param wrapMode (Optional) GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, or GL_CLAMP_TO_BORDER. Defaults to GL_CLAMP_TO_EDGE. */
		void init(const Bitmap& bitmap, GLint minMagFiler = GL_LINEAR, GLint wrapMode = GL_CLAMP_TO_EDGE);

		/**
		Returns the id of the texture object assigned by openGL.
		@return The id of the texture */
		GLuint getId() const;

		/**
		Returns the width of the texture in pixels.
		@return The width of the texture */
		GLfloat getWidth() const;

		/**
		Returns the height of the texture in pixels.
		@return The height of the texture */
		GLfloat getHeight() const;
};
/*
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
*/

#include "System/Modules/Texture.h"
#include <stdexcept>

static GLenum TextureFormatForBitmapFormat(Bitmap::Format format)
{
	switch (format) {
	case Bitmap::Format_RGB: return GL_RGB;
	case Bitmap::Format_RGBA: return GL_RGBA;
	default: throw std::runtime_error("Unrecognised Bitmap::Format");
	}
}

Texture::Texture()
{
}

Texture::Texture(const Bitmap& bitmap, GLint minMagFiler, GLint wrapMode) :
m_fWidth((GLfloat)bitmap.width()),
m_fHeight((GLfloat)bitmap.height())
{
	glGenTextures(1, &m_uiTextureId);
	glBindTexture(GL_TEXTURE_2D, m_uiTextureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minMagFiler);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minMagFiler);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	glTexImage2D(GL_TEXTURE_2D,
		0,
		TextureFormatForBitmapFormat(bitmap.format()),
		(GLsizei)bitmap.width(),
		(GLsizei)bitmap.height(),
		0,
		TextureFormatForBitmapFormat(bitmap.format()),
		GL_UNSIGNED_BYTE,
		bitmap.pixelBuffer());
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_uiTextureId);
}

void Texture::init(const Bitmap& bitmap, GLint minMagFiler, GLint wrapMode)
{
	m_fWidth = (GLfloat)bitmap.width();
	m_fHeight = (GLfloat)bitmap.height();

	glGenTextures(1, &m_uiTextureId);
	glBindTexture(GL_TEXTURE_2D, m_uiTextureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minMagFiler);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minMagFiler);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	glTexImage2D(GL_TEXTURE_2D,
		0,
		TextureFormatForBitmapFormat(bitmap.format()),
		(GLsizei)bitmap.width(),
		(GLsizei)bitmap.height(),
		0,
		TextureFormatForBitmapFormat(bitmap.format()),
		GL_UNSIGNED_BYTE,
		bitmap.pixelBuffer());
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getId() const
{
	return m_uiTextureId;
}

GLfloat Texture::getWidth() const
{
	return m_fWidth;
}

GLfloat Texture::getHeight() const
{
	return m_fHeight;
}
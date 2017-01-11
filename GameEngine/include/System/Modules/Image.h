/**
An image is a 2D renderable texture. 

Implementation not finished.

@TODO: Make image size modifyable
@TODO: Make image position modifyable
@TODO: Render with a projection & model matrix

@author Nathan */

#ifndef IMAGE_H
#define IMAGE_H

#include <memory>
#include <glm\gtc\matrix_transform.hpp>

#include "System/Modules/Texture.h"
#include "System/Modules/Shader.h"

class Image
{
	private:
		static const std::string m_sSUTexture;
		static const std::string m_sSUXOffset;
		static const std::string m_sSUYOffset;
		static const std::string m_sSUViewWidth;
		static const std::string m_sSUViewHeight;

		unsigned int m_uiNumPoints = 6;				  // The number of vertices to build the rectangle
		unsigned int m_uiXPosition;					  // The x position in pixels
		unsigned int m_uiYPosition;					  // The y position in pixels
		unsigned int m_uiWidth;						  // The width in pixels
		unsigned int m_uiHeight;					  // The height in pixels

		GLuint m_uiVertexArrayId;
		GLuint m_uiVertexBufferId;
		GLuint m_uiUVBufferId;

		std::shared_ptr<Texture> m_texture;

	protected:

	public:
		/**
		Constructs an Image. */
		Image();

		/**
		Destructs the Image. */
		~Image();

		/**
		Construct an image from given paramaters
		@param tex A pointer to the texture to use
		@param x The x position, in pixels
		@param y The y position, in pixels
		@param wd The width, in pixels
		@param ht The height, in pixels		*/
		Image(std::shared_ptr<Texture> tex, unsigned int x, unsigned int y, unsigned int wd, unsigned int ht);
		
		/**
		Initialises the Image. This function must be called before the Image can be used.
		This function will fail if openGL was not initialised.
		@return True if the Image successfully initialises, false otherwise */
		bool init();

		/**
		Sets the texture. Passing a nullptr will remove the current texture if there
		was one.
		@param texture A shared pointer to a texture */
		void setTexture(std::shared_ptr<Texture> texture);

		/**
		Sets the position of the image in pixels. 0,0 indicates the top-left of the
		window and is the default position.
		@param uiXPos The x position
		@param uiYPos The y position */
		void setPosition(unsigned int uiXPos, unsigned int uiYPos);

		/**
		Sets the size of the texture in pixels. Must be at least 1x1. Defaults to
		100x100.
		@param uiWidth The width of the image
		@param uiHeight The height of the image */
		void setSize(unsigned int uiWidth, unsigned int uiHeight);

		/**
		Renders to the window. You must activate the desired shader BEFORE calling this
		function. This is done for performance reasons.
		@param shaderManager A reference to the Shader to use */
		void render(Shader& shader);
		
};

#endif
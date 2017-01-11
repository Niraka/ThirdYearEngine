/**
Allows the user to display an image on screen. 

@author Nathan + Wade */

#ifndef UI_IMAGE_H
#define UI_IMAGE_H

#include "Scene/Modules/UIComponent.h"

class UIImage :
	public UIComponent
{
	private:

	protected:
		/**
		Renders the UImage. */
		void onRender(ShaderManager& shaderManager, const RenderData& data);

	public:
		/**
		Constructs a default UIImage. */
		UIImage();

		/**
		Destructs a UIImage. */
		~UIImage();

		/**
		Construct a UIImage with given parameteres
		@param idName a unique name for this image
		@param i A pointer to an image
		@param x The x position of the new UIImage
		@param y The y position of the new UIImage
		@param w The width of the new image
		@param h The height of the new image
		@param GMod A pointer ot the GUIModule*/
		UIImage(std::string idName, Image* i, int x, int y, int w, int h, std::shared_ptr<GUIModule> GMod);

		/**
		Get the type of this UIComponent
		@return The enum type of this component */
		UIType getType();
};

#endif
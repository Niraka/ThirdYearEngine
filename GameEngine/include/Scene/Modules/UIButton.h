/**
Allows the user to display a clickable button on screen. 

@author Nathan + Wade */

#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include "Scene/Modules/UIComponent.h"

class UIButton :
	public UIComponent
{
	private:
		

	protected:
		/**
		Renders the UButton. */
		void onRender(ShaderManager& shaderManager, const RenderData& data);

	public:
		/**
		Constructs a default UIButton. */
		UIButton();

		/**
		Destructs a UIButton. */
		~UIButton();

		/** 
		Construct a UIButton from given parameteres
		@param idName A unique name for this button
		@param i The image for this UIButton
		@param x The x position
		@param y The y position
		@param w The width
		@param h The height
		@oaram GMod A pointer to the GUIModule	*/
		UIButton(std::string idName, Image* i, int x, int y, int w, int h, std::shared_ptr<GUIModule> GMod);

		/**
		Get the type of this UIComponent
		@return The enum type of this component */
		UIType getType();
};

#endif
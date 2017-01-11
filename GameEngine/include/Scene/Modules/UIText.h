/**
Allows the user to display text on screen. 

@author Nathan + Wade */

#ifndef UI_TEXT_H
#define UI_TEXT_H

#include "Scene/Modules/UIComponent.h"
#include "System/Utility/VectorSim.h"

class UIText :
	public UIComponent
{
	private:
		std::string m_textString;							//!< The string of text to draw to the screen
		VectorSim<std::pair<int, int>> m_textImages;		//!< A vector of pairs that holds the co-ordinates of each character to be pulled from the FontSet image

	protected:
		/**
		Renders the UIText. */
		void onRender(ShaderManager& shaderManager, const RenderData& data);

	public:
		/**
		Constructs a default UIText. */
		UIText();

		/**
		Destructs a UIText. */
		~UIText();

		/**
		Construct a UIText object with given parameteres
		@param idName A unique name for this text object
		@param
		@param text The text for this object to draw
		@param x The x position
		@param y The y position
		@param w The width
		@param h The height
		@param GMod A pointer to the GUIModule	*/
		UIText(std::string idName, Image* img, int x, int y, int w, int h, std::string text, std::shared_ptr<GUIModule> GMod);

		/**
		Get the type of this UIComponent
		@return The enum type of this component */
		UIType getType();

		/** 
		Fills m_textImages to match the given string
		@param textString The string to convert to images*/
		void setImageToText(std::string textString);
};

#endif
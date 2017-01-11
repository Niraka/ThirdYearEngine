/**
The base class of a UI component such as a button, image or text.

@author Nathan + Wade */

#ifndef UI_COMPONENT_H
#define UI_COMPONENT_H

#include "System/Modules/Renderable.h"
#include "System/Modules/Image.h"

class GUIModule;

class UIComponent :
	public Renderable
{
	public:
		enum UIType 
		{
			BUTTON, 
			TEXT, 
			IMAGE 
		};

	private:
	
	protected:
		bool m_bIsVisible;
		int m_XPos;		                            //<! The relative X position as a percentage of screen width
		int m_YPos;		                            //<! The relative Y position as a percentage of screen height
		int m_width;	                            //<! The relative width as a percentage of screen width
		int m_height;	                            //<! The relative height as a percentage of screen height

		int m_screenHeight;	                      	//<! The known height of the current screen
		int m_screenWidth;	                      	//<! The known width of the current screen
							                      
		std::string m_name;	                      	//!< A name for this object
		Image* m_drawImage;	                      	//<! The image to draw for this component
		std::shared_ptr<GUIModule> m_parentModule;	//!< Pointer to the parent module

		/**
		Called each time render is called to execute component-specific rendering (if the 
		component is visible). */
		virtual void onRender(ShaderManager& shaderManager, const RenderData& data) = 0;

	public:
		/**
		Constructs a default UIComponent. */
		UIComponent();

		/**
		Destructs a UIComponent. */
		~UIComponent();

		/**
		Renders to the window.
		@param data The data required to correctly interface with the shader */
		void render(ShaderManager& shaderManager, const RenderData& data);

		/**
		Set the visibility of this Component
		@param vis The new visibilty to set this component to*/
		void setVisible(bool vis);

		/**
		@return The current visibilty of this compnent*/
		bool getVisibile();

		/**
		Set this component to a new position
		@param x The new X position
		@param y The new Y position*/
		void setPosition(int x, int y);

		/**
		Get the current X postion
		@return The current X position */
		int getX();

		/**
		Get the current Y position
		@return The current Y position */
		int getY();

		/**
		Set the size to new values
		@param w The new width
		@param h The new height */
		void setSize(int w, int h);

		/**
		Get the current width
		@return The current width*/
		int getWidth();

		/**
		Get the current height
		@return The current height */
		int getHeight();

		/**
		Check whether this click event click on this component
		@param xClick The x position of the click
		@param yClick the y position of the click */
		bool checkClick(int xClick, int yClick);

		/**
		Get the type of this component
		@return The type of component as an enum */
		virtual UIType getType() = 0;

		/**
		Get the name of this component
		@return the name of the component as a string */
		std::string getName();

		/**
		Update the stored width to a new value
		@param newWidth The new screen width in pixels*/
		void updateWidth(int newWidth);

		/**
		Update the stored height to a new value
		@param newHeight The new screen height in pixels */
		void updateHeight(int newHeight);
		
};

#endif
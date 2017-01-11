/**
Defines the necessary functionality required for a class to be able to register
to listen to input events. 

Note that all functions have default implementations so that the developer may
choose which functions to implement and which functions to ignore. 

@author Nathan */

#ifndef INPUT_LISTENER_H
#define INPUT_LISTENER_H

class InputListener
{
	private:
	protected:
	public:
		/**
		Constructs a default InputListener. */
		InputListener();

		/**
		Destructs an InputListener. */
		~InputListener();

		/**
		Called by the InputManager when a character is typed. 
		@param uiChar The character code */
		virtual void onCharacterTyped(unsigned int uiChar);

		/**
		Called by the InputManager when the mouse is scrolled. 
		@param fXOffset The x scroll offset 
		@param fYOffset The y scroll offset */
		virtual void onScroll(double fXOffset, double fYOffset);

		/**
		Called by the InputManager when the cursor enters the window. */
		virtual void onCursorEnter();

		/**
		Called by the InputManager when the cursor exits the window. */
		virtual void onCursorExit();

		/**
		Called by the InputManager when the cursor moves. 
		@param fXPos The x position of the cursor
		@param fYPos The y position of the cursor */
		virtual void onCursorMoved(double fXPos, double fYPos);

		/**
		Called by the InputManager when a mouse button is pressed. 
		@param iButton The code of the button that was pressed
		@param iMods The modifiers bitmask */
		virtual void onMousePressed(int iButton, int iMods);

		/**
		Called by the InputManager when a mouse button is released.
		@param iButton The code of the button that was released
		@param iMods The modifiers bitmask */
		virtual void onMouseReleased(int iButton, int iMods);

		/**
		Called by the InputManager when a key is pressed.
		@param iKey The code of the key that was pressed
		@param iScancode The scancode of the key
		@param iMods The modifiers bitmask */
		virtual void onKeyPressed(int iKey, int iScancode, int iMods);

		/**
		Called by the InputManager when a key is released.
		@param iKey The code of the key that was released
		@param iScancode The scancode of the key
		@param iMods The modifiers bitmask */
		virtual void onKeyReleased(int iKey, int iScancode, int iMods);
};

#endif
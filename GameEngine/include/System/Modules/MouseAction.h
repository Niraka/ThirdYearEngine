/**
A MouseAction is an interface class that provides the necessary functionality for a class to be capable
of executing instructions in response to a mouse input event.

Note that while it is perfectly acceptable to use an InputListener in place of a ControlSet and its
associated Key/MouseActions's, the latter is preferable in situations where a large number of controls
need to be bound/unbound at one time and from one location (typically the Scene).

@author Nathan */

#ifndef MOUSE_ACTION_H
#define MOUSE_ACTION_H

class MouseAction
{
	private:

	protected:

	public:
		/**
		This function is called by a Scene when a mouse button with a matching modifiers bitmask whose
		action points to this class is pressed. 
		@param iButton The button code
		@param iModifiers The modifiers bitmask */
		virtual void onMousePressed(int iButton, int iModifiers) = 0;

		/**
		This function is called by a Scene when a mouse button with a matching modifiers bitmask whose
		action points to this class is released.
		@param iButton The button code
		@param iModifiers The modifiers bitmask */
		virtual void onMouseReleased(int iButton, int iModifiers) = 0;
};

#endif
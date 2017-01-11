/**
The InputManager is a singletons class that, once bound to a GLFW window, will receive
and broadcast input to all registered input listeners.

The manager is a singleton because it provides a simple means to convert static context
GLFW input events to non-static context without particularly complicated logic.

Whilst it is possible to register any number of input listeners with the manager, it is
expected that only 1-5 listeners will be active at any one time.

@author Nathan */

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <GLFW/glfw3.h>
#include "System/Modules/InputListener.h"
#include "System/Utility/VectorSim.h"

class InputManager
{
	private:
		static bool m_bInstanceExists;
		static InputManager* m_instance;
		VectorSim<InputListener*> m_listeners;
		
		/**
		Constructs an InputManager. */
		InputManager();

		/**
		Destructs an InputManager. */
		~InputManager();

		/**
		Called by the character callback to broadcast the event to all input listeners. 
		@param window A pointer to the window the event occurred on 
		@param uiChar The code of the character that was typed*/
		void charCallbackBroadcaster(GLFWwindow* window, unsigned int uiChar);

		/**
		Called by the scroll callback to broadcast the event to all input listeners.
		@param window A pointer to the window the event occurred on
		@param fXOffset The x offset
		@param fYOffset The y offset */
		void scrollCallbackBroadcaster(GLFWwindow* window, double fXOffset, double fYOffset);

		/**
		Called by the cursor enter/exit callback to broadcast the event to all input listeners.
		@param window A pointer to the window the event occurred on
		@param iEntered An enum indicating whether the window was entered or exited  */
		void cursorEnterCallbackBroadcaster(GLFWwindow* window, int iEntered);

		/**
		Called by the cursor position callback to broadcast the event to all input listeners. 
		@param window A pointer to the window the event occurred on
		@param fXPos The x position of the cursor
		@param fYPos The y position of the cursor */ 
		void cursorPositionCallbackBroadcaster(GLFWwindow* window, double fXPos, double fYPos);

		/**
		Called by the mouse button callback to broadcast the event to all input listeners. 
		@param window A pointer to the window the event occurred on
		@param iButton The button code
		@param iAction The action code
		@param iMods The modifiers bitmask */
		void mouseCallbackBroadcaster(GLFWwindow* window, int iButton, int iAction, int iMods);

		/**
		Called by the key button callback to broadcast the event to all input listeners. 
		@param window A pointer to the window the event occurred on
		@param iKey The key code
		@param iScancode The scancode
		@param iAction The action code
		@param iMods The modifiers bitmask */ 
		void keyCallbackBroadcaster(GLFWwindow* window, int iKey, int iScancode, int iAction, int iMods);

	protected:

	public:
		/**
		Returns a pointer to the InputManager. If this is the first time the InputManager has been
		retrieved, it is first instantiated. 
		@return A pointer to the InputManager */
		static InputManager* getInstance();

		/**
		The character callback function for receiving character events. 
		@param window A pointer to the window the event occurred on 
		@param uiChar The code of the character that was typed */
		static void char_callback(GLFWwindow* window, unsigned int uiChar);
		
		/**
		The scroll callback function for receiving scroll events.
		@param window A pointer to the window the event occurred on
		@param fXOffset The x offset
		@param fYOffset The y offset */
		static void scroll_callback(GLFWwindow* window, double fXOffset, double fYOffset);

		/**
		The cursor enter/exit callback function for receiving cursor enter/exit events.
		@param window A pointer to the window the event occurred on
		@param iEntered An enum indicating whether the window was entered or exited */
		static void cursorEnter_callback(GLFWwindow* window, int iEntered);

		/**
		The cursor position callback function for receiving cursor movement events.
		@param window A pointer to the window the event occurred on
		@param fXPos The x position of the cursor
		@param fYPos The y position of the cursor */
		static void cursorPosition_callback(GLFWwindow* window, double fXPos, double fYPos);

		/**
		The mouse callback function for receiving mouse button events. 
		@param window A pointer to the window the event occurred on
		@param iButton The button code
		@param iAction The action code
		@param iMods The modifiers bitmask */
		static void mouse_callback(GLFWwindow* window, int iButton, int iAction, int iMods);

		/**
		The key callback function for receiving key events.
		@param window A pointer to the window the event occurred on
		@param iKey The key code
		@param iScancode The scancode
		@param iAction The action code
		@param iMods The modifiers bitmask */
		static void key_callback(GLFWwindow* window, int iKey, int iScancode, int iAction, int iMods);

		/**
		Clears all listeners from the InputManager. This function should only be called when the WindowModule
		is shutting down as the GLFWwindow bindings will become invalid. */
		void clearListeners();

		/**
		Adds an input listener.
		@param l The input listener to add */
		void addInputListener(InputListener* l);

		/**
		Removes an input listenerr.
		@param l The input listener to remove
		@return The number of listeners removed*/
		int removeInputListener(InputListener* l);
};

#endif
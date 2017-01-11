/**
The window events manager is responsible for handling events occurring on the glfw Window. 

@author Nathan */

#ifndef WINDOW_EVENTS_MANAGER_H
#define WINDOW_EVENTS_MANAGER_H

#include <GLFW/glfw3.h>
#include "System/Modules/WindowListener.h"
#include "System/Utility/VectorSim.h"

class WindowEventsManager
{
	private:
		static WindowEventsManager* m_instance;
		static bool m_bInstanceExists;
		VectorSim<WindowListener*> m_listeners;

		/**
		Constructs a default WindowEventsManager. */
		WindowEventsManager();

		/**
		Destructs a WindowEventsManager. */
		~WindowEventsManager();

		/**
		Called by the window close callback function to broadcast the event to all window
		event listeners. */
		void windowCloseCallbackBroadcaster();

		/**
		Called by the window resized callback function to broadcast the event to all window
		event listeners.
		@param iWidth The new window width
		@param iHeight The new window height */
		void windowResizedCallbackBroadcaster(int iWidth, int iHeight);

		/**
		Called by the frame buffer resized callback function to broadcast the event to all 
		window event listeners.
		@param iWidth The new frame buffer width
		@param iHeight The new frame buffer height */
		void frameBufferResizedCallbackBroadcaster(int iWidth, int iHeight);

	protected:

	public:
		/**
		Returns a pointer to the WindowEventsManager. If this is the first time calling this 
		function, the manager is instantiated first.
		@return A pointer to the WindowEventsManager. */
		static WindowEventsManager* getInstance();

		/**
		The window close callback function for receiving window close events.
		@param window A pointer to the window the event occurred on */
		static void windowCloseCallback(GLFWwindow* window);

		/**
		The window resized callback function for receiving window resized events.
		@param window A pointer to the window the event occurred on 
		@param iWidth The new window width
		@param iHeight The new window height */
		static void windowResizedCallback(GLFWwindow* window, int iWidth, int iHeight);

		/**
		The frame buffer resized callback function for receiving frame buffer resized events.
		@param window A pointer to the window the event occurred on
		@param iWidth The new window width
		@param iHeight The new window height */
		static void frameBufferResizedCallback(GLFWwindow* window, int iWidth, int iHeight);

		/**
		Adds a window listener to the window events manager. 
		@param l The listener to add */
		void addWindowListener(WindowListener* l);

		/**
		Removes a window listener from the window events manager.
		@param l The listener to remove
		@return The number of listeners removed */
		int removeWindowListener(WindowListener* l);
};

#endif
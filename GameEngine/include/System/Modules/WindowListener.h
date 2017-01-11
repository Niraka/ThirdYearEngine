/**
Allows a class to register with the WindowEventsManager to receive window events. 

Each event has an empty implementation so that the programmer may decide which
events to take interest in whilst avoiding class clutter.

@author Nathan */

#ifndef WINDOW_LISTENER_H
#define WINDOW_LISTENER_H

class WindowListener
{
	private:

	protected:

	public:
		/**
		Called by the WindowEventsManager when the Window is closing. */
		virtual void onWindowClose();

		/**
		Called by the WindowEventsManager when the Window has been resized.
		@param iWidth The new width of the window
		@param iHeight The new height of the window */
		virtual void onWindowResized(int iWidth, int iHeight);

		/**
		Called by the WindowEventsManager when the frame buffer has been resized.
		@param iWidth The new width of the frame buffer
		@param iHeight The new height of the frame buffer */
		virtual void onFramebufferResized(int iWidth, int iHeight);
};

#endif
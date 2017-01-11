/**
A LightListener is an interface that defines the necessary functions for a class to be able to register for
and respond to events occurring on Lights.

@author Nathan */

#ifndef LIGHT_LISTENER_H
#define LIGHT_LISTENER_H

class LightListener
{
	private:
	protected:
	public:
		/**
		This function is called by a Light this LightListener is listening to when it is enabled.
		@param uiLightId The id of the light that was enabled */
		virtual void onLightEnabled(unsigned int uiLightId) = 0;

		/**
		This function is called by a Light this LightListener is listening to when it is disabled.
		@param uiLightId The id of the light that was disabled */
		virtual void onLightDisabled(unsigned int uiLightId) = 0;
};

#endif
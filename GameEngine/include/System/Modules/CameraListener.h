/**
A CameraListener is an interface class that provides the necessary function definitions for a class to
be able to register for and respond to events occurring on Cameras as part of a Scene.

@author Nathan */

#ifndef CAMERA_LISTENER_H
#define CAMERA_LISTENER_H

class CameraListener
{
	private:

	protected:

	public:
		/**
		Called when a Camera this CameraListener is listening to is enabled. 
		@param iCameraId The id of the Camera */
		virtual void onCameraEnabled(int iCameraId) = 0;

		/**
		Called when a Camera this CameraListener is listening to is disabled.
		@param iCameraId The id of the Camera */
		virtual void onCameraDisabled(int iCameraId) = 0;

		/**
		Called when a Camera this CameraListener is listening to enables its automatic aspect
		ratio correction.
		@param iCameraId The id of the Camera */
		virtual void onAutoAspectEnabled(int iCameraId) = 0;

		/**
		Called when a Camera this CameraListener is listening to disables its automatic aspect
		ratio correction.
		@param iCameraId The id of the Camera */
		virtual void onAutoAspectDisabled(int iCameraId) = 0;

		/**
		Called when a Camera this CameraListener is listening to resizes its view. 
		@param iCameraId The id of the Camera */
		virtual void onViewResized(int iCameraId) = 0;
};

#endif
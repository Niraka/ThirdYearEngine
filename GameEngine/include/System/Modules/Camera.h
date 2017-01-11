/**
A 3D Camera.

Note that field of view is stored in radians internally

@author Nathan */

#ifndef CAMERA_H
#define CAMERA_H

#define GLM_FORCE_RADIANS

#include "System/Modules/CameraListener.h"
#include "System/Utility/VectorSim.h"
#include "System/Utility/MathsUtils.h"
#include "System/Utility/HasId.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera :
	public HasId<int>
{
	private:
		MathsUtils m_mathsUtils;
		VectorSim<CameraListener*> m_listeners;
		bool m_bEnabled;
		bool m_bAutoAspectRatio;

		float m_fFieldOfView;
		float m_fNearClip;
		float m_fFarClip;
		float m_fAspectRatio;

		bool m_bInvertYAxis;
		bool m_bInvertXAxis;
		bool m_bInvertZAxis;

		glm::vec2 m_viewSize;
		glm::vec2 m_viewPosition;

		glm::mat4 m_view;
		glm::mat4 m_projection;

		glm::vec3 m_position;
		glm::vec3 m_targetPos;

		glm::vec3 m_xaxis;
		glm::vec3 m_yaxis;
		glm::vec3 m_zaxis;

		/**
		Rebuilds the projection matrix. */
		void buildProjectionMatrix();

		/**
		Rebuilds the view matrix. */
		void buildViewMatrix();

	protected:

	public:
		/**
		Constructs a Camera. */
		Camera();

		/**
		Destructs the Camera. */
		~Camera();

		/**
		Enables or disables the Camera. All registered CameraListeners are notified. Cameras are 
		enabled by default. 
		@param bEnabled True to enable, false to disable */
		void setEnabled(bool bEnabled);
		
		/**
		Returns the enabled status of the Camera. 
		@return True if the Camera is enabled, false otherwise */
		bool isEnabled() const;

		/**
		Enables or disables automatic aspect ratio correction when this Camera is attached to a Scene.
		Disabled this to apply custom affects. Enabled by default. 
		@param bEnabled True to enable, false otherwise */
		void setAutoAspectRatioEnabled(bool bEnabled);

		/**
		Returns the enabled status of the automatic aspect ratio correction.
		@return True if automatic aspect ratio correction is enabled, false otherwise */
		bool isAutoAspectRatioEnabled() const;

		/**
		Sets the size of the view. The size should be given as a percentage between 0 and 1.
		@param size The new size */
		void setViewSize(glm::vec2 size);

		/**
		Sets the position of the view. The position should be given as a percentage between 0 and
		1. Note that (0, 0) indicates the bottom left of the window, not the top right.
		@param position The new position */
		void setViewPosition(glm::vec2 position);
		
		/**
		Returns the view size. 
		@return The view size */
		glm::vec2 getViewSize() const;

		/**
		Returns the view position.
		@return The view position */
		glm::vec2 getViewPosition() const;

		/**
		Adds a CameraListener. The listener will receive notification of events occurring on this Camera.
		@param l The listener to add */
		void addListener(CameraListener* l);

		/**
		Removes a CameraListener.
		@param l The listener to remove
		@return The number of CameraListeners removed */
		int removeListener(CameraListener* l);

		/**
		Returns the field of view.
		@return The field of view */
		float getFOV() const;

		/**
		Returns the aspect ratio.
		@return The aspect ratio */
		float getAspectRatio() const;

		/**
		Returns the near clipping plane.
		@return The near clipping plane */
		float getNearClip() const;

		/**
		Returns the far clipping plane.
		@return The far clipping plane */
		float getFarClip() const;

		/**
		Sets the field of view. This value must be greater than 0 and less than 180. Defaults
		to 110.
		@param fFOV The new field of view */
		void setFOV(float fFOV);

		/**
		Calculates the aspect ratio from the given width and height. If automatic aspect ratio updating
		is enabled (which by default it is), this function is called by the Scene that the Camera is 
		attached to each time the window is resized.
		@param fWidth The width of the view
		@param fHeight The height of the view */
		void setAspectRatio(float fWidth, float fHeight);

		/**
		Sets the near clipping plane. The near clipping plane must be greater than 0, and the far
		clipping plane must be greater than the near clipping plane. Default values are 0.01 and
		200 respectively.
		@param fNear The new near clip
		@param fFar The new far clip */
		void setClippingPlanes(float fNear, float fFar);

		/**
		Moves the camera relative to its current position.
		@param fX The x offset
		@param fY The y offset
		@param fZ The z offset */
		void move(float fX, float fY, float fZ);

		/**
		Sets the absolute position of the camera.
		@param pos The new position */
		void setPosition(glm::vec3 pos);

		/**
		Sets the absolute position of the target of the Camera. The target is the position that the Camera
		is looking at. 
		@param The new position */
		void setTarget(glm::vec3 pos);

		/**
		Returns the position of the camera in world coordinates.
		@return The position */
		glm::vec3 getPosition() const;

		/**
		Returns the view matrix.
		@return The view matrix */
		glm::mat4 getViewMatrix();

		/**
		Returns the projection matrix
		@return The projection matrix */
		glm::mat4 getProjMatrix();
	
		/**
		Resets the Camera to its initial state. The Camera id remains unchanged. */
		void reset();

		/**
		Sets the orientation of the Camera.
		@param fX The x rotation in degrees
		@param fY The y rotation in degrees
		@param fZ The z rotation in degrees */
		void setOrientation(float fX, float fY, float fZ);

		/**
		Rotates the Camera.
		@param fX The x rotation in degrees
		@param fY The y rotation in degrees
		@param fZ The z rotation in degrees */
		void rotate(float fX, float fY, float fZ);

};

#endif
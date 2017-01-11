/**
A Scene is the world in which the game is currently taking places. It links together lighting, cameras, controls,
game logic and entities.

Whilst it is possible to create multiple Scenes, only one Scene may be active at any one time. This is useful for
loading scene data in the background, or for games that require the player to switch between two (or more) very 
different locations frequently.

@author Nathan */

#ifndef SCENE_H
#define SCENE_H

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "System/Modules/Renderable.h"
#include "System/Modules/PointLight.h"
#include "System/Modules/AmbientLight.h"
#include "System/Modules/SpotLight.h"
#include "System/Modules/Camera.h"
#include "System/Modules/InputManager.h"
#include "System/Utility/VectorInd.h"
#include "System/Modules/LightingLimits.h"
#include "System/Modules/Shader.h"
#include "System/Modules/ControlSet.h"
#include "System/Modules/ShaderManager.h"
#include "System/Modules/CameraListener.h"
#include "System/Modules/RenderModes.h"
#include "System/Modules/WindowEventsManager.h"
#include "System/Utility/VectorInd.h"
#include "System/Utility/ArbitraryPropertyListener.h"

#include <set>
#include <vector>
#include <memory>
#include <array>

class Scene :
	public InputListener,
	public CameraListener,
	public WindowListener,
	public LightListener
{
	public:
		enum LightTypes
		{
			UNKNOWN_TYPE,
			AMBIENT,
			POINT,
			SPOT
		};

	private:
		const std::string m_sShaderKeyNumAmbLgts;
		const std::string m_sShaderKeyNumPoiLgts;
		const std::string m_sShaderKeyNumSpoLgts;

		std::string m_sName;
		ShaderManager* m_shaderManager;
		GLFWwindow* m_window;
		std::array<std::pair<Renderable*, RenderModes>, 20> m_renderables;

		double m_fLastCursorX;
		double m_fLastCursorY;
		float m_fFrameBufferWidth;
		float m_fFrameBufferHeight;
		float m_fWindowWidth;
		float m_fWindowHeight;
		unsigned int m_uiNextCameraId;
		unsigned int m_uiNextLightId;

		std::shared_ptr<ControlSet> m_activeControlSet;
		VectorInd<std::shared_ptr<ControlSet>> m_controlSets;
		std::vector<std::shared_ptr<AmbientLight>> m_activeAmbientLights;
		std::vector<std::shared_ptr<PointLight>> m_activePointLights;
		std::vector<std::shared_ptr<SpotLight>> m_activeSpotLights;
		std::vector<std::shared_ptr<AmbientLight>> m_ambientLights;
		std::vector<std::shared_ptr<PointLight>> m_pointLights;
		std::vector<std::shared_ptr<SpotLight>> m_spotLights;
		LightingLimits m_lightingLimits;
		std::vector<std::shared_ptr<Camera>> m_cameras;
		unsigned int m_uiNumEnabledCameras;
		int m_iCursorMode;
		
		/**
		Constructs a Scene. Not to be used. */
		Scene();

		/**
		Called by the WindowEventsManager when the frame buffer has been resized.
		@param iWidth The new width of the frame buffer
		@param iHeight The new height of the frame buffer */
		void onFramebufferResized(int iWidth, int iHeight);

		/**
		Called by the WindowEventsManager when the Window has been resized.
		@param iWidth The new width of the window
		@param iHeight The new height of the window */
		void onWindowResized(int iWidth, int iHeight);

		/**
		Called by the InputManager when a character is typed.
		@param uiChar The character code */
		void onCharacterTyped(unsigned int uiChar);

		/**
		Called by the InputManager when the mouse is scrolled.
		@param fXOffset The x scroll offset
		@param fYOffset The y scroll offset */
		void onScroll(double fXOffset, double fYOffset);

		/**
		Called by the InputManager when the cursor enters the window. */
		void onCursorEnter();

		/**
		Called by the InputManager when the cursor exits the window. */
		void onCursorExit();

		/**
		Called by the InputManager when the cursor moves.
		@param fXPos The x position of the cursor
		@param fYPos The y position of the cursor */
		void onCursorMoved(double fXPos, double fYPos);

		/**
		Called by the InputManager when a mouse button is pressed.
		@param iButton The code of the button that was pressed
		@param iMods The modifiers bitmask */
		void onMousePressed(int iButton, int iMods);

		/**
		Called by the InputManager when a mouse button is released.
		@param iButton The code of the button that was released
		@param iMods The modifiers bitmask */
		void onMouseReleased(int iButton, int iMods);

		/**
		Called by the InputManager when a key is pressed.
		@param iKey The code of the key that was pressed
		@param iScancode The scancode of the key
		@param iMods The modifiers bitmask */
		void onKeyPressed(int iKey, int iScancode, int iMods);

		/**
		Called by the InputManager when a key is released.
		@param iKey The code of the key that was released
		@param iScancode The scancode of the key
		@param iMods The modifiers bitmask */
		void onKeyReleased(int iKey, int iScancode, int iMods);

		/**
		Gets the type of the light with the given id.
		@param uiLightId The id of the light to query
		@return The type of the light */
		LightTypes getLightType(unsigned int uiLightId) const;

		/**
		This function is called by a Light this LightListener is listening to when it is enabled.
		@param uiLightId The id of the light that was enabled */
		void onLightEnabled(unsigned int uiLightId);

		/**
		This function is called by a Light this LightListener is listening to when it is disabled.
		@param uiLightId The id of the light that was disabled */
		void onLightDisabled(unsigned int uiLightId);
		
		/**
		Called when a Camera this CameraListener is listening to is enabled.
		@param iCameraId The id of the Camera */
		void onCameraEnabled(int iCameraId);

		/**
		Called when a Camera this CameraListener is listening to is disabled.
		@param iCameraId The id of the Camera */
		void onCameraDisabled(int iCameraId);

		/**
		Called when a Camera this CameraListener is listening to enables its automatic aspect
		ratio correction.
		@param iCameraId The id of the Camera */
		void onAutoAspectEnabled(int iCameraId);

		/**
		Called when a Camera this CameraListener is listening to disables its automatic aspect
		ratio correction.
		@param iCameraId The id of the Camera */
		void onAutoAspectDisabled(int iCameraId);

		/**
		Called when a Camera this CameraListener is listening to resizes its view.
		@param iCameraId The id of the Camera */
		void onViewResized(int iCameraId);

	protected:

	public:
		/**
		Constructs a Scene with the given name and framebuffer size. 
		@param sName The name of the Scene */
		Scene(std::string sName);

		/**
		Destructs the Scene. */
		~Scene();

		/**
		Returns the name of the Scene.
		@return The name of the Scene */
		std::string getName() const;

		/**
		This function is called when the Scene is activated by the SceneManager. It should be used to perform
		essential initialisation or continuation of the Scene. */
		void onActivation();

		/**
		This function is called when the Scene is deactivated by the SceneManager. It should be used to put
		the Scene in to a safe, stable state where it may be either continued or unloaded. */
		void onDeactivation();

		/**
		Adds a Renderable to the Scene. The Renderable will receive periodic calls to its render function whenever
		this Scene is active. The index parameter will determine the order in which Renderables are drawn. Higher
		numbers are drawn after lower numbered Renderables. The index must be between 0 and 19 inclusive. The
		Rendermode determines the method of rendering the Renderable will use.
		Note that in the future the optional parameters will no longer be optional!
		@param r The Renderable to add 
		@param iIndex (Optional) The index to insert the Renderable. Defaults to next available
		@param mode (Optional) The RenderMode to use. Default 'PER_CAMERA' */
		void addRenderable(Renderable* r, int iIndex = -1, RenderModes mode = RenderModes::PER_CAMERA);

		/**
		Removes a Renderable from the Scene. 
		@param r The Renderable to remove */
		void removeRenderable(Renderable* r);

		/**
		Sets the cursor mode. The mode will be remembered and activated each time this Scene is
		activated. The mode will not be updated if an invalid value is given. 
		@param iCursorMode One of GLFW_CURSOR_NORMAL, GLFW_CURSOR_HIDDEN or GLFW_CURSOR_DISABLED */
		void setCursorMode(int iCursorMode);

		/**
		Updates the scene. */
		void onUpdate();

		/**
		Renders the game. Requires a valid pointer to the ShaderManager and at least one Camera to run. */
		void onRender();

		/**
		Creates a Camera. The Camera is disabled by default. An id of 0 indicates that the Camera failed
		to create. 
		@return The id of the Camera */
		unsigned int createCamera();

		/**
		Returns a shared pointer to a Camera with the given id. If no such Camera existed, a nullptr is
		returned instead.
		@param uiCameraId The id of the Camera to get 
		@retun A shared pointer to a Camera, or a nullptr */
		std::shared_ptr<Camera> getCamera(unsigned int uiCameraId);

		/**
		Deletes a Camera with the given id.
		@param uiCameraId The id of the Camera to delete 
		@return True if a Camera was deleted, false otherwise */
		bool deleteCamera(unsigned int uiCameraId);

		/**
		Creates a light of the given type and asigns it a unique id. The light is disabled by
		default. An id of 0 indicates that the light failed to create.
		@param type The type of light to create 
		@return The id of the light */
		unsigned int createLight(LightTypes type);

		/**
		Returns a shared pointer to an ambient light with the given id. If no such light existed, a
		nullptr is returned instead.
		@param uiLightId The id of the light to get
		@return A shared pointer to an AmbientLight, or a nullptr */
		std::shared_ptr<AmbientLight> getAmbientLight(unsigned int uiLightId);
		
		/**
		Returns a shared pointer to an point light with the given id. If no such light existed, a
		nullptr is returned instead.
		@param uiLightId The id of the light to get
		@return A shared pointer to a PointLight, or a nullptr */
		std::shared_ptr<PointLight> getPointLight(unsigned int uiLightId);

		/**
		Returns a shared pointer to a spot light with the given id. If no such light existed, a
		nullptr is returned instead.
		@param uiLightId The id of the light to get
		@return A shared pointer to a SpotLight, or a nullptr */
		std::shared_ptr<SpotLight> getSpotLight(unsigned int uiLightId);
		
		/**
		Deletes a light with the given id. If no such light existed, this function does nothing.
		@param uiLightId The id of the light to delete
		@return True if a light was deleted, false otherwise */
		bool deleteLight(unsigned int uiLightId);

		/**
		Creates a ControlSet and returns its id. A returned id of 0 indicates a failure to create
		the set.
		@return The id of the new ControlSet, or 0 */
		unsigned int createControlSet();

		/**
		Activates the ControlSet with the given id. If no such ControlSet existed, this function
		does nothing. 
		@param uiId The id of the ControlSet to activate */
		void activateControlSet(unsigned int uiId);

		/**
		Deactivates the ControlSet with the given id. If no such ControlSet existed, this function
		does nothing. 
		@param uiId The id of the ControlSet to deactivate */
		void deactivateControlSet(unsigned int uiId);

		/**
		Returns a shared pointer to a ControlSet with the given id. If no such ControlSet existed, a 
		nullptr is returned instead.
		@param uiId The id of the ControlSet to get 
		@return A shared pointer to a ControlSet, or a nullptr */
		std::shared_ptr<ControlSet> getControlSet(unsigned int uiId);
		
		/**
		Deletes a ControlSet with the given id. If no such ControlSet existed, this function does
		nothing. If the ControlSet was currently active, it is first deactivated.
		@param uiId The id of the ControlSet to delete */
		void deleteControlSet(unsigned int uiId);

		/**
		Links some essential components to the Scene. These components are removed when the scene
		is deactivated and restored when it is activated. 
		@param window A pointer to the active window
		@param shaderManagaer A pointer to the shader manager */
		void linkComponents(GLFWwindow* window, ShaderManager* shaderManager);

};

#endif
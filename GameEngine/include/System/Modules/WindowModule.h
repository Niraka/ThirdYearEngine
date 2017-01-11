/**
The WindowModule is responsible for managing the canvas with which the user will interact.

Input
User input is handled via the InputManager. The manager converts incoming GLFW input events in to
engine input events and distributes them to all registered input listeners.

Window
Whilst GLFW has support for multiple windows, this engine will only be supporting one. The window
may be configured in many ways such as size, styling, interactivity and initial position.

Scenes
The window hosts a SceneManager that is responsible for the management of Scene objects.

Shaders
The window compiles and stores a series of shaders that can be utilised by the Scenes during rendering.

@author Nathan */

#ifndef WINDOW_MODULE_H
#define WINDOW_MODULE_H

#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "System/Framework/Module.h"
#include "System/Framework/ConfigurationListener.h"
#include "System/Framework/ConfigurationManager.h"
#include "System/Modules/SceneManager.h"
#include "System/Modules/ShaderManager.h"
#include "System/Services/LoggerService.h"
#include "System/Modules/InputManager.h"
#include "System/Modules/EventModule.h"
#include "System/Modules/WindowEventsManager.h"

class WindowModule :
	public Module,
	public ConfigurationListener,
	public SceneManagerListener
{
	private:
		GLFWmonitor* m_monitor;
		GLFWwindow* m_window;
		bool m_bRendering;
		bool m_bRenderingContextValid;
		std::shared_ptr<LoggerNode> m_loggerNode;
		std::shared_ptr<EventModule> m_eventModule;

		unsigned int m_uiSceneChangedId = 0;
		unsigned int m_uiWindowOpenedId = 0;
		unsigned int m_uiWindowClosedId = 0;

		ShaderManager m_shaderManager;
		InputManager* m_inputManager;
		WindowEventsManager* m_windowEventsManager;
		SceneManager m_sceneManager;

		/**
		Creates a Window. If the window already existed, it is first closed before being reopened.
		This function will fail if it attempts to utilise a configuration that the users computer
		does not support.
		@return True if the window was successfully created, false otherwise */
		bool createWindow();

		/**
		Repositions the window. */
		void repositionWindow();

	protected:
		/**
		Updates the WindowModule. */
		void onUpdate();

	public:
		/**
		Constructs a WindowModule. */
		WindowModule();

		/**
		Destructs a WindowModule. */
		~WindowModule();

		/**
		Starts up the module.
		@return True if the module started up successfully, false otherwise */
		bool start();

		/**
		Stops the module.
		@return True if the module stopped successfully, false otherwise */
		bool stop(); 

		/**
		Creates a Shader with the given name. If any of the shaders fail to load or compile, or the name 
		was already in use, this function will fail. Note that the shader name is also the name of the 
		file that the shaders will be loaded from once the appropriate file extensions have been appended. 
		This has been done to enforce naming consistency. Example usage:
		Shader name: "skybox"
		Vertex shader: ".\\data\\shaders\\skybox.vert"
		Fragment shader: ".\\data\\shaders\\skybox.frag"
		@param sShaderName The name of the shader
		@return True if the shaders were successfully created, false otherwise */
		bool createShaders(std::string sShaderName);

		/**
		Creates a Scene object with the given name. If the name was already in use by another Scene, this
		function will fail.
		@param sSceneName The name of the Scene to create
		@return A shared pointer to a Scene, or a nullptr on failure */
		std::shared_ptr<Scene> createScene(std::string sSceneName);

		/**
		Retrieves a Scene with the given name. If no such Scene existed, a nullptr is returned instead. If
		no name is provided, the action is performed on the active Scene instead.
		@param sSceneName (Optional) The name of the Scene to get
		@return A shared pointer to a Scene, or a nullptr */
		std::shared_ptr<Scene> getScene(std::string sSceneName = "");

		/**
		Returns true if a Scene with the given name existed. If no name is provided, this function returns
		true when the active Scene is valid.
		@param sSceneName (Optional) The name of the Scene to query
		@return True if a Scene with the given name existed, false otherwise */
		bool sceneExists(std::string sSceneName = "");

		/**
		Deletes a Scene object with the given name. If the Scene was active, it is first deactivated. If
		no such Scene existed, this function does nothing.
		@param sSceneName The name of the Scene to delete */
		void deleteScene(std::string sSceneName);

		/**
		Activates a Scene with the given name. If another Scene was already active, it is first deactivated.
		If no such Scene existed, this function does nothing.
		@param sSceneName The name of the Scene to activate
		@return True if the Scene was activated, false otherwise */
		bool activateScene(std::string sSceneName);

		/**
		Returns true if a Scene with the given name is active.
		@param sSceneName The name of the Scene to query
		@return True if a Scene with the given name is active */
		bool sceneIsActive(std::string sSceneName);

		/**
		Deactivates a Scene with the given name. The Scene's data is not unloaded. If the Scene was not active or
		did not exist, this function does nothing.
		@param sSceneName The name of the Scene to deactivate
		@return True if the Scene was deactivated, false otherwise */
		bool deactivateScene(std::string sSceneName, bool bSceneChangeEvent = true);

		/**
		Adds a SceneManagerListener to the SceneManager.
		@param l The listener to add */
		void addSceneManagerListener(SceneManagerListener* l);

		/**
		Removes a SceneManagerListener from the SceneManager.
		@param l The listener to remove.
		@return The number of listeners removed */
		int removeSceneManagerListener(SceneManagerListener* l);

		/**
		Enables or disables rendering. Note that this flag will be ignored if the WindowModule determines
		that the rendering context was not valid. 
		@param bRendering True to enable rendering */
		void setRendering(bool bRendering);

		/**
		This function is called by the ConfigurationManager when a property is updated. 
		@param prop An enum representing the updated property */
		void onPropertyUpdated(ConfigurationProperties prop);
			
		/**
		This function is called when a module becomes available that is a dependency of this class. Note that
		the pointer is delivered as a void pointer and must first be cast to the correct module using a
		static pointer cast.
		@param moduleName The name of the module
		@param module A shared pointer to the new module */
		void moduleDependencyBecameAvailable(Modules moduleName, std::shared_ptr<void> module);

		/**
		This function is called when a service becomes available that is a dependency of this class. Note that
		the pointer is delivered as a void pointer and must first be cast to the correct service using a static
		pointer cast.
		@param serviceName The name of the service
		@param service A shared pointer to the new service */
		void serviceDependencyBecameAvailable(Services serviceName, std::shared_ptr<void> service);

		/**
		This function is called when a module that is a dependency of this class becomes unavailable.
		@param moduleName The name of the module */
		void moduleDependencyBecameUnavailable(Modules moduleName);

		/**
		This function is called when a service that is a dependency of this class becomes unavailable.
		@param serviceName The name of the service */
		void serviceDependencyBecameUnavailable(Services serviceName);

		/**
		Adds an input listener to the input manager.
		@param l The input listener to add */
		void addInputListener(InputListener* l);

		/**
		Removes an input listener from the input manager.
		@param l The input listener to remove */
		int removeInputListener(InputListener* l);

		/**
		This function is called whenever the active scene is changed.
		@param sNewScene The name of the new scene
		@param sOldScene The name of the old scene */
		void onSceneChanged(std::string sNewScene, std::string sOldScene);
};

#endif
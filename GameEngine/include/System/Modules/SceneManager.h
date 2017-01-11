/**
The SceneManager is responsible for the creation, storage and activation of Scene objects. It is also
capable of receiving input and forwarding it to the active Scene.

Creation & Deletion
A Scene object can be created or deleted using the createScene and deleteScene functions. A scene that
has not been created via this method lacks important initialisation that will instead be performed when
the Scene is activated. A Scene object will be held in storage until it is deleted using the deleteScene 
function.

Storage
Scene objects are stored internally as shared pointers. A Scene may be retrieved with a call to getScene
with the correct Scene name. Scene names must be unique.

Activation/Deactivation
For a Scene to rendered or successfully interacted with by the user, it must first be activated. Only one
Scene may be active at any one time, and activating a Scene whilst another is already active would deactive
the first. Deactivated Scenes stop receiving updates, input and rendering calls, but do not unload their data.

@author Nathan */

#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <map>
#include <string>
#include <memory>

#include "System/Utility/VectorSim.h"
#include "System/Modules/Scene.h"
#include "System/Modules/SceneManagerListener.h"
#include "System/Utility/DirectoryListing.h"

class SceneManager
{
	private:
		std::map<std::string, std::shared_ptr<Scene>> m_scenes;
		VectorSim<SceneManagerListener*> m_listeners;
		std::shared_ptr<Scene> m_activeScene;

		/**
		Launches a sceneChanged event to all registered SceneManagerListeners. 
		@param sNewScene The name of the old Scene
		@param sOldScene The name of the new Scene */
		void launchEvent_sceneChanged(std::string sNewScene, std::string sOldScene);


	protected:

	public:
		/**
		Constructs a SceneManager. */
		SceneManager();

		/**
		Destructs a SceneManager. */
		~SceneManager();

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
		Updates a Scene with the given name. If no name is provided, the active Scene is updated instead.
		@param sSceneName (Optional) The name of the Scene to update */
		void updateScene(std::string sSceneName = "");

		/**
		Renders a Scene with the given name. If no name is provided, the active Scene is rendered instead.
		@param sSceneName (Optional) The name of the Scene to render */
		void renderScene(std::string sSceneName = "");

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
		Adds a SceneManagerListener.
		@param l The listener to add */
		void addListener(SceneManagerListener* l);

		/**
		Removes a SceneManagerListener.
		@param l The listener to remove.
		@return The number of listeners removed */
		int removeListener(SceneManagerListener* l);
};

#endif
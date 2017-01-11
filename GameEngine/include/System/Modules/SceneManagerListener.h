/**
The SceneManagerListener provides a means of listening to events occurring on the SceneManager.

Inherit this class, implement the functions and use WindowModule.addSceneManagerListener(this)
to register your listener with the SceneManager.

@author Nathan */

#ifndef SCENE_MANAGER_LISTENER_H
#define SCENE_MANAGER_LISTENER_H

#include <string>

class SceneManagerListener
{
	private:

	protected:

	public:
		/**
		This function is called whenever the active scene is changed.
		@param sNewScene The name of the new scene
		@param sOldScene The name of the old scene */
		virtual void onSceneChanged(std::string sNewScene, std::string sOldScene) = 0;
};

#endif
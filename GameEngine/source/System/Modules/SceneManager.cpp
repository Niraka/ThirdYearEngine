#include "System/Modules/SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::launchEvent_sceneChanged(std::string sNewScene, std::string sOldScene)
{
	unsigned int uiIndx = 0;
	unsigned int uiSize = m_listeners.size();
	for (; uiIndx < uiSize; ++uiIndx)
	{
		m_listeners.at(uiIndx)->onSceneChanged(sNewScene, sOldScene);
	}
}

std::shared_ptr<Scene> SceneManager::createScene(std::string sSceneName)
{
	// Return if the name was not available
	if (sceneExists(sSceneName))
	{
		return nullptr;
	}

	std::shared_ptr<Scene> scene = std::make_shared<Scene>(sSceneName);
	m_scenes.emplace(sSceneName, scene);
	return scene;
}

std::shared_ptr<Scene> SceneManager::getScene(std::string sSceneName)
{
	if (sSceneName == "")
	{
		if (m_activeScene)
		{
			return m_activeScene;
		}
		else
		{
			return nullptr;
		}
	}
	else
	{
		if (sceneExists(sSceneName))
		{
			return m_scenes.at(sSceneName);
		}
		else
		{
			return nullptr;
		}
	}
}

void SceneManager::updateScene(std::string sSceneName)
{
	if (sSceneName == "" && m_activeScene)
	{
		m_activeScene->onUpdate();
	}
	else
	{
		if (sceneExists(sSceneName))
		{
			m_scenes.at(sSceneName)->onUpdate();
		}
	}
}

void SceneManager::renderScene(std::string sSceneName)
{
	if (sSceneName == "" && m_activeScene)
	{
		m_activeScene->onRender();
	}
	else
	{
		if (sceneExists(sSceneName))
		{
			m_scenes.at(sSceneName)->onRender();
		}
	}
}

bool SceneManager::sceneExists(std::string sSceneName)
{
	if (sSceneName == "")
	{
		if (m_activeScene)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return m_scenes.find(sSceneName) != m_scenes.end();
	}
}

void SceneManager::deleteScene(std::string sSceneName)
{
	if (sceneExists(sSceneName))
	{
		if (m_activeScene)
		{
			if (m_activeScene->getName() == sSceneName)
			{
				deactivateScene(m_activeScene->getName());
			}
		}
		m_scenes.erase(sSceneName);
	}
}

bool SceneManager::activateScene(std::string sSceneName)
{
	if (sceneExists(sSceneName))
	{
		// If another scene is already active, deactivate it first
		std::string sOldScene = "";
		if (m_activeScene)
		{
			sOldScene = m_activeScene->getName();
			deactivateScene(sOldScene, false);
		}

		// Activate the new scene
		m_activeScene = m_scenes.at(sSceneName);
		launchEvent_sceneChanged(sSceneName, sOldScene);
		m_activeScene->onActivation();
		return true;
	}
	return false;
}

bool SceneManager::sceneIsActive(std::string sSceneName)
{
	if (m_activeScene)
	{
		if (m_activeScene->getName() == sSceneName)
		{
			return true;
		}
	}
	return false;
}

bool SceneManager::deactivateScene(std::string sSceneName, bool bSceneChangeEvent)
{
	if (m_activeScene)
	{
		if (m_activeScene->getName() == sSceneName)
		{
			if (bSceneChangeEvent)
			{
				launchEvent_sceneChanged(std::string(), sSceneName);
			}
			m_activeScene->onDeactivation();
			m_activeScene = nullptr;
			return true;
		}
	}
	return false;
}

void SceneManager::addListener(SceneManagerListener* l)
{
	m_listeners.add(l);
}

int SceneManager::removeListener(SceneManagerListener* l)
{
	return m_listeners.remove(l);
}
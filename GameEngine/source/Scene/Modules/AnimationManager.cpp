#include "Scene/Modules/AnimationManager.h"		

AnimationManager::AnimationManager()
{
}

AnimationManager::~AnimationManager()
{
}

void AnimationManager::loadAnimation(std::string sName)
{

}

void AnimationManager::unloadAnimation(std::string sName)
{

}

std::shared_ptr<Animation> AnimationManager::getAnimation(std::string sName)
{
	if (animationExists(sName))
	{
		return m_animations.at(sName);
	}
	else
	{
		return nullptr;
	}
}

bool AnimationManager::animationExists(std::string sName) const
{
	return m_animations.find(sName) != m_animations.end();
}
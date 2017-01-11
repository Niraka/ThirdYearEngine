/**
@author Nathan */

#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include "Scene/Modules/AnimationLoader.h"

#include <map>
#include <memory>

class AnimationManager
{
	private:
		std::map<std::string, std::shared_ptr<Animation>> m_animations;
		AnimationLoader m_animationLoader;

	protected:

	public:
		/**
		Constructs an AnimationManager. */
		AnimationManager();

		/**
		Destructs an AnimationManager. */
		~AnimationManager();

		void loadAnimation(std::string sName);
		void unloadAnimation(std::string sName);

		/**
		Returns a pointer to the desired Animation or a nullptr if no such Animation existed.
		@param sName The name of the Animation to get
		@return A shared pointer to an Animation, or a nullptr */
		std::shared_ptr<Animation> getAnimation(std::string sName);

		/**
		Returns true if an Animation with the given name exists. 
		@param sName The name of the Animation to query
		@return True if the Animation existed, false otherwise */
		bool animationExists(std::string sName) const;
};

#endif
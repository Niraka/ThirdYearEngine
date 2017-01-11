/**
A KeyAction is an interface class that provides the necessary functionality for a class to be capable
of executing instructions in response to a keyboard input event.

Note that while it is perfectly acceptable to use an InputListener in place of a ControlSet and its
associated Key/MouseActions's, the latter is preferable in situations where a large number of controls
need to be bound/unbound at one time and from one location (typically the Scene).

@author Nathan */

#ifndef KEY_ACTION_H
#define KEY_ACTION_H

#include <GLFW\glfw3.h>
#include <string>
#include <set>
#include <map>

class KeyAction
{
	private:
		std::set<std::string> m_actions;
		std::map<int, std::string> m_pressBindings;
		std::map<int, std::string> m_releaseBindings;

	protected:
		/**
		Adds an action with the given name. The name is an arbitrary identifier that can be referenced
		during the binding and triggering of events.
		@param sActionName The name of the action to add */
		void addAction(std::string sActionName);

	public:
		/**
		This function is called by a Scene when a key with a matching modifiers bitmask whose action 
		points to this class is pressed. The function will in turn launch any associated events via
		the onAction(string) function.
		@param iKey The key code
		@param iModifiers The modifiers bitmask */
		void onKeyPressed(int iKey, int iModifiers);

		/**
		This function is called by a Scene when a key with a matching modifiers bitmask whose action 
		points to this class is released. The function will in turn launch any associated events via
		the onAction(string) function.
		@param iKey The key code
		@param iModifiers The modifiers bitmask */
		void onKeyReleased(int iKey, int iModifiers);

		/**
		Binds a key to an action. If the action did not exist, this function will fail. 
		@param iKey The key code
		@param iModifiers The modifiers bitmask
		@param iAction An enum indicating whether the action should fire on press or release
		@param sActionName The name of the action to bind to 
		@return True if the binding was successful, false otherwise */
		bool bindKeyToAction(int iKey, int iModifiers, int iAction, std::string sActionName);

		/**
		Removes a binding that matches the given action type and name. This function fails if the binding
		did not exist or the given name was unknown.
		@param iAction An enum indicating whether the action should fire on press or release
		@param sActionName The name of the action to bind to  
		@return True if a key was unbound, false otherwise */
		bool unbindKey(int iAction, std::string sActionName);
			
		/**
		This function is called when an action is triggered by a bound key press/release.
		@param sActionName The name of the action that was triggered */
		virtual void onAction(const std::string& sActionName) = 0;
};

#endif
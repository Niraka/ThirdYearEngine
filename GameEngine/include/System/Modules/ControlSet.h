/**
A ControlSet provides a method of grouping together a set of key and mouse mappings. The set can
then be assigned to a Scene and, once activated, will forward user input to the locations assigned
by the mappings.

The ControlSet can be used to build what is commonly known as "keybindings".

NOTE: It can be very easy to confuse the ControlSet with an InputListener, as their functionality
is quite similar. However, the control set is intended for directing USER input, whereas the
InputListener is intended for directing SYSTEM input.

@author Nathan */

#ifndef CONTROL_SET_H
#define CONTROL_SET_H

#include <GLFW\glfw3.h>
#include <vector>

#include "System/Modules/KeyMapping.h"
#include "System/Modules/MouseMapping.h"
#include "System/Modules/MovementMapping.h"

class ControlSet
{
	private:
		MovementMapping* m_movementMapping;
		std::vector<MouseMapping> m_mouseMappings;
		std::vector<KeyMapping> m_keyMappings;

	protected:

	public:
		/**
		Constructs a ControlSet. */
		ControlSet();

		/**
		Destructs a ControlSet. */
		~ControlSet();

		/**
		Adds a movement mapping. Existing MovementMappings are removed. */
		void addMovementMapping(MovementMapping* mapping);

		/**
		Adds a mouse mapping. A control set may only have one mapping per button per modifier
		mask. If a mapping already existed for the given button and modifiers combination, the
		new mapping overwrites the old one.
		@param iButton The button code
		@param iEventType The event type (GLFW_PRESSED or GLFW_RELEASED)
		@param iModifiers The modifiers bitmask
		@param action A pointer to a MouseAction */
		void addMouseMapping(int iButton, int iEventType, int iModifiers, MouseAction* action);
		
		/**
		Adds a key mapping. A control set may only have one mapping per key per modifier mask. 
		If a mapping already existed for the given key and modifiers combination, the new 
		mapping overwrites the old one.
		@param iKey The key code
		@param iEventType The event type (GLFW_PRESSED or GLFW_RELEASED)
		@param iModifiers The modifiers bitmask
		@param action A pointer to a KeyAction */
		void addKeyMapping(int iKey, int iEventType, int iModifiers, KeyAction* action);

		/**
		Removes a mouse mapping.
		@param iButton The button code
		@param iEventType The event type (GLFW_PRESSED or GLFW_RELEASED)
		@param iModifiers The modifiers bitmask */
		void removeMouseMapping(int iButton, int iEventType, int iModifiers);

		/**
		Removes a key mapping.
		@param iKey The key code
		@param iEventType The event type (GLFW_PRESSED or GLFW_RELEASED)
		@param iModifiers The modifiers bitmask */
		void removeKeyMapping(int iKey, int iEventType, int iModifiers);
		
		bool hasMovementMapping();

		/**
		Returns true if the control set has a mapping for the given combination. The mapping
		must also contain a valid MouseAction.
		@param iButton A reference to the button code
		@param iEventType A reference to the event type (GLFW_PRESSED or GLFW_RELEASED)
		@param iModifiers A reference to the modifiers bitmask
		@return True if the mapping existed and was valid */
		bool hasMouseMapping(const int& iButton, const int& iEventType, const int& iModifiers);

		/**
		Returns true if the control set has a mapping for the given combination. The mapping
		must also contain a valid MouseAction.
		@param iKey A reference to the key code
		@param iEventType A reference to the event type (GLFW_PRESSED or GLFW_RELEASED)
		@param iModifiers A reference to the modifiers bitmask
		@return True if the mapping existed and was valid */
		bool hasKeyMapping(const int& iKey, const int& iEventType, const int& iModifiers);

		/**
		Retrieves the MovementMapping bound to this ControlSet.
		@return The MovementMapping */
		MovementMapping* getMovementMapping();

		/**
		Retrieves the MouseAction stored at the given mouse mapping combination. If no such mouse mapping
		existed, this function returns a nullptr.
		@param iButton A reference to the button code
		@param iEventType A reference to the event type (GLFW_PRESSED or GLFW_RELEASED)
		@param iModifiers A reference to the modifiers bitmask
		@return The desired MouseAction, or a nullptr */
		MouseAction* getMouseAction(const int& iButton, int iEventType, const int& iModifiers);
		
		/**
		Retrieves the KeyAction stored at the given key mapping combination. If no such key mapping
		existed, this function returns a nullptr.
		@param iKey A reference to the key code
		@param iEventType A reference to the event type (GLFW_PRESSED or GLFW_RELEASED)
		@param iModifiers A reference to the modifiers bitmask
		@return The desired KeyAction, or a nullptr */
		KeyAction* getKeyAction(const int& iKey, int iEventType, const int& iModifiers);
};

#endif
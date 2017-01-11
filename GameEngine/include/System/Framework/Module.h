/**
A module provides the foundation for each section of the engine. It provides functions for starting,
stopping and receiving frequent updates.

@author Nathan */

#ifndef MODULE_H
#define MODULE_H

#include "System/Framework/Dependency.h"

class Module :
	public Dependency
{
	private:
		/**
		The number of times this module has been updated. This value is incremented each time update is called
		regardless of whether any processing actually took place. Thus, this value can be reliably used to
		determine whether updates are being received by this module. */
		unsigned long m_iUpdateCounter;

	protected:
		/**
		Creates a default module. */
		Module();

		/**
		Destructs the module. */
		~Module();

		/**
		Executes derived module update functionality. To update the entire module, use the public update 
		function instead. */
		virtual void onUpdate() = 0;

	public:
		/**
		Updates the module. Each time this function is called, the internal update counter is incremented. */
		void update();

		/**
		Returns the update counter, which is the number of times update has been called on this module.
		@return The update counter */
		unsigned long getUpdateCounter() const;

		/**
		Starts up the module. 
		@return True if the module started up successfully, false otherwise */
		virtual bool start() = 0;

		/**
		Stops the module.
		@return True if the module stopped successfully, false otherwise */
		virtual bool stop() = 0;
};

#endif
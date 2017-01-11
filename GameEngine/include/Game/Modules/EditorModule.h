/**
Not implemented yet.

@author Nathan */

#ifndef EDITOR_MODULE_H
#define EDITOR_MODULE_H

#include "System/Framework/Module.h"

class EditorModule :
	public Module
{
	private:

	protected:
		/**
		Updates the EditorModule. */
		void onUpdate();

	public:
		EditorModule();
		~EditorModule();

		/**
		Starts up the EditorModule.
		@return True if the module started up successfully, false otherwise */
		bool start();

		/**
		Stops the EditorModule.
		@return True if the module stopped successfully, false otherwise */
		bool stop();
};

#endif
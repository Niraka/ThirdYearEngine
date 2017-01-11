/**
A MovementMapping is an interface class that provides the necessary functionality for a class to be capable of
executing instructions in response to mouse movement. 

@author Nathan */

#ifndef MOVEMENT_MAPPING_H
#define MOVEMENT_MAPPING_H

class MovementMapping
{
	private:

	protected:

	public:
		/**
		This function is called by a Scene when the mouse is moved. 
		@param fX The mouse x position
		@param fY The mouse y position */
		virtual void onMouseMoved(double fX, double fY) = 0;
};

#endif
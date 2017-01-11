/**
An enum detailing the available window position styles.

@author Nathan */

#ifndef WINDOW_POSITION_STYLE_H
#define WINDOW_POSITION_STYLE_H

enum WindowPositionStyle
{
	FREE,        // The window will not be repositioned on creation
	TOP_LEFT,    // The top-left of the window will match the top-left of the monitor
	CENTRE       // The centre of the window will match the centre of the monitor
};

#endif
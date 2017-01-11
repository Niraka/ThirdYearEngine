/**
An enum detailing the available window styles

@author Nathan */

#ifndef WINDOW_STYLE_H
#define WINDOW_STYLE_H

enum WindowStyle
{
	WINDOWED,             // Windowed according to the operating system standard
	WINDOWED_BORDERLESS,  // Windowed minus the operating system decoration
	FULLSCREEN            // Fullscreen
};

#endif
#ifndef MUSIC_FADE_INFO_H
#define MUSIC_FADE_INFO_H

#include <SFML\Audio\Music.hpp>

struct MusicFadeInfo
{
	sf::Music* music;        // A pointer to the heap-allocated music
	double currentDuration;  // The current duration, in seconds
	double targetDuration;   // The target duration, in seconds
};

#endif
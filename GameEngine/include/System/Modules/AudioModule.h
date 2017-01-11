/**
The AudioModule is responsible for all audio based functionality within the engine.

Audio is split in to two sections: Music and Sounds

Music is long sections of audio, typically a background music track or a lengthy piece of
dialogue. It is streamed from the file system as it is necessary.

Sounds are shorter section of audio and are generally much greater in number. Examples 
include footsteps, gun shots and weather sound effects.

@author Nathan */

#ifndef AUDIO_MODULE_H
#define AUDIO_MODULE_H


#include <gl\glew.h>
#include "System/Framework/Module.h"
#include "System/Services/LoggerService.h"
#include "System/Utility/VectorInd.h"
#include "System/Modules/AudioChannel.h"
#include "System/Modules/SoundNodeListener.h"
#include "System/Utility/DirectoryListing.h"
#include "System/Modules/ResourceModule.h"
#include "System/Modules/SoundNode.h"
#include "System/Modules/MusicFadeInfo.h"

#include <map>
#include <SFML\Audio.hpp>

class AudioModule :
	public Module,
	public SoundNodeListener
{
	private:
		std::shared_ptr<SoundNode> node;   // testing only

		float m_fEffectiveMusicVolume;
		float m_fMusicVolume;
		sf::Music* m_currentMusic;
		MusicFadeInfo m_fadeInInfo;
		MusicFadeInfo m_fadeOutInfo;
		unsigned int m_uiSoundBufferResourceTypeId;
		std::string m_sAudioDirectory;
		std::shared_ptr<LoggerNode> m_loggerNode;
		std::shared_ptr<ResourceModule> m_resourceModule;
		std::map<std::string, unsigned int> m_bufferIdMap;
		std::map<std::string, std::string> m_musics;
		std::map<std::string, AudioChannel> m_audioChannels;

	protected:
		/**
		Updates the AudioModule. */
		void onUpdate();

	public:
		/**
		Constructs an AudioModule. */
		AudioModule();

		/**
		Destructs the AudioModule. */
		~AudioModule();

		/**
		Starts up the module.
		@return True if the module started up successfully, false otherwise */
		bool start();

		/**
		Stops the module.
		@return True if the module stopped successfully, false otherwise */
		bool stop();

		/**
		Loads a SoundBuffer from the given file and assigns it the given name. If the name was already in use
		by another SoundBuffer, or the file could not be loaded, this function will fail. 
		@param sFile The name of the file to load
		@param sName The name by which the sound buffer will be referred to
		@return True if the buffer was successfully loaded, false otherwise */
		bool loadSoundBuffer(const std::string& sFile, const std::string& sName);

		/**
		Loads a Music from the given file and assigns it the given name. This function will fail if the name 
		was already in use by another Music. Note that as Musics are streamed resources, the opening of the file
		will not be checked until the Music is played. 
		@param sFile The name of the file to load
		@param sName The name by which the Music will be referred to 
		@return True if the Music was successfully loaded, false otherwise */
		bool loadMusic(const std::string& sFile, const std::string& sName);

		/**
		Creates and returns a shared pointer to a SoundNode. A copy is not stored internally.
		@return A shared pointer to a SoundNode */
		std::shared_ptr<SoundNode> createSoundNode();

		/**
		Sets the position of the listener. Typically the listener is the players camera position or the players
		entity. The default position is (0, 0, 0).
		@param pos The new position */
		void setListenerPosition(glm::vec3 pos);

		/**
		Begins playing a Music with the given name. If another Music is currently playing, a fade out/fade in
		transition will be applied over the given duration. If the given music did not exist, no action is taken.
		@param sName The name of the Music to begin playing 
		@param bLoop True to make the Music loop
		@param fTransitionDuration (Optional) The duration over which the Music will transition 
		@return True if the Music successfully started playing, false otherwise */
		bool playMusic(const std::string& sName, bool bLoop, double fTransitionDuration = 0.f);

		/**
		Stops playing the current Music. If no Music was currently playing, this function does nothing. 
		@param fTransitionDuration (Optional) The duration over which the Music will fade out
		@return True if a Music was stopped, false otherwise */
		bool stopMusic(double fTransitionDuration = 0.f);

		/**
		Creates an audio channel with the given name. This function will fail if the channel already existed 
		or the name was an empty string. 
		@param sChannelName The name of the channel 
		@return True if the channel was created, false otherwise */
		bool createChannel(const std::string& sChannelName);

		/**
		Deletes an audio channel with the given name. All Sound objects within that channel are destroyed. This
		function will fail if the target channel did not exist.
		@param sChannelName The name of the channel 
		@return True if the channel was deleted, false otherwise */
		bool deleteChannel(const std::string& sChannelName); 
		
		/**
		Resets the channels to their default state. That is, all channels will be removed except for the master
		channel. The master channel will be cleared and reset to the default volume. */
		void resetChannels();

		/**
		Sets the volume of the Music. This volume is affected by the master volume. Volumes are given as values 
		between 0 and 100.
		@param fVolume The new volume */
		void setMusicVolume(float fVolume);

		/**
		Resets the volume of the Music to the default value (100). */
		void resetMusicVolume();

		/**
		Sets the volume of a channel. Modifying the volume of the master channel will modify the effective volume
		of all other channels. Volumes are given as values between 0 and 100.
		@param sChannelName The name of the channel whose volume to set 
		@param fVolume The new volume */
		void setChannelVolume(const std::string& sChannelName, float fVolume);
		
		/**
		Resets the volume of a channel to the default value (100). Modifying the volume of the master channel will 
		modify the effective volume of all other channels.
		@param sChannelName The name of the channel whose volume to reset */
		void resetChannelVolume(const std::string& sChannelName);

		/**
		This function is called by a SoundNode when it requests the creation of a Sound object. If
		this function fails for any reason, the returned value is a pair containing a nullptr and
		invalid deletion info.
		@param sChannelName The name of the channel to create the sound on
		@return A pair containing a Sound pointer and deletion info. The pointer may be a nullptr */
		std::pair<sf::Sound*, SoundDeleteInfo> onCreateSoundRequest(const std::string& sChannelName);

		/**
		This function is called by a SoundNode when it requests the deletion of a Sound object.
		@param info The information required to delete the SoundNode */
		void onDeleteSoundRequest(SoundDeleteInfo info);

		/**
		This function is called by a SoundNode when it requests a pointer to a SoundBuffer object with the given
		name. If no such SoundBuffer existed, this function returns a nullptr.
		@param sSoundBuffer The name of the sound buffer to get
		@return A pointer to a SoundBuffer, or a nullptr */
		sf::SoundBuffer* onGetSoundBufferRequest(const std::string& sSoundBuffer);

		/**
		This function is called when a service becomes available that is a dependency of this class. Note that
		the pointer is delivered as a void pointer and must first be cast to the correct service using a static
		pointer cast.
		@param serviceName The name of the service
		@param service A shared pointer to the new service */
		void serviceDependencyBecameAvailable(Services serviceName, std::shared_ptr<void> service);

		/**
		This function is called when a service that is a dependency of this class becomes unavailable.
		@param serviceName The name of the service */
		void serviceDependencyBecameUnavailable(Services serviceName);

		/**
		This function is called when a module becomes available that is a dependency of this class. Note that
		the pointer is delivered as a void pointer and must first be cast to the correct module using a
		static pointer cast.
		@param moduleName The name of the module
		@param module A shared pointer to the new module */
		void moduleDependencyBecameAvailable(Modules moduleName, std::shared_ptr<void> module);

		/**
		This function is called when a module that is a dependency of this class becomes unavailable.
		@param moduleName The name of the module */
		void moduleDependencyBecameUnavailable(Modules moduleName);
};

#endif
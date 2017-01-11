#include "System/Modules/AudioModule.h"

AudioModule::AudioModule()
{
	addServiceDependency(Services::LOGGER);
	addModuleDependency(Modules::RESOURCE);
	m_sAudioDirectory = DirectoryListing::getInstance()->getDirectory("audio");

	m_currentMusic = nullptr;
	m_fadeInInfo.music = nullptr;
	m_fadeOutInfo.music = nullptr;
}

AudioModule::~AudioModule()
{
}

void AudioModule::onUpdate()
{
	if (m_fadeInInfo.music)
	{
		if (m_fadeInInfo.currentDuration >= m_fadeInInfo.targetDuration)
		{
			m_currentMusic = m_fadeInInfo.music;
			m_fadeInInfo.music = nullptr;
		}
		else
		{
			m_fadeInInfo.currentDuration += (1.0 / 60.0);
			float fPercentComplete = (float)m_fadeInInfo.currentDuration / (float)m_fadeInInfo.targetDuration;
			m_fadeInInfo.music->setVolume(m_fEffectiveMusicVolume * fPercentComplete);
		}
	}

	if (m_fadeOutInfo.music)
	{
		if (m_fadeOutInfo.currentDuration >= m_fadeOutInfo.targetDuration)
		{
			m_fadeOutInfo.music->stop();
			delete m_fadeOutInfo.music;
			m_fadeOutInfo.music = nullptr;
		}
		else
		{
			m_fadeOutInfo.currentDuration += (1.0 / 60.0);
			float fPercentComplete = (float)m_fadeOutInfo.currentDuration / (float)m_fadeOutInfo.targetDuration;
			m_fadeOutInfo.music->setVolume(m_fEffectiveMusicVolume * (1 - fPercentComplete));
		}
	}
}

bool AudioModule::start()
{
	if (m_loggerNode)
	{
		m_loggerNode->log("Audio module launching");
	}

	resetChannels();
	resetMusicVolume();

	if (m_loggerNode)
	{
		m_loggerNode->log("Audio module successfully launched");
	}
	return true;
}

bool AudioModule::stop()
{
	if (m_loggerNode)
	{
		m_loggerNode->log("Audio module shutting down");
	}

	resetChannels();

	if (m_loggerNode)
	{
		m_loggerNode->log("Audio module successfully shut down");
	}
	m_loggerNode = nullptr;
	return true;
}

bool AudioModule::loadSoundBuffer(const std::string& sFile, const std::string& sName)
{
	if (!m_resourceModule)
	{
		return false;
	}

	if (m_bufferIdMap.find(sName) == m_bufferIdMap.end())
	{
		unsigned int uiResId = m_resourceModule->createResource(m_uiSoundBufferResourceTypeId);
		sf::SoundBuffer* buffer = m_resourceModule->getResource<sf::SoundBuffer>(m_uiSoundBufferResourceTypeId, uiResId);
		if (uiResId == 0)
		{
			return false;
		}
		else
		{
			if (buffer->loadFromFile(m_sAudioDirectory + sFile))
			{
				m_bufferIdMap.emplace(sName, uiResId);
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}
}

bool AudioModule::loadMusic(const std::string& sFile, const std::string& sName)
{
	if (m_musics.find(sName) == m_musics.end())
	{
		m_musics.emplace(sName, m_sAudioDirectory + sFile);
		return true;
	}
	else
	{
		return false;
	}
}

std::shared_ptr<SoundNode> AudioModule::createSoundNode()
{
	return std::make_shared<SoundNode>(this);
}

void AudioModule::setListenerPosition(glm::vec3 pos)
{
	sf::Listener::setPosition(pos.x, pos.y, pos.z);
}

bool AudioModule::playMusic(const std::string& sName, bool bLoop, double fTransitionDuration)
{
	if (m_musics.find(sName) == m_musics.end())
	{
		return false;
	}
	
	sf::Music* music = new sf::Music();
	if (!music->openFromFile(m_musics.at(sName)))
	{
		delete music;
		return false;
	}
	music->setLoop(bLoop);

	if (fTransitionDuration == 0.0)
	{
		// If there is a current music, stop it
		if (m_fadeInInfo.music)
		{
			m_fadeInInfo.music->stop();
			delete m_fadeInInfo.music;
			m_fadeInInfo.music = nullptr;
		}
		if (m_currentMusic)
		{
			m_currentMusic->stop();
			delete m_currentMusic;
			m_currentMusic = nullptr;
		}
		if (m_fadeOutInfo.music)
		{
			m_fadeOutInfo.music->stop();
			delete m_fadeOutInfo.music;
			m_fadeOutInfo.music = nullptr;
		}	

		m_currentMusic = music; 
		music->setVolume(m_fEffectiveMusicVolume);
	}
	else
	{
		// If there is a current music, start fading it out. 
		if (m_currentMusic)
		{
			stopMusic(fTransitionDuration);
		}

		// If there was another music fading in, set it to fade out
		// instead of the current music
		if (m_fadeInInfo.music)
		{
			//If music is already fading out, instantly stop it
			if (m_fadeOutInfo.music)
			{
				m_fadeOutInfo.music->stop();
				delete m_fadeOutInfo.music;
				m_fadeOutInfo.music = nullptr;
			}

			MusicFadeInfo info;
			info.music = m_fadeInInfo.music;
			info.currentDuration = 0;
			info.targetDuration = fTransitionDuration;
			m_fadeOutInfo = info;
		}

		// Fade in the new music
		MusicFadeInfo info;
		info.music = music;
		info.currentDuration = 0;
		info.targetDuration = fTransitionDuration;
		m_fadeInInfo = info; 
		
		music->setVolume(0);
	}

	music->play();
	return true;
}

bool AudioModule::stopMusic(double fTransitionDuration)
{
	// If it is isnt, stop the active and ending tracks
	if (fTransitionDuration == 0.0)
	{
		if (m_fadeOutInfo.music)
		{
			m_fadeOutInfo.music->stop();
			delete m_fadeOutInfo.music;
			m_fadeOutInfo.music = nullptr;
		}
		if (m_currentMusic)
		{
			m_currentMusic->stop();
			delete m_currentMusic;
			m_currentMusic = nullptr;
		}
	}

	//If music is already fading out, instantly stop it
	if (m_fadeOutInfo.music)
	{
		m_fadeOutInfo.music->stop();
		delete m_fadeOutInfo.music;
		m_fadeOutInfo.music = nullptr;
	}

	// Replace it with the new fading music
	MusicFadeInfo info;
	info.music = m_currentMusic;
	info.currentDuration = 0;
	info.targetDuration = fTransitionDuration;
	m_fadeOutInfo = info;
	m_currentMusic = nullptr;
	return true;
}

bool AudioModule::createChannel(const std::string& sChannelName)
{
	if (m_audioChannels.find(sChannelName) == m_audioChannels.end())
	{
		m_audioChannels.emplace(sChannelName, AudioChannel(sChannelName));
		m_audioChannels.at(AudioChannel::m_sMasterChannelName).addChannelListener(&m_audioChannels.at(sChannelName));
		m_audioChannels.at(sChannelName).linkMasterChannel(&m_audioChannels.at(AudioChannel::m_sMasterChannelName));
		return true;
	}
	else
	{
		return false;
	}
}

bool AudioModule::deleteChannel(const std::string& sChannelName)
{
	if (sChannelName == AudioChannel::m_sMasterChannelName)
	{
		return false;
	}

	if (m_audioChannels.find(sChannelName) != m_audioChannels.end())
	{
		m_audioChannels.at(AudioChannel::m_sMasterChannelName).removeChannelListener(&m_audioChannels.at(sChannelName));
		m_audioChannels.erase(sChannelName);
		return true;
	}
	else
	{
		return false;
	}
}

void AudioModule::resetChannels()
{
	m_audioChannels.clear();
	m_audioChannels.emplace(AudioChannel::m_sMasterChannelName, AudioChannel(AudioChannel::m_sMasterChannelName));
	m_audioChannels.at(AudioChannel::m_sMasterChannelName).linkMasterChannel(&m_audioChannels.at(AudioChannel::m_sMasterChannelName));
}

void AudioModule::setMusicVolume(float fVolume)
{
	if (fVolume > 100.f)
	{
		fVolume = 100.f;
	}
	else if (fVolume < 0.f)
	{
		fVolume = 0.f;
	}

	m_fMusicVolume = fVolume;
	m_fEffectiveMusicVolume = (m_audioChannels.at(AudioChannel::m_sMasterChannelName).getVolume() / 100.f) * m_fMusicVolume;

	if (m_currentMusic)
	{
		m_currentMusic->setVolume(m_fEffectiveMusicVolume);
	}
}

void AudioModule::resetMusicVolume()
{
	m_fMusicVolume = 100.f;
	m_fEffectiveMusicVolume = (m_audioChannels.at(AudioChannel::m_sMasterChannelName).getVolume() / 100.f) * m_fMusicVolume;

	if (m_currentMusic)
	{
		m_currentMusic->setVolume(m_fEffectiveMusicVolume);
	}
}

void AudioModule::setChannelVolume(const std::string& sChannelName, float fVolume)
{
	std::map<std::string, AudioChannel>::iterator result = m_audioChannels.find(sChannelName);
	if (result != m_audioChannels.end())
	{
		result->second.setVolume(fVolume);
	}
}

void AudioModule::resetChannelVolume(const std::string& sChannelName)
{
	std::map<std::string, AudioChannel>::iterator result = m_audioChannels.find(sChannelName);
	if (result != m_audioChannels.end())
	{
		result->second.setVolume(100.f);
	}
}

std::pair<sf::Sound*, SoundDeleteInfo> AudioModule::onCreateSoundRequest(const std::string& sChannelName)
{
	// Check the channel exists
	std::map<std::string, AudioChannel>::iterator result = m_audioChannels.find(sChannelName);
	if (result == m_audioChannels.end())
	{
		return std::make_pair(nullptr, SoundDeleteInfo());
	}

	// Generate the Sound
	unsigned int uiSoundId = result->second.createSound();

	SoundDeleteInfo info;
	info.uiIndex = uiSoundId;
	info.sChannel = sChannelName;
	return std::make_pair(result->second.getSound(uiSoundId), info);
}

void AudioModule::onDeleteSoundRequest(SoundDeleteInfo info)
{
	std::map<std::string, AudioChannel>::iterator result = m_audioChannels.find(info.sChannel);
	if (result != m_audioChannels.end())
	{
		result->second.deleteSound(info.uiIndex);
	}
}

sf::SoundBuffer* AudioModule::onGetSoundBufferRequest(const std::string& sSoundBuffer)
{
	if (!m_resourceModule)
	{
		return nullptr;
	}

	std::map<std::string, unsigned int>::iterator result = m_bufferIdMap.find(sSoundBuffer);
	if (result != m_bufferIdMap.end())
	{
		return m_resourceModule->getResource<sf::SoundBuffer>(m_uiSoundBufferResourceTypeId, result->second);
	}
	else
	{
		return nullptr;
	}
}

void AudioModule::serviceDependencyBecameAvailable(Services serviceName, std::shared_ptr<void> service)
{
	if (serviceName == Services::LOGGER)
	{
		std::shared_ptr<LoggerService> logger = std::static_pointer_cast<LoggerService>(service);
		if (logger)
		{
			m_loggerNode = logger->createLoggerNode("AU");
		}
	}
}

void AudioModule::serviceDependencyBecameUnavailable(Services serviceName)
{
	if (serviceName == Services::LOGGER)
	{
		m_loggerNode = nullptr;
	}
}

void AudioModule::moduleDependencyBecameAvailable(Modules moduleName, std::shared_ptr<void> module)
{
	if (moduleName == Modules::RESOURCE)
	{ 
		m_resourceModule = std::static_pointer_cast<ResourceModule>(module);
		m_uiSoundBufferResourceTypeId = m_resourceModule->getResourceTypeId<sf::SoundBuffer>();
	}
}

void AudioModule::moduleDependencyBecameUnavailable(Modules moduleName)
{
	if (moduleName == Modules::RESOURCE)
	{
		m_resourceModule = nullptr;
		
		// Note: We dont need to manually release the SoundBuffers from the Sounds
		// as SFML takes care of this internally
	}
}
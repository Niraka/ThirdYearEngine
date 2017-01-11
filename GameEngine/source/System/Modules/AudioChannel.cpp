#include "System/Modules/AudioChannel.h"

const std::string AudioChannel::m_sMasterChannelName = "master";

AudioChannel::AudioChannel(const std::string& sChannelName)
{
	m_masterChannel = this;
	m_fVolume = 100.0f;
	m_fEffectiveVolume = m_fVolume * (m_masterChannel->getVolume() / 100);
	m_sChannelName = sChannelName;
}

AudioChannel::~AudioChannel()
{
}

void AudioChannel::linkMasterChannel(AudioChannel* channel)
{
	m_masterChannel = channel;
	setVolume(m_fVolume);
}

float AudioChannel::getVolume() const
{
	return m_fVolume;
}

float AudioChannel::getEffectiveVolume() const
{
	return m_fEffectiveVolume;
}

const std::string& AudioChannel::getChannelName() const
{
	return m_sChannelName;
}

void AudioChannel::setVolume(float fVolume)
{	
	// Clamp. Maybe SFML does this internally though?
	if (fVolume > 100)
	{
		fVolume = 100;
	}
	else if (fVolume < 0)
	{
		fVolume = 0;
	}

	// Set the volume of this channel
	m_fVolume = fVolume;
	m_fEffectiveVolume = m_fVolume * (m_masterChannel->getVolume() / 100);
	
	unsigned int uiCrnt = 0;
	unsigned int uiSize = m_sounds.size();
	for (; uiCrnt < uiSize; ++uiCrnt)
	{
		m_sounds.get(uiCrnt).setVolume(m_fEffectiveVolume);
	}

	// Notify interested volume listeners
	uiCrnt = 0;
	uiSize = m_listeners.size();
	for (; uiCrnt < uiSize; ++uiCrnt)
	{
		m_listeners.at(uiCrnt)->onChannelVolumeChanged(m_sChannelName, m_fVolume);
	}
}

unsigned int AudioChannel::createSound()
{
	unsigned int ret = m_sounds.add(sf::Sound());
	m_sounds.get(ret).setVolume(m_fEffectiveVolume);
	m_sounds.get(ret).setAttenuation(0);
	return ret;
}

sf::Sound* AudioChannel::getSound(unsigned int uiId)
{
	if (uiId < m_sounds.size() && m_sounds.exists(uiId))
	{
		return &m_sounds.get(uiId);
	}
	else
	{
		return nullptr;
	}
}

void AudioChannel::deleteSound(unsigned int uiId)
{
	m_sounds.remove(uiId);
}

void AudioChannel::addChannelListener(AudioChannelListener* l)
{
	m_listeners.add(l);
}

void AudioChannel::removeChannelListener(AudioChannelListener* l)
{
	m_listeners.remove(l);
}

void AudioChannel::onChannelVolumeChanged(const std::string& sChannelName, float fVolume)
{
	// If the channel that launched the event was the master channel..
	if (sChannelName == m_sMasterChannelName)
	{
		// Recalculate effective volume. The master channels effective volume is the same as
		// its standard volume
		if (m_sChannelName != m_sMasterChannelName)
		{
			m_fEffectiveVolume = m_fVolume * (fVolume / 100);
		}
	}
}
#include "System/Modules/SoundNode.h"

SoundNode::SoundNode(SoundNodeListener* listener)
{
	m_listener = listener;
}

SoundNode::~SoundNode()
{
}

void SoundNode::setPosition(const glm::vec3& pos)
{
	m_position = pos;
	for (std::pair<const std::string, std::pair<sf::Sound*, SoundDeleteInfo>>& sound : m_sounds)
	{
		if (sound.second.first)
		{
			sound.second.first->setPosition(pos.x, pos.y, pos.z);
		}
	}
}

void SoundNode::setSoundLooping(const std::string& sSoundName, bool bLooping)
{
	std::map<std::string, std::pair<sf::Sound*, SoundDeleteInfo>>::iterator result = m_sounds.find(sSoundName);
	if (result != m_sounds.end())
	{
		if (result->second.first)
		{
			result->second.first->setLoop(bLooping);
		}
	}
}

void SoundNode::setSoundMinimumDistance(const std::string& sSoundName, float fDistance)
{
	std::map<std::string, std::pair<sf::Sound*, SoundDeleteInfo>>::iterator result = m_sounds.find(sSoundName);
	if (result != m_sounds.end())
	{
		if (result->second.first)
		{
			result->second.first->setMinDistance(fDistance);
		}
	}
}

void SoundNode::setSoundAttenuation(const std::string& sSoundName, float fAttenuation)
{
	std::map<std::string, std::pair<sf::Sound*, SoundDeleteInfo>>::iterator result = m_sounds.find(sSoundName);
	if (result != m_sounds.end())
	{
		if (result->second.first)
		{
			result->second.first->setAttenuation(fAttenuation);
		}
	}
}

bool SoundNode::setSoundBuffer(const std::string& sSoundName, const std::string& sBufferName)
{
	std::map<std::string, std::pair<sf::Sound*, SoundDeleteInfo>>::iterator result = m_sounds.find(sSoundName);
	if (result == m_sounds.end())
	{
		return false;
	}

	sf::SoundBuffer* buffer = m_listener->onGetSoundBufferRequest(sBufferName);
	if (buffer && result->second.first)
	{
		result->second.first->setBuffer(*buffer);
		return true;
	}
	else
	{
		return false;
	}
}

bool SoundNode::createSound(const std::string& sSoundName, const std::string& sChannelName)
{
	std::map<std::string, std::pair<sf::Sound*, SoundDeleteInfo>>::iterator result = m_sounds.find(sSoundName);
	if (result != m_sounds.end())
	{
		return false;
	}

	std::pair<sf::Sound*, SoundDeleteInfo> pair = m_listener->onCreateSoundRequest(sChannelName);
	if (pair.first != nullptr)
	{
		pair.first->setPosition(m_position.x, m_position.y, m_position.z);
		m_sounds.emplace(sSoundName, pair);
		return true;
	}
	else
	{
		return false;
	}
}

void SoundNode::deleteSound(const std::string& sSoundName)
{
	std::map<std::string, std::pair<sf::Sound*, SoundDeleteInfo>>::iterator result = m_sounds.find(sSoundName);
	if (result != m_sounds.end())
	{	
		m_listener->onDeleteSoundRequest(result->second.second);
	}
}

void SoundNode::playSound(const std::string& sSoundName)
{
	std::map<std::string, std::pair<sf::Sound*, SoundDeleteInfo>>::iterator result = m_sounds.find(sSoundName);
	if (result != m_sounds.end())
	{
		if (result->second.first)
		{
			result->second.first->play();
		}
	}
}

void SoundNode::stopSound(const std::string& sSoundName)
{
	std::map<std::string, std::pair<sf::Sound*, SoundDeleteInfo>>::iterator result = m_sounds.find(sSoundName);
	if (result != m_sounds.end())
	{
		if (result->second.first)
		{
			result->second.first->stop();
		}
	}
}
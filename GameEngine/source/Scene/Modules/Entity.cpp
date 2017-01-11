#include "Scene/Modules/Entity.h"

Entity::Entity() :
m_sMoveForward("forward"),
m_sMoveBackward("backward"),
m_sMoveLeft("left"),
m_sMoveRight("right")
{
	m_sound = nullptr;
	m_actor = nullptr;
	m_physics = nullptr;
	m_camera = nullptr;
	m_spotLight = nullptr;
	m_pointLight = nullptr;
	m_aiNode = nullptr;

	m_spotLightMode = Entity::SpotLightModes::FIRST_PERSON;
	m_cameraMode = Entity::CameraModes::FIRST_PERSON;

	addAction(m_sMoveForward);
	addAction(m_sMoveBackward);
	addAction(m_sMoveLeft);
	addAction(m_sMoveRight);
}

Entity::Entity(const EntitySpecification& spec) :
m_buildSpec(spec),
m_sMoveForward("forward"),
m_sMoveBackward("backward"),
m_sMoveLeft("left"),
m_sMoveRight("right")
{
	m_sound = nullptr;
	m_actor = nullptr;
	m_physics = nullptr;
	m_camera = nullptr;
	m_spotLight = nullptr;
	m_pointLight = nullptr;
	m_aiNode = nullptr;

	m_spotLightMode = Entity::SpotLightModes::FIRST_PERSON;
	m_cameraMode = Entity::CameraModes::FIRST_PERSON;

	addAction(m_sMoveForward);
	addAction(m_sMoveBackward);
	addAction(m_sMoveLeft);
	addAction(m_sMoveRight);
}

Entity::~Entity()
{
}

const EntitySpecification& Entity::getSpec() const
{
	return m_buildSpec;
}

EntityToken* Entity::getEntityToken()
{
	return &m_token;
}

void Entity::setFlag(EntityFlags::Flags flag, bool bValue)
{
	m_token.setFlag(flag, bValue);
}

bool Entity::getFlag(EntityFlags::Flags flag)
{
	return m_token.getFlag(flag);
}

void Entity::attachPointLight(std::shared_ptr<PointLight> light)
{
	m_pointLight = light;
	if (m_pointLight)
	{
		m_pointLight->setPosition(getPosition());
	}
}

void Entity::attachSpotLight(std::shared_ptr<SpotLight> light)
{
	m_spotLight = light;
	if (m_spotLight)
	{
		if (m_spotLightMode == Entity::SpotLightModes::FIRST_PERSON)
		{
			m_spotLight->setFacingPosition(getPosition());
		}
		else
		{
			m_spotLight->setPosition(getPosition());
		}
	}
}

void Entity::attachCamera(std::shared_ptr<Camera> camera)
{
	m_camera = camera;
	if (m_camera)
	{
		if (m_cameraMode == Entity::CameraModes::FIRST_PERSON)
		{
			m_camera->setTarget(getPosition());
		}
		else
		{
			m_camera->setTarget(getPosition());
		}
	}	
}

void Entity::attachActor(std::shared_ptr<Actor> actor)
{
	m_actor = actor;

	if (m_actor)
	{
		m_actor->setPosition(m_token.getPosition());
	}
}

void Entity::attachPhysicsNode(std::shared_ptr<PhysicsNode> node)
{
	m_physics = node;
	if (m_physics)
	{
		m_physics->setRotationalVelocity(glm::vec3(0, 2, 0));
		m_physics->setPosition(m_token.getPosition());	
	}
}

void Entity::attachSoundNode(std::shared_ptr<SoundNode> node)
{
	m_sound = node;	
	if (m_sound)
	{
		m_sound->setPosition(m_token.getPosition());
	}
}

void Entity::attachAINode(std::shared_ptr<AINode> node)
{
	m_aiNode = node;
	if (m_aiNode)
	{
		// AI nodes shouldnt have a position so this is????
		m_aiNode->setPosition(getPosition());
	}
}

void Entity::move(glm::vec3 distance)
{
	setPosition(m_token.getPosition() + distance);
}

void Entity::setPosition(glm::vec3 pos)
{
	m_token.setPosition(pos);

	if (m_actor)
	{
		m_actor->setPosition(pos);
	}

	if (m_physics)
	{
		m_physics->setPosition(pos);
	}

	if (m_sound)
	{
		m_sound->setPosition(pos);
	}

	if (m_camera)
	{
		// Currently do the same - but would implement third person cam here if I had time
		if (m_cameraMode == Entity::CameraModes::FIRST_PERSON)
		{
			m_camera->setTarget(pos);
		}
		else
		{
			m_camera->setTarget(pos);
		}
	}

	if (m_spotLight)
	{
		if (m_spotLightMode == Entity::SpotLightModes::FIRST_PERSON)
		{
			m_spotLight->setFacingPosition(pos); 
		}
		else
		{
			m_spotLight->setPosition(pos);
		}	
	}
	
	if (m_pointLight)
	{
		m_pointLight->setPosition(pos);
	}
	
	if (m_aiNode)
	{
		// AI nodes shouldnt have a position so this is????
		m_aiNode->setPosition(pos);
	}
}

glm::vec3 Entity::getPosition() const
{
	return m_token.getPosition();
}

void Entity::scale(glm::vec3 scale)
{
	setScale(m_token.getScale() + scale);
}

void Entity::setScale(glm::vec3 scale)
{
	m_token.setScale(scale);

	if (m_actor)
	{
		m_actor->setScale(scale);
	}
}

glm::vec3 Entity::getScale() const
{
	return m_token.getScale();
}

void Entity::rotate(glm::vec3 rotation)
{
	setOrientation(m_token.getOrientation() + rotation);
}

void Entity::setOrientation(glm::vec3 orientation)
{
	m_token.setOrientation(orientation);

	if (m_actor)
	{
		m_actor->setOrientation(orientation);
	}

	if (m_physics)
	{
		m_physics->setRotation(orientation);
	}

	if (m_camera)
	{
		if (m_cameraMode == CameraModes::FIRST_PERSON)
		{
			//glm::rotate
			//m_camera->setPosition()
		}
		else if (m_cameraMode == CameraModes::THIRD_PERSON)
		{

		}
	}
}

glm::vec3 Entity::getOrienation() const
{
	return m_token.getOrientation();
}

void Entity::setVisible(bool bVisible)
{
	if (m_actor)
	{
		m_actor->setVisible(bVisible);
	}
}

void Entity::render(ShaderManager& shaderManager, const RenderData& data)
{
	if (m_actor)
	{
		m_actor->render(shaderManager, data);
	}
}

void Entity::setSoundLooping(const std::string& sSoundName, bool bLooping)
{
	if (m_sound)
	{
		m_sound->setSoundLooping(sSoundName, bLooping);
	}
}

void Entity::setSoundMinimumDistance(const std::string& sSoundName, float fDistance)
{
	if (m_sound)
	{
		m_sound->setSoundMinimumDistance(sSoundName, fDistance);
	}
}

void Entity::setSoundAttenuation(const std::string& sSoundName, float fAttenuation)
{
	if (m_sound)
	{
		m_sound->setSoundAttenuation(sSoundName, fAttenuation);
	}
}

bool Entity::setSoundBuffer(const std::string& sSoundName, const std::string& sBufferName)
{
	if (m_sound)
	{
		return m_sound->setSoundBuffer(sSoundName, sBufferName);
	}
	else
	{
		return false;
	}
}

bool Entity::createSound(const std::string& sSoundName, const std::string& sChannelName)
{
	if (m_sound)
	{
		return m_sound->createSound(sSoundName, sChannelName);
	}
	else
	{
		return false;
	}
}

void Entity::deleteSound(const std::string& sSoundName)
{
	if (m_sound)
	{
		m_sound->deleteSound(sSoundName);
	}
}

void Entity::stopSound(const std::string& sSoundName)
{
	if (m_sound)
	{
		m_sound->stopSound(sSoundName);
	}
}

void Entity::playSound(const std::string& sSoundName)
{
	if (m_sound)
	{
		m_sound->playSound(sSoundName);
	}
}

void Entity::onAction(const std::string& sActionName)
{
	if (sActionName == m_sMoveForward)
	{
		move(glm::vec3(0.0, 0, 0.1));
	}	
	else if (sActionName == m_sMoveBackward)
	{
		move(glm::vec3(0.0, 0, -0.1));
	}
	else if (sActionName == m_sMoveLeft)
	{
		move(glm::vec3(0.1, 0, 0));
	}	
	else if (sActionName == m_sMoveRight)
	{
		move(glm::vec3(-0.1, 0, 0));
	}
}	

void Entity::onMouseMoved(double fX, double fY)
{
	rotate(glm::vec3(0, -fX * 0.25, 0));
}
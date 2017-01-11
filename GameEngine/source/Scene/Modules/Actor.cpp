#include "Scene/Modules/Actor.h"

const glm::vec3 Actor::m_worldX = glm::vec3(1.f, 0.f, 0.f);
const glm::vec3 Actor::m_worldY = glm::vec3(0.f, 1.f, 0.f);
const glm::vec3 Actor::m_worldZ = glm::vec3(0.f, 0.f, 1.f);

Actor::Actor()
{
	m_model = nullptr;
	m_position = glm::vec3(0.f);
	m_scale = glm::vec3(1.f);
	m_orientation = glm::vec3(0.f);
	m_bVisible = true;
}

Actor::~Actor()
{
}

Actor::Actor(std::shared_ptr<Model> model)
{
	m_model = model;
	m_bVisible = true;
}

void Actor::buildModelMatrix()
{
	m_modelMatrix = glm::mat4(1.f);
	m_modelMatrix = glm::translate(m_modelMatrix, m_position);
	m_modelMatrix = glm::rotate(m_modelMatrix, m_orientation.x, m_worldX);
	m_modelMatrix = glm::rotate(m_modelMatrix, m_orientation.y, m_worldY);
	m_modelMatrix = glm::rotate(m_modelMatrix, m_orientation.z, m_worldZ);
	m_modelMatrix = glm::scale(m_modelMatrix, m_scale);
}

void Actor::setVisible(bool bVisible)
{
	m_bVisible = bVisible;
}

bool Actor::isVisible() const
{
	return m_bVisible;
}

void Actor::move(glm::vec3 distance)
{
	m_position += distance;
	buildModelMatrix();
}

void Actor::setPosition(const glm::vec3& pos)
{
	m_position = pos;
	buildModelMatrix();
}

glm::vec3 Actor::getPosition() const
{
	return m_position;
}

void Actor::scale(glm::vec3 scale)
{
	m_scale += scale;
	buildModelMatrix();
}

void Actor::setScale(glm::vec3 scale)
{
	m_scale = scale;
	buildModelMatrix();
}

glm::vec3 Actor::getScale() const
{
	return m_scale;
}

void Actor::rotate(glm::vec3 rotation)
{
	m_orientation += rotation;
	buildModelMatrix();
}

void Actor::setOrientation(glm::vec3 orientation)
{
	m_orientation = orientation;
	buildModelMatrix();
}

glm::vec3 Actor::getOrienation() const
{
	return m_orientation;
}

void Actor::setModel(std::shared_ptr<Model> model)
{
	m_model = model;
}

void Actor::render(ShaderManager& shaderManager, const RenderData& data)
{
	if (m_model && m_bVisible)
	{
		m_model->render(shaderManager, data, m_modelMatrix);
	}
}
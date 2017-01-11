#include "Scene/Modules/Mesh.h"

Mesh::Mesh()
{	
	m_uiVertexArrayId = 0;

	m_min = glm::vec3(0.f, 0.f, 0.f);
	m_max = glm::vec3(0.f, 0.f, 0.f);
	m_centre = glm::vec3(0.f, 0.f, 0.f);
}

Mesh::~Mesh()
{
	m_uiVertexArrayId = 0;
}

glm::vec3 Mesh::getMin() const
{
	return m_min;
}

glm::vec3 Mesh::getMax() const
{
	return m_max;
}

glm::vec3 Mesh::getCentre() const
{
	return m_centre;
}

MeshGroup* Mesh::getGroup(unsigned int index)
{
	return &m_groups.at(index);
}

unsigned int Mesh::getNumGroups()
{
	return m_groups.size();
}

GLuint Mesh::getArrayId() const
{
	return m_uiVertexArrayId;
}

bool Mesh::isValid() const
{
	return m_uiVertexArrayId != 0 && m_groups.size() != 0;
}
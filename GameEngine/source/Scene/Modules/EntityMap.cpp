#include "Scene/Modules/EntityMap.h"


EntityMap::EntityMap()
{
	i = 0;
}

EntityMap::~EntityMap()
{
}

void EntityMap::addToken(EntityToken* token)
{
	m_tokens.push_back(token);
}

void EntityMap::removeToken(EntityToken* token)
{
	std::vector<EntityToken*>::iterator itCrnt = m_tokens.begin();
	std::vector<EntityToken*>::iterator itEnd = m_tokens.end();
	for (; itCrnt != itEnd; ++itCrnt)
	{
		if (*itCrnt == token)
		{
			m_tokens.erase(itCrnt);
			return;
		}
	}
}

const EntityToken* EntityMap::getNearest(glm::vec3 position)
{

	

	return nullptr;
}


const EntityToken* EntityMap::getNearestWithFlag(glm::vec3 position, EntityFlags::Flags flag)
{
	std::vector<EntityToken*>::iterator it;
	
	float store_vec;

	VectorSim<float> Dist;
	

	
	for ( it = m_tokens.begin(); it != m_tokens.end(); ++it, i++)
	 {
		store_vec = position.length() - m_tokens.at(i)->getPosition().length();
		Dist.add(store_vec);
	 }
	float f_min = m_mathsUtils.getMinimum(Dist);
	for (int i = 0; i < Dist.size(); i++)
	{
		if (f_min = m_tokens.at(i)->getPosition().length() && flag == m_tokens.at(i)->getFlag(flag))
		{
			return m_tokens.at(i);
		}
		if (flag = EntityFlags::IS_PLAYER)
		{
			return m_tokens.at(i);
		}

	}
}
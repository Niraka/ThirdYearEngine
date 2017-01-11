#include "Scene\Modules\CollisionEvent.h"
#include "Scene\Modules\HitRegion.h"

CollisionEvent::CollisionEvent()
{
	
}

CollisionEvent::~CollisionEvent()
{

}

CollisionEvent::CollisionEvent(bool intersect, glm::vec4 unitNormal, float depth, std::shared_ptr<HitRegion> collideBox)
{
	m_intersect = intersect;
	m_unitNormal = unitNormal;
	m_depth = depth;
	m_collideWith = collideBox;
}
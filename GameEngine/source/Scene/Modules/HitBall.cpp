#include "Scene\Modules\HitBall.h"
#include "Scene\Modules\HitBoxOO.h"
#include "Scene\Modules\PhysicsNode.h"
#include "Scene/Modules/PhysicsModule.h"
#include "Scene\Modules\CollisionEvent.h"

HitBall::HitBall()
{

}

HitBall::~HitBall()
{

}

HitBall::HitBall(PhysicsNode* physNode, glm::vec3 c, float r)
{
	m_parentNode = physNode;
	m_centre = c;
	m_radius = r;
}

glm::vec3 HitBall::getSize()
{
	return glm::vec3(m_radius,0,0);
}

void HitBall::setSize(glm::vec3 sz)
{
	m_radius = sz.x;
}

void HitBall::setRotation(glm::vec3 rot)
{
	//Do nothing - no point in rotating a sphere
}

glm::vec3 HitBall::getRotation()
{
	return glm::vec3(0, 0, 0);		//Returns all zero - rotating a ball makes no difference
}

CollisionEvent HitBall::collide(std::shared_ptr<HitRegion> other)
{
	return other->collide(std::make_shared<HitBall>(*this));
}

CollisionEvent HitBall::collide(std::shared_ptr<HitBall> other)
{
	glm::vec3 distVec = other->getCentre() - m_centre;		//create vector between sphere centres
	float dist = distVec.length();							//get distance between sphere centres
	float radiisum = other->getSize().x + m_radius;				//get sum of the two sphere's radii

	if (dist < radiisum)		//If the distance between them is less than the sum of the radii
	{
		glm::vec4 distVecFour(distVec.x, distVec.y, distVec.z, 1);	//convert distVec to a vec4

		return CollisionEvent(true, distVecFour / dist, abs(dist));		//A collision has occured
	}
	else
	{
		return CollisionEvent(false);		//Otherwise, no collison
	}
}

CollisionEvent HitBall::collide(std::shared_ptr<HitBoxOO> other)
{
	if (other->getRotation() == glm::vec3(0, 0, 0))		//If other is found to have zero rotation
	{
		return this->collideWithAABB(other);		//Perform AABB collison test - faster
	}
	glm::vec3 Balloldpos = m_centre;		//Save the old positions of the ball and OOBox
	glm::vec3 OOBoxoldpos = other->getCentre();

	m_centre -= other->getCentre();		//Translate ball by -OOBox position
	other->setCentre(glm::vec3(0, 0, 0));	//Set OOBox's position to origin

	//Get the 3 rotations as radians
	float angleRadsX = m_parentNode->m_parentModule->m_mathsUtils.toRadian(other->getRotation().x);
	float angleRadsY = m_parentNode->m_parentModule->m_mathsUtils.toRadian(other->getRotation().y);
	float angleRadsZ = m_parentNode->m_parentModule->m_mathsUtils.toRadian(other->getRotation().z);
	
	//Create a rotation matrix - the inverse of the oobox's rotation around X
	glm::mat4x4 rotMatrixX = m_parentNode->m_parentModule->m_mathsUtils.getRotationMatrixAroundX(-angleRadsX);

	//Create a rotation matrix - the inverse of the oobox's rotation around Y
	glm::mat4x4 rotMatrixY = m_parentNode->m_parentModule->m_mathsUtils.getRotationMatrixAroundY(-angleRadsY);

	//Create a rotation matrix - the inverse of the oobox's rotation around Z
	glm::mat4x4 rotMatrixZ = m_parentNode->m_parentModule->m_mathsUtils.getRotationMatrixAroundZ(-angleRadsZ);

	glm::vec4 centreFour(m_centre.x, m_centre.y, m_centre.z, 1);	//Convert Vec3 centre to a Vec4 - add the W component as 1

	//Apply rotations to ball's position in reverse order
	centreFour = centreFour * rotMatrixZ;
	centreFour = centreFour * rotMatrixY;
	centreFour = centreFour * rotMatrixZ;

	//Now extract the XYZ components from the Vec4 back into the m_centre Vec3
	m_centre = glm::vec3(centreFour.x, centreFour.y, centreFour.z);


	//Now apply Ball - AABox collision test as normal

	glm::vec3 dist = m_centre - other->getCentre();
	glm::vec3 clamp(0, 0, 0);

	//Clamp to within hitbox -  X
	if (dist.x >= 0)
	{
		clamp.x = m_parentNode->m_parentModule->m_mathsUtils.getMinimum(dist.x, other->getSize().x);
	}
	else if (dist.x < 0)
	{
		clamp.x = m_parentNode->m_parentModule->m_mathsUtils.getMaximum(dist.x, other->getSize().x);
	}

	//Clamp to within hitbox - Y
	if (dist.y >= 0)
	{
		clamp.y = m_parentNode->m_parentModule->m_mathsUtils.getMinimum(dist.y, other->getSize().y);
	}
	else if (dist.y < 0)
	{
		clamp.y = m_parentNode->m_parentModule->m_mathsUtils.getMaximum(dist.y, other->getSize().y);
	}

	//clamp to within hitbox - Z
	if (dist.z >= 0)
	{
		clamp.z = m_parentNode->m_parentModule->m_mathsUtils.getMinimum(dist.z, other->getSize().z);
	}
	else if (dist.x < 0)
	{
		clamp.z = m_parentNode->m_parentModule->m_mathsUtils.getMinimum(dist.z, other->getSize().z);
	}

	glm::vec3 diff = dist - clamp;		//Calculate vector between box edge and cirlce centre

	float distance = diff.length() - m_radius;		//calculate absolute distance between box edge and ball edge
	
	m_centre = Balloldpos;			//Return box and ball to original positions
	other->setCentre(OOBoxoldpos);

	if (distance <= 0)		//if distance is negative
	{
		glm::vec4 diffFour(diff.x, diff.y, diff.z, 1);	//make the difference vector a vec4
		diffFour = diffFour * m_parentNode->m_parentModule->m_mathsUtils.getRotationMatrixAroundX(angleRadsX);			//Rotate differnce vector by the 3 rotations
		diffFour = diffFour * m_parentNode->m_parentModule->m_mathsUtils.getRotationMatrixAroundY(angleRadsY);
		diffFour = diffFour * m_parentNode->m_parentModule->m_mathsUtils.getRotationMatrixAroundZ(angleRadsZ);
		float diffSize = diffFour.length();		//Calculate the size of the difference vector	
		
		return CollisionEvent(true, diffFour / diffSize, abs(distance));	//Collision has occured
	}
	else if (distance > 0)		//if distance is positive
	{
		return CollisionEvent(false);	//No collision occured
	}
}

CollisionEvent HitBall::collideWithAABB(std::shared_ptr<HitBoxOO> other)
{
	glm::vec3 dist = m_centre - other->getCentre();		//calculate vector between centres
	glm::vec3 clamp(0, 0, 0);

	//Clamp to within hitbox -  X
	if (dist.x >= 0)
	{
		clamp.x = m_parentNode->m_parentModule->m_mathsUtils.getMinimum(dist.x, other->getSize().x);
	}
	else if (dist.x < 0)
	{
		clamp.x = m_parentNode->m_parentModule->m_mathsUtils.getMaximum(dist.x, other->getSize().x);
	}

	//Clamp to within hitbox - Y
	if (dist.y >= 0)
	{
		clamp.y = m_parentNode->m_parentModule->m_mathsUtils.getMinimum(dist.y, other->getSize().y);
	}
	else if (dist.y < 0)
	{
		clamp.y = m_parentNode->m_parentModule->m_mathsUtils.getMaximum(dist.y, other->getSize().y);
	}

	//clamp to within hitbox - Z
	if (dist.z >= 0)
	{
		clamp.z = m_parentNode->m_parentModule->m_mathsUtils.getMinimum(dist.z, other->getSize().z);
	}
	else if (dist.x < 0)
	{
		clamp.z = m_parentNode->m_parentModule->m_mathsUtils.getMinimum(dist.z, other->getSize().z);
	}

	glm::vec3 diff = dist - clamp;		//Calculate vector between box edge and cirlce centre

	float distance = diff.length() - m_radius;		//calculate absolute distance between box edge and ball edge

	if (distance <= 0)		//if distance is negative
	{
		glm::vec4 diffFour(diff.x, diff.y, diff.z, 1);
		float diffSize = diff.length();
		return CollisionEvent(true, diffFour/diffSize, abs(distance));	//Collision has occured
	}
	else if (distance > 0)		//if distance is positive
	{
		return CollisionEvent(false);	//No collision occured
	}
}
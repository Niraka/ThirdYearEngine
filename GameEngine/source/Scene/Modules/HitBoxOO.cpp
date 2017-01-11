#include "Scene\Modules\HitBoxOO.h"
#include "Scene\Modules\HitBall.h"
#include "Scene\Modules\PhysicsNode.h"
#include "Scene\Modules\PhysicsModule.h"
#include "Scene\Modules\CollisionEvent.h"


HitBoxOO::HitBoxOO()
{

}

HitBoxOO::~HitBoxOO()
{

}

HitBoxOO::HitBoxOO(PhysicsNode* physNode, glm::vec3 c, glm::vec3 e, glm::vec3 r)
{
	m_parentNode = physNode;
	m_centre = c;
	m_extents = e;
	m_XRotate = r.x;
	m_YRotate = r.y;
	m_ZRotate = r.z;
}

glm::vec3 HitBoxOO::getSize()
{
	return m_extents;
}

void HitBoxOO::setSize(glm::vec3 sz)
{
	m_extents = sz;
}

void HitBoxOO::setRotation(glm::vec3 rot)
{
	m_XRotate = rot.x;
	m_YRotate = rot.y;
	m_ZRotate = rot.z;
}

glm::vec3 HitBoxOO::getRotation()
{
	return glm::vec3(m_XRotate, m_YRotate, m_ZRotate);
}

CollisionEvent HitBoxOO::collide(std::shared_ptr<HitRegion> other)
{
	return other->collide(std::make_shared<HitBoxOO>(*this));
}

CollisionEvent HitBoxOO::collide(std::shared_ptr<HitBall> other)
{
	if (m_XRotate == 0 && m_YRotate == 0 && m_ZRotate)		//if this box has no rotation
	{
		return this->collideWithBallAsAA(other);		//Perform simpler AABB to Ball test
	}

	glm::vec3 Balloldpos = other->getCentre();		//Save the old positions of the ball and OOBox
	glm::vec3 OOBoxoldpos = m_centre;

	other->setCentre(other->getCentre() - m_centre);		//Translate ball by -OOBox position
	m_centre = glm::vec3(0, 0, 0);	//Set OOBox's position to origin

	//Get the 3 rotations as radians
	float angleRadsX = m_parentNode->m_parentModule->m_mathsUtils.toRadian(m_XRotate);
	float angleRadsY = m_parentNode->m_parentModule->m_mathsUtils.toRadian(m_YRotate);
	float angleRadsZ = m_parentNode->m_parentModule->m_mathsUtils.toRadian(m_ZRotate);

	//Create a rotation matrix - the inverse of the oobox's rotation around X
	glm::mat4x4 rotMatrixX = m_parentNode->m_parentModule->m_mathsUtils.getRotationMatrixAroundX(-angleRadsX);

	//Create a rotation matrix - the inverse of the oobox's rotation around Y
	glm::mat4x4 rotMatrixY = m_parentNode->m_parentModule->m_mathsUtils.getRotationMatrixAroundY(-angleRadsY);

	//Create a rotation matrix - the inverse of the oobox's rotation around Z
	glm::mat4x4 rotMatrixZ = m_parentNode->m_parentModule->m_mathsUtils.getRotationMatrixAroundZ(-angleRadsZ);

	glm::vec4 centreFour(other->getCentre().x, other->getCentre().y, other->getCentre().z, 1);	//Convert ball's Vec3 centre to a Vec4 - add the W component as 1
		
	//Apply rotations to ball's position in reverse order
		centreFour = centreFour * rotMatrixZ;
		centreFour = centreFour * rotMatrixY;
		centreFour = centreFour * rotMatrixZ;

		//Now extract the XYZ components from the Vec4 back into the m_centre Vec3
		other->setCentre(glm::vec3(centreFour.x, centreFour.y, centreFour.z));

		//Now perform standard AAbox - Ball test

		glm::vec3 dist = other->getCentre() - m_centre;
		glm::vec3 clamp(0, 0, 0);

		//Clamp to within hitbox -  X
		if (dist.x >= 0)
		{
			clamp.x = m_parentNode->m_parentModule->m_mathsUtils.getMinimum(dist.x, m_extents.x);
		}
		else if (dist.x < 0)
		{
			clamp.x = m_parentNode->m_parentModule->m_mathsUtils.getMaximum(dist.x, m_extents.x);
		}

		//Clamp to within hitbox - Y
		if (dist.y >= 0)
		{
			clamp.y = m_parentNode->m_parentModule->m_mathsUtils.getMinimum(dist.y, m_extents.y);
		}
		else if (dist.y < 0)
		{
			clamp.y = m_parentNode->m_parentModule->m_mathsUtils.getMaximum(dist.y, m_extents.y);
		}

		//clamp to within hitbox - Z
		if (dist.z >= 0)
		{
			clamp.z = m_parentNode->m_parentModule->m_mathsUtils.getMinimum(dist.z, m_extents.z);
		}
		else if (dist.x < 0)
		{
			clamp.z = m_parentNode->m_parentModule->m_mathsUtils.getMaximum(dist.z, m_extents.z);
		}

		glm::vec3 diff = dist - clamp;		//Calculate vector between box edge and cirlce centre

		float distance = diff.length() - other->getSize().x;		//calculate absolute distance between box edge and ball edge

		m_centre = OOBoxoldpos;
		other->setCentre(Balloldpos);		//Return box and ball to original positions

		if (distance <= 0)		//if distance is negative
		{
			glm::vec4 diffFour(diff.x, diff.y, diff.z, 1);
			float diffSize = diff.length();
			return CollisionEvent(true, diffFour / diffSize, abs(distance), other);	//Collision has occured
		}
		else if (distance > 0)		//if distance is positive
		{
			return CollisionEvent(false);	//No collision occured
		}
}

CollisionEvent HitBoxOO::collide(std::shared_ptr<HitBoxOO> other)
{
	glm::vec3 dist = other->getCentre() - m_centre;		//get vector between centres

	if (dist.length() > this->getMax() + other->getMax())	//Broad phase test - treat both OOBB's as spheres with radius equal to their greatest extent
	{														//If the distance between them is greates than the sum of their radii - no collision possible
		return CollisionEvent(false);
	}

	if (m_XRotate == 0 && m_YRotate == 0 && m_ZRotate)	//if this box has no rotation
	{
		if (other->getRotation() == glm::vec3(0, 0, 0))		//and the other box has no rotation
		{
			return this->collideAsTwoAA(other);		//perform simpler AABB - AABB test
		}
	}
	//Get the 3 rotations of this OObox as radians
	float angleRadsXA = m_parentNode->m_parentModule->m_mathsUtils.toRadian(m_XRotate);
	float angleRadsYA = m_parentNode->m_parentModule->m_mathsUtils.toRadian(m_YRotate);
	float angleRadsZA = m_parentNode->m_parentModule->m_mathsUtils.toRadian(m_ZRotate);

	//Get the 3 rotations of ther other OObox as radians
	float angleRadsXB = m_parentNode->m_parentModule->m_mathsUtils.toRadian(other->getRotation().x);
	float angleRadsYB = m_parentNode->m_parentModule->m_mathsUtils.toRadian(other->getRotation().y);
	float angleRadsZB = m_parentNode->m_parentModule->m_mathsUtils.toRadian(other->getRotation().z);

	//Create a rotation matrix of this OOBox in X
	glm::mat4x4 rotMatrixXA = m_parentNode->m_parentModule->m_mathsUtils.getRotationMatrixAroundX(angleRadsXA);

	//Create a rotation matrix of this OObox in Y
	glm::mat4x4 rotMatrixYA = m_parentNode->m_parentModule->m_mathsUtils.getRotationMatrixAroundY(angleRadsYA);

	//Create a rotation matrix of this OOBox in Z
	glm::mat4x4 rotMatrixZA = m_parentNode->m_parentModule->m_mathsUtils.getRotationMatrixAroundZ(angleRadsZA);

	//-----------

	//Create a rotation matrix of the other OOBox in X
	glm::mat4x4 rotMatrixXB = m_parentNode->m_parentModule->m_mathsUtils.getRotationMatrixAroundX(angleRadsXB);

	//Create a rotation matrix of the other OObox in Y
	glm::mat4x4 rotMatrixYB = m_parentNode->m_parentModule->m_mathsUtils.getRotationMatrixAroundY(angleRadsYB);

	//Create a rotation matrix of the other OOBox in Z
	glm::mat4x4 rotMatrixZB = m_parentNode->m_parentModule->m_mathsUtils.getRotationMatrixAroundZ(angleRadsZB);

	//Calculate the co-ordinates of the eight vertices of each cube before rotation and translation
	//Cube A == this, and Cube B == other
	//p0 = -x,+y,+z | p1 = -x,+y,-z | p2 = +x,+y,-z | p3 = +x,+y,+z
	//p4 = -x,-y,+z | p5 = -x,-y,-z | p6 = +x,-y,-z | p7 = +x,-y,+z
	std::vector<glm::vec4> pA;
	pA.reserve(8);
	pA.at(0) = glm::vec4(-m_extents.x, m_extents.y, m_extents.z, 1);
	pA.at(1) = glm::vec4(-m_extents.x, m_extents.y, -m_extents.z, 1);
	pA.at(2) = glm::vec4(m_extents.x, m_extents.y, -m_extents.z, 1);
	pA.at(3) = glm::vec4(m_extents.x, m_extents.y, m_extents.z, 1);
	pA.at(4) = glm::vec4(-m_extents.x, -m_extents.y, m_extents.z, 1);
	pA.at(5) = glm::vec4(-m_extents.x, -m_extents.y, -m_extents.z, 1);
	pA.at(6) = glm::vec4(m_extents.x, -m_extents.y, -m_extents.z, 1);
	pA.at(7) = glm::vec4(m_extents.x, -m_extents.y, m_extents.z, 1);

	std::vector<glm::vec4> pB;
	pB.reserve(8);
	pB.at(0) = glm::vec4(-other->getSize().x, other->getSize().y, other->getSize().z, 1);
	pB.at(1) = glm::vec4(-other->getSize().x, other->getSize().y, -other->getSize().z, 1);
	pB.at(2) = glm::vec4(other->getSize().x, other->getSize().y, -other->getSize().z, 1);
	pB.at(3) = glm::vec4(other->getSize().x, other->getSize().y, other->getSize().z, 1);
	pB.at(4) = glm::vec4(-other->getSize().x, -other->getSize().y, other->getSize().z, 1);
	pB.at(5) = glm::vec4(-other->getSize().x, -other->getSize().y, -other->getSize().z, 1);
	pB.at(6) = glm::vec4(other->getSize().x, -other->getSize().y, -other->getSize().z, 1);
	pB.at(7) = glm::vec4(other->getSize().x, -other->getSize().y, other->getSize().z, 1);

	//Now multiply each vertex of each cube by their rotation matrices
	//OOBox A
	for (int i = 0; i < 8; ++i)
	{
		pA[i] = pA[i] * rotMatrixXA;
		pA[i] = pA[i] * rotMatrixYA;
		pA[i] = pA[i] * rotMatrixZA;

		pB[i] = pB[i] * rotMatrixXB;
		pB[i] = pB[i] * rotMatrixYB;
		pB[i] = pB[i] * rotMatrixZB;
	}

	//Now translate each vertex of each box by the OObox's centre
	for (int i = 0; i < 8; ++i)
	{
		pA[i] = pA[i] + glm::vec4(m_centre.x, m_centre.y, m_centre.z, 0);
		pB[i] = pB[i] + glm::vec4(other->getCentre().x, other->getCentre().y, other->getCentre().z, 0);
	}

	//Next step is to project onto axis - use box A XYZ and box B XYZ
	//Create an array of test axes - parralel to edges in each box
	glm::vec4 currentTestAxis[6];
	currentTestAxis[0] = pA[6] - pA[5];
	currentTestAxis[1] = pA[1] - pA[5];		
	currentTestAxis[2] = pA[4] - pA[5];		
	currentTestAxis[3] = pB[6] - pB[5];		
	currentTestAxis[4] = pB[1] - pB[5];		
	currentTestAxis[5] = pB[4] - pB[5];

	for (int i = 0; i < 6; ++i)
	{
		if (testThisAxis(currentTestAxis[i], pA, pB, m_centre, other->getCentre()))		//if the tested axis seperates them
		{
			return CollisionEvent(false);			//No collision
		}
	}
	//if all tests have failed - assume collision
	glm::vec3 distVec = other->getCentre() - m_centre;	//get vector between centres
	glm::vec4 distVecFour(distVec.x, distVec.y, distVec.z, 1);		//convert to a vec4
	float sz = distVecFour.length();
	float dpth = abs((distVec - (other->getSize() - m_extents)).length());		//calculate collision depth
	return CollisionEvent(true, distVecFour/sz, dpth);


}

CollisionEvent HitBoxOO::collideAsTwoAA(std::shared_ptr<HitBoxOO> other)
{
	glm::vec3 distVec = other->getCentre() - m_centre;		//Vector from A to B

	if (abs(distVec.x) < (m_extents.x + other->getSize().x))		//If X component of distVec is less than sum of X extents
	{
		glm::vec4 distVecFour(distVec.x, distVec.y, distVec.z, 1);
		float sz = distVecFour.length();
		return CollisionEvent(true, distVecFour / sz, abs(distVec.x - m_extents.x + other->getSize().x));
	}
	else if (abs(distVec.y) < (m_extents.y + other->getSize().y))	//If Y component of distVec is less than sum of Y extents
	{
		glm::vec4 distVecFour(distVec.x, distVec.y, distVec.z, 1);
		float sz = distVecFour.length();
		return CollisionEvent(true, distVecFour / sz, abs(distVec.y - m_extents.y + other->getSize().y));
	}
	else if (abs(distVec.z) < (m_extents.z + other->getSize().z))	//If Z component of distVec is less than sum of Z extents
	{
		glm::vec4 distVecFour(distVec.x, distVec.y, distVec.z, 1);
		float sz = distVecFour.length();
		return CollisionEvent(true, distVecFour/sz, abs(distVec.z - m_extents.z + other->getSize().z));
	}
	else
	{											//If no intersection was found
		return CollisionEvent(false);			//Return false
	}
}

CollisionEvent HitBoxOO::collideWithBallAsAA(std::shared_ptr<HitBall> other)
{
	glm::vec3 dist = other->getCentre() - m_centre;
	glm::vec3 clamp(0, 0, 0);

	//Clamp to within hitbox -  X
	if (dist.x >= 0)
	{
	clamp.x = m_parentNode->m_parentModule->m_mathsUtils.getMinimum(dist.x, m_extents.x);
	}
	else if (dist.x < 0)
	{
	clamp.x = m_parentNode->m_parentModule->m_mathsUtils.getMaximum(dist.x, m_extents.x);
	}

	//Clamp to within hitbox - Y
	if (dist.y >= 0)
	{
		clamp.y = m_parentNode->m_parentModule->m_mathsUtils.getMinimum(dist.y, m_extents.y);
	}
	else if (dist.y < 0)
	{
		clamp.y = m_parentNode->m_parentModule->m_mathsUtils.getMaximum(dist.y, m_extents.y);
	}

	//clamp to within hitbox - Z
	if (dist.z >= 0)
	{
		clamp.z = m_parentNode->m_parentModule->m_mathsUtils.getMinimum(dist.z, m_extents.z);
	}
	else if (dist.x < 0)
	{
		clamp.z = m_parentNode->m_parentModule->m_mathsUtils.getMaximum(dist.z, m_extents.z);
	}

	glm::vec3 diff = dist - clamp;		//Calculate vector between box edge and cirlce centre

	float distance = diff.length() - other->getSize().x;		//calculate absolute distance between box edge and ball edge

	if (distance <= 0)		//if distance is negative
	{
		glm::vec4 diffFour(diff.x, diff.y, diff.z, 1);		//Convert diff vector to a vec4
		float sz = diffFour.length();
		return CollisionEvent(true, diffFour / sz, abs(distance));	//Collision has occured
	}
	else if (distance > 0)		//if distance is positive
	{
		return CollisionEvent(false);	//No collision occured
	}
	
}

float HitBoxOO::getMax()
{
	VectorSim<float> values;
	values.add(m_extents.x);
	values.add(m_extents.y);
	values.add(m_extents.z);		//store each extent in a VectorSim
	return m_parentNode->m_parentModule->m_mathsUtils.getMaximum(values);	//return the highest value
}
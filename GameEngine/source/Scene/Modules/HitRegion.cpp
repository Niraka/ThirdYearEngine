#include "Scene/Modules/HitRegion.h"
#include "Scene\Modules\PhysicsNode.h"
#include "Scene/Modules/PhysicsModule.h"


HitRegion::HitRegion()
{

}

HitRegion::~HitRegion()
{

}

void HitRegion::setCentre(glm::vec3 newCent)
{
	m_centre = newCent;
}

glm::vec3 HitRegion::getCentre()
{
	return m_centre;
}

bool HitRegion::getActive()
{
	return m_active;
}

void HitRegion::setActive(bool act)
{
	m_active = act;
}

//function to use to test an axis against the boxes, returns true if the axis seperates them
bool HitRegion::testThisAxis(glm::vec4 testAxis, std::vector<glm::vec4> pointsA, std::vector<glm::vec4> pointsB, glm::vec3 centreA, glm::vec3 centreB)
{

	//Make the axis a unit vector
	float axisLength = testAxis.length();
	testAxis.x = testAxis.x / axisLength;
	testAxis.y = testAxis.y / axisLength;
	testAxis.z = testAxis.z / axisLength;

	//Dot product each vertex with the axis to project it
	VectorSim<float> pAProject;
	VectorSim<float> pBProject;
	

	int vecSize = pointsA.size();
	for (int i = 0; i < vecSize; ++i)
	{
		pAProject.at(i) = ((pointsA.at(i).x * testAxis.x) + (pointsA.at(i).x * testAxis.y) + (pointsA.at(i).z * testAxis.z));
		pBProject.at(i) = ((pointsB.at(i).x * testAxis.x) + (pointsB.at(i).x * testAxis.y) + (pointsB.at(i).z * testAxis.z));
	}


	//project centres onto axis 
	float ACentreProject = ((centreA.x * testAxis.x) + (centreA.y * testAxis.y) + (centreA.z * testAxis.z));
	float BCentreProject = ((centreB.x * testAxis.x) + (centreB.y * testAxis.y) + (centreB.z * testAxis.z));

	//Char to store if A is left 'L' or right 'R' of B
	char leftRight;
	if (ACentreProject < BCentreProject)		//If A is left of B on axis
	{
		leftRight = 'L';
	}
	else
	{
		leftRight = 'R';
	}

	if (leftRight == 'L')		//if A is left of B on the test axis
	{
		float AMax = m_parentNode->m_parentModule->m_mathsUtils.getMaximum(pAProject);		//get maximum of A along axis
		float BMin = m_parentNode->m_parentModule->m_mathsUtils.getMinimum(pBProject);		//get minimum of B along axis
		if (AMax < BMin)
		{
			return true;
		}
	}
	else if (leftRight == 'R')	//if A is right of B on the test axis
	{
		float AMin = m_parentNode->m_parentModule->m_mathsUtils.getMinimum(pAProject);		//get minimum of A along axis
		float BMax = m_parentNode->m_parentModule->m_mathsUtils.getMaximum(pBProject);		//get maximum of B along axis
		if (AMin > BMax)
		{
			return true;
		}
	}

	return false;
}

PhysicsNode* HitRegion::getParent()
{
	return m_parentNode;
}
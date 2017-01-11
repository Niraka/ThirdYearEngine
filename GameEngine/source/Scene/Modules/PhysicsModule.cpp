#include "Scene/Modules/PhysicsModule.h"

PhysicsModule::PhysicsModule()
{
	m_mapMax = 1000;
	m_maxPosition = glm::vec3(m_mapMax, m_mapMax, m_mapMax);		//Map is currently assumed to be no bigger than 1000 units cubed, and exsists only in the positive axis
	m_maxPosition = glm::vec3(0,0,0);
	m_updateRate = 0.03125f;		//Current update rate is 1/32 seconds

	addServiceDependency(Services::LOGGER);	
	addModuleDependency(Modules::TIMING);
}

PhysicsModule::~PhysicsModule()
{
}

void PhysicsModule::onUpdate()
{
	
}

void PhysicsModule::updatePhysics()
{
	if (m_active)		//If physics are currently active
	{

		std::map<std::string, std::shared_ptr<PhysicsNode>>::iterator mapIt;

		for (mapIt = m_PhysNodeHodler.begin(); mapIt != m_PhysNodeHodler.end(); ++mapIt)
		{
			mapIt->second->update(m_updateRate);		//update every PhysicsNode
		}
	}

	this->generateCubeGrid();		//Regenerate the cubegrid
	std::shared_ptr<Timer> timer = std::make_shared<Timer>("update_physics", m_updateRate);	//Create a new timer to go off for the next update
	m_timingModule->addTimer(timer);
}

std::shared_ptr<PhysicsNode> PhysicsModule::createNode(std::string idname, glm::vec3 exts, HitRegionTypes hitReg, glm::vec3 p, glm::vec3 v, float maxS, glm::vec3 a, glm::vec3 r, glm::vec3 rv, bool mov, bool coll)
{
	std::shared_ptr<PhysicsNode> newNode = std::make_shared<PhysicsNode>(this, idname, exts, hitReg, p, v, maxS, a, r, rv, mov, coll);
	m_PhysNodeHodler.insert(std::pair<std::string, std::shared_ptr<PhysicsNode>>(idname, newNode));
	return newNode;
}

void PhysicsModule::setActive(bool act)
{
	m_active = act;
}

bool PhysicsModule::getActive()
{
	return m_active;
}

void PhysicsModule::generateCubeGrid()
{
	//Empty the old cubegrid
	for (int i = 0; i < 5; ++i)	//for all items in the x row
	{
		for (int j = 0; j < 5; ++j)	//for all items in the y row
		{
			for (int k = 0; k < 5; ++k)		//for all items in the z row
			{
				m_cubeGrid.at(i).at(j).at(k).clear();		//clear the old data				
			}
		}
	}
	
	std::map<std::string, std::shared_ptr<PhysicsNode>>::iterator mapIt;	//create an iterator for the map
	for (mapIt = m_PhysNodeHodler.begin(); mapIt != m_PhysNodeHodler.end(); ++mapIt)
	{
		glm::vec3 nodePos(mapIt->second->getPosition());		//get the node's position
		int divider = m_mapMax / 5;	//Maximum point / number of grid squares, divide each position by the divider and chop off the decimal to get grid square
		int x = nodePos.x / divider;
		int y = nodePos.y / divider;
		int z = nodePos.z / divider;
		m_cubeGrid.at(x).at(y).at(z).add(mapIt->second);	//Add this node to the relevant cubegrid location
	}
}

VectorSim<std::shared_ptr<PhysicsNode>>* PhysicsModule::getGridSqaure(int x, int y, int z)
{
	return &m_cubeGrid.at(x).at(y).at(z);
}

VectorSim<std::shared_ptr<PhysicsNode>> PhysicsModule::getReleventNodes(PhysicsNode* physNode)
{
	VectorSim<std::shared_ptr<PhysicsNode>> returnVec;		//create a vector to return
	glm::vec3 nodePos = physNode->getPosition();		//get the position of the asking node
	int divider = m_mapMax / 5;			//Maximum point / number of grid squares, divide each position by the divider and chop off the decimal to get grid square
	int x = nodePos.x / divider;
	int y = nodePos.y / divider;		//Calculate what cube grid this node is in
	int z = nodePos.z / divider;


	for (int i = -1; i < 2; ++i)		//this loop checks the calling node's cube grid, and all surrounding cube grid sqaures
	{
		for (int j = -1; j < 2; ++j)
		{
			for (int k = -1; k < 2; ++k)
			{
				if (x+i >= 0 && x+i < 5)	//if x is within scope
				{
					if (y + j >= 0 && y + j < 5)	//and y is within scope
					{
						if (z + k >= 0 && z + k < 5)	//and k is within scope
						{
							returnVec.append(m_cubeGrid.at(x+i).at(x+j).at(x+k));	//add the current checking node in our cube grid to the return vec
						}
					}
				}
			}
		}
	}

	return returnVec;	//return the vector of nodes we found

}

void PhysicsModule::onTimerExpired(std::string sTimer)
{
	if (sTimer == "update_physics")
	{
		this->updatePhysics();
	}
}

void PhysicsModule::moduleDependencyBecameAvailable(Modules moduleName, std::shared_ptr<void> module)
{
	if (moduleName == Modules::TIMING)
	{
		m_timingModule = std::static_pointer_cast<TimingModule>(module);

		if (m_timingModule)
		{
			std::shared_ptr<Timer> timer = std::make_shared<Timer>("update_physics", m_updateRate);	//Create a timer to time for physics updates - currently 1/32 seconds
			m_timingModule->addTimer(timer);
			m_timingModule->addTimerListener(this);
		}
	}
}

void PhysicsModule::moduleDependencyBecameUnavailable(Modules moduleName)
{
	if (moduleName == Modules::TIMING)
	{
		m_timingModule = nullptr;
	}
}

bool PhysicsModule::start()
{
	if (m_loggerNode)
	{
		m_loggerNode->log("Physics module launching");
	}

	//PhysicsModule startup actions

	if (m_loggerNode)
	{
		m_loggerNode->log("Physics module successfully launched");
	}
	return true;
}

bool PhysicsModule::stop()
{
	return true;
}

void PhysicsModule::serviceDependencyBecameAvailable(Services serviceName, std::shared_ptr<void> service)
{
	if (serviceName == Services::LOGGER)
	{
		std::shared_ptr<LoggerService> loggerService = std::static_pointer_cast<LoggerService>(service);
		if (loggerService)
		{
			m_loggerNode = loggerService->createLoggerNode("PH");
		}
	}
}

void PhysicsModule::serviceDependencyBecameUnavailable(Services serviceName)
{
	if (serviceName == Services::LOGGER)
	{
		m_loggerNode = nullptr;
	}
}

glm::vec3 PhysicsModule::getMaxPos()
{
	return m_maxPosition;
}

glm::vec3 PhysicsModule::getMinPos()
{
	return m_minPosition;
}
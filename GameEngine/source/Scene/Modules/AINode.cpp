#include "Scene\Modules\AINode.h"

AINode::AINode()
{

}
AINode::~AINode()
{

}

AIRequestedNode AINode::processAI()
{
	startAIBehaviour();
	AIRequestedNode node;

	for (std::shared_ptr<Behaviour>& currentBehaviour : m_behaviours)
	{
		currentBehaviour->onUpdate(node);
	}

	return node;
}


void AINode::addAIBehaviour(Behaviour::m_Behaviours AIb)
{
	switch (AIb)
	{
	case Behaviour::WANDER:
		for (std::shared_ptr<Behaviour>& currentBehaviour : m_behaviours)
		{
			currentBehaviour->b_wander = true;
		}
		//removeAIBehaviour(Behaviour::SEEK);
		//removeAIBehaviour(Behaviour::AVOID);
		break;
	case Behaviour::SEEK:
		for (std::shared_ptr<Behaviour>& currentBehaviour : m_behaviours)
		{
			currentBehaviour->b_seek = true;
		}
		//removeAIBehaviour(Behaviour::WANDER);
		//removeAIBehaviour(Behaviour::AVOID);
		break;
	case Behaviour::AVOID:
		for (std::shared_ptr<Behaviour>& currentBehaviour : m_behaviours)
		{
			currentBehaviour->b_avoid= true;
		}
		//removeAIBehaviour(Behaviour::WANDER);
		//removeAIBehaviour(Behaviour::SEEK);
		break;
	default:
		break;
	}

}

void AINode::startAIBehaviour()
{
	for (std::shared_ptr<Behaviour>& currentBehaviour : m_behaviours)
	{
		currentBehaviour->start();
	}
}

void AINode::removeAIBehaviour(Behaviour::m_Behaviours AIb)
{
	switch (AIb)
	{
	case Behaviour::WANDER:
		for (std::shared_ptr<Behaviour>& currentBehaviour : m_behaviours)
		{
			currentBehaviour->b_wander = false;
		}
		break;
	case Behaviour::SEEK:
		for (std::shared_ptr<Behaviour>& currentBehaviour : m_behaviours)
		{
			currentBehaviour->b_seek = false;
		}
		break;
	case Behaviour::AVOID:
		for (std::shared_ptr<Behaviour>& currentBehaviour : m_behaviours)
		{
			currentBehaviour->b_avoid = false;
		}
		break;
	default:
		break;
	}
}
void AINode::initialiseAIBehaviour()
{
	for (std::shared_ptr<Behaviour>& currentBehaviour : m_behaviours)
	{
		currentBehaviour->initialise();
	}
}

void AINode::setPosition(glm::vec3 position)
{
	m_position = position;
}


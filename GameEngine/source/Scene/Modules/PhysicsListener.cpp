#include "Scene\Modules\PhysicsListener.h"
#include "Scene\Modules\PhysicsNode.h"

PhysicsListener::PhysicsListener()
{

}

PhysicsListener::~PhysicsListener()
{

}

void PhysicsListener::registerMe(std::shared_ptr<PhysicsNode> listenNode)
{
	listenNode->addListener(this);
}
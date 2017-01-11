#include "System/Framework/Module.h"

Module::Module()
{
	m_iUpdateCounter = 0;
}

Module::~Module()
{
}

void Module::update()
{
	// Update the module
	onUpdate();

	// Increment the update counter
	++m_iUpdateCounter;
}

unsigned long Module::getUpdateCounter() const
{
	return m_iUpdateCounter;
}
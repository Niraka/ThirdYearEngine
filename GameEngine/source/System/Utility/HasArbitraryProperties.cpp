#include "System/Utility/HasArbitraryProperties.h"

HasArbitraryProperties::HasArbitraryProperties()
{
}

HasArbitraryProperties::~HasArbitraryProperties()
{
}

bool HasArbitraryProperties::hasProperty(std::string sProperty)
{
	return m_properties.find(sProperty) != m_properties.end();
}

bool HasArbitraryProperties::addProperty(std::string sProperty)
{
	if (!hasProperty(sProperty))
	{
		m_properties.emplace(sProperty);
		return true;
	}
	return false;
}

bool HasArbitraryProperties::removeProperty(std::string sProperty)
{
	return m_properties.erase(sProperty) == 1;
}

unsigned int HasArbitraryProperties::getId()
{
	return 0;
}

void HasArbitraryProperties::launchEventPropertyModified(std::string sProperty)
{
	unsigned int uiCrnt = 0;
	unsigned int uiSize = m_listeners.size();
	ArbitraryProperty prop = getValue(sProperty);
	prop.setId(getId());
	for (; uiCrnt < uiSize; ++uiCrnt)
	{
		m_listeners.at(uiCrnt)->onPropertyModified(prop);
	}
}

void HasArbitraryProperties::addPropertyListener(ArbitraryPropertyListener* l)
{
	m_listeners.add(l);
}

void HasArbitraryProperties::removePropertyListener(ArbitraryPropertyListener* l)
{
	m_listeners.remove(l);
}
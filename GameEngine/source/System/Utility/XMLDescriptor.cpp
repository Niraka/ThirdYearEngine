#include "System/Utility/XMLDescriptor.h"

XMLDescriptor::XMLDescriptor()
{
}

XMLDescriptor::~XMLDescriptor()
{
}

void XMLDescriptor::addElement(const std::string& sElement)
{
	m_elements.emplace(sElement);
}

bool XMLDescriptor::hasElement(const std::string& sElement)
{
	return m_elements.find(sElement) != m_elements.end();
}
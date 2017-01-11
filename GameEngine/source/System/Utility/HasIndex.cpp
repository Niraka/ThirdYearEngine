#include "System/Utility/HasIndex.h"

HasIndex::HasIndex(bool bLocked)
{
	m_bLocked = bLocked;
	m_bIsSet = false;
}

HasIndex::~HasIndex()
{
}

void HasIndex::setIndex(unsigned int uiIndex)
{
	if (m_bLocked && !m_bIsSet)
	{
		m_uiIndex = uiIndex;
		m_bIsSet = true;
	}
	else
	{
		m_uiIndex = uiIndex;
	}
}

const unsigned int& HasIndex::getIndex() const
{
	return m_uiIndex;
}
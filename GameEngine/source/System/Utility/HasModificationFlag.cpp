#include "System/Utility/HasModificationFlag.h"

HasModificationFlag::HasModificationFlag()
{
	m_bModifiedFlag = false;
}

bool HasModificationFlag::hasBeenModified()
{
	if (m_bModifiedFlag)
	{
		m_bModifiedFlag = false;
		return true;
	}
	else
	{
		return false;
	}
}
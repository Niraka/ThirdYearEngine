#ifndef ARBITRARY_PROPERTY_LISTENER_H
#define ARBITRARY_PROPERTY_LISTENER_H

#include <string>
#include "System/Utility/ArbitraryProperty.h"

class ArbitraryPropertyListener
{
	private:

	protected:

	public:
		virtual void onPropertyModified(const ArbitraryProperty& prop) = 0;
};

#endif
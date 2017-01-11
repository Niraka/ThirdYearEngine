#ifndef HAS_ARBITRARY_PROPERTIES_H
#define HAS_ARBITRARY_PROPERTIES_H

#include "System/Utility/ArbitraryPropertyListener.h"
#include "System/Utility/ArbitraryProperty.h"
#include "System/Utility/VectorSim.h"

#include <string>
#include <set>

class HasArbitraryProperties
{
	private:
		std::set<std::string> m_properties;
		VectorSim<ArbitraryPropertyListener*> m_listeners;

	protected:

	public:
		HasArbitraryProperties();
		~HasArbitraryProperties();

		bool hasProperty(std::string sProperty);
		bool addProperty(std::string sProperty);
		bool removeProperty(std::string sProperty);
		void launchEventPropertyModified(std::string sProperty);

		void addPropertyListener(ArbitraryPropertyListener* l);
		void removePropertyListener(ArbitraryPropertyListener* l);

		virtual unsigned int getId();
		virtual ArbitraryProperty getValue(const std::string& sProperty) = 0;
};

#endif
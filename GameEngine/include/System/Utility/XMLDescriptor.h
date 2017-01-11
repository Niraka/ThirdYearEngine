/**
The XMLDescriptor stores a set of std::string elements that can be used to determine
whether elements loaded from an XML file are valid.

The descriptor is used in two stages. First, it is built using the addElement
function as many times as necessary. For example:

std::string sString1 = "num_lights";
std::string sString2 = "num_cameras";
addElement(sString1);
addElement(sString2);

Secondly, the descriptor is queried whilst an XML file is being read to determine
whether the parsed element is a valid element. For example:

for (elements in document)
{
	if (descriptor.hasElement(element.getName()))
	{
		do something
	}
}

@author Nathan */

#ifndef XML_DESCRIPTOR_H
#define XML_DESCRIPTOR_H

#include <string>
#include <set>

class XMLDescriptor
{
	private:
		std::set<std::string> m_elements;

	protected:
	public:
		/**
		Constructs an XMLDescriptor. */
		XMLDescriptor();

		/**
		Destructs an XMLDescriptor. */
		~XMLDescriptor();

		/**
		Adds an element to the descriptor.
		@param sElement A constant reference to the name of the element */
		void addElement(const std::string& sElement);

		/**
		Returns true if the descriptor contained the desired element. 
		@param sElement A constant reference to the name of the element to query
		@return True if the descriptor contained the element */
		bool hasElement(const std::string& sElement);
};

#endif
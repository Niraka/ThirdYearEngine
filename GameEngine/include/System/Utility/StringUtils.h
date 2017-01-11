/**
Various string orientated utilities. 

@author Nathan */

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <sstream>
#include <vector>

class StringUtils
{
	private:

	protected:

	public:
		/**
		Constructs a String Utils object. */
		StringUtils();

		/**
		Destructs a String Utils objects. */
		~StringUtils();

		/**
		Converts a string to a float. If the given string could not be converted,
		a value of 0 is returned instead.
		@param s The string to convert
		@return A float value */
		float toFloat(const std::string& s);

		/**
		Converts a string to an integer. If the given string could not be converted,
		a value of 0 is returned instead.
		@param s The string to convert
		@return An integer value */
		int toInt(const std::string& s);

		/**
		Converts a string to a bool. If the given string could not be converted,
		a value of false is returned instead.
		@param s The string to convert
		@return A bool value */
		bool toBool(const std::string& s);

		/**
		Splits a string using the given split character. 
		@param s The string to split
		@param cSplitChar The character to split the string at
		@return A vector of strings containing the split string */
		std::vector<std::string> splitString(std::string& s, char cSplitChar);
};

#endif
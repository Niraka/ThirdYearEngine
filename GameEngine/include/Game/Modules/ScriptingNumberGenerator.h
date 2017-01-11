/**
A floating point number generator for use as part of the ScriptingModules functionality.

@author Nathan */

#ifndef SCRIPTING_NUMBER_GENERATOR_H
#define SCRIPTING_NUMBER_GENERATOR_H

#include <random>

class ScriptingNumberGenerator
{
	private:
		std::mt19937 m_generator;
		std::uniform_real_distribution<float> m_distributor;

	protected:

	public:
		/**
		Constructs a ScriptingNumberGenerator. */
		ScriptingNumberGenerator();

		/**
		Destructs the ScriptingNumberGenerator. */
		~ScriptingNumberGenerator();

		/**
		Returns a floating point value between the given lower and upper bounds. Returns -1
		if the upper bound is less than or equal to the lower bound.
		@param fLower The lower bound
		@param fUpper The upper bound 
		@return A generated float, or -1 */
		float getValue(float fLower, float fUpper);

		/**
		Returns an integer value between the given lower and upper bounds. Returns -1 if the 
		upper bound is less than or equal to the lower bound.
		@param iLower The lower bound
		@param iUpper The upper bound
		@return A generated integer, or -1 */
		int getValue(int iLower, int iUpper);
};

#endif
/**
Various mathematical utility functions. 

@author Nathan + Wade */

#ifndef MATHS_UTILS_H
#define MATHS_UTILS_H

#include <System\Utility\VectorSim.h>
#include <glm/glm.hpp>

class MathsUtils
{
	private:
		float m_fPiLowPres;
		double m_fPiHighPres;

	protected:
	public:
		/**
		Constructs a MathUtils object. */
		MathsUtils();

		/**
		Destructs a MathUtils object. */
		~MathsUtils();

		/**
		Clamps a given value between a maximum and minimum boundary.
		@param fMin The minimum value
		@param fMax The maximum value
		@param fValue The value to evaluate
		@return A value between the minimum and maximum values */
		float clamp(float fMin, float fMax, float fValue);

		/**
		Converts a value from radians to degrees.
		@param fRadian A value in radians
		@return The value in degrees */
		float toDegree(float fRadian) const;

		/**
		Converts a value from degrees to radians.
		@param fDegree A value in degrees
		@return The value as radians */
		float toRadian(float fDegree) const;

		/**
		Gets a low precision representation of pi.
		@return A low precision representation of pi */
		float getPi() const;

		/**
		Gets a high precision representation of pi. 
		@return A high precision representation of pi */
		double getPiHighPres() const;

		/**
		Returns the minimum from a given pair of values
		@param a The first value to compare
		@param b The second value to compare
		@return  The value that is lower */
		float getMinimum(float a, float b);

		/**
		Returns the minimum from a given VectorSim of values
		@param values The vector of values to compare
		@return The lowest value in the VectorSim */
		float getMinimum(VectorSim<float> values);		

		/**
		Returns the maximum from a given pair of values
		@param a The first value to compare
		@param b The second value to compare
		@return The value that is higher */
		float getMaximum(float a, float b);

		/**
		Returns the maximum from a given vector of values
		@param values The vector of values to compare
		@return The highest value in the vector */
		float getMaximum(VectorSim<float> values);

		/**
		Generate a 4x4 rotation matrix for a rotation around the X axis
		@param angleRads The angle to rotate by, in radians */
		glm::mat4 getRotationMatrixAroundX(float angleRads);

		/**
		Generate a 4x4 rotation matrix for a rotation around the Y axis
		@param angleRads The angle to rotate by, in radians */
		glm::mat4 getRotationMatrixAroundY(float angleRads);

		/**
		Generate a 4x4 rotation matrix for a rotation around the Z axis
		@param angleRads The angle to rotate by, in radians */
		glm::mat4 getRotationMatrixAroundZ(float angleRads);

		/**
		@param vec The vector to convert
		@return The given vector as a unit vector */
		glm::vec3 asUnit(glm::vec3 vec);

		/**
		@param a The first vector
		@param b The second vector
		@return The dot product of a*b */
		float dotProduct(glm::vec3 a, glm::vec3 b);

};

#endif
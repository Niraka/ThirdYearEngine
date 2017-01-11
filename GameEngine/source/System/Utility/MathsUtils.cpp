#include "System/Utility/MathsUtils.h"

MathsUtils::MathsUtils()
{
	m_fPiLowPres = 3.141592;
	m_fPiHighPres = 3.14159265358979;
}

MathsUtils::~MathsUtils()
{
}

float MathsUtils::clamp(float fMin, float fMax, float fValue)
{
	if (fValue < fMin)
	{
		return fMin;
	}
	else if (fValue > fMax)
	{
		return fMax;
	}
	else
	{
		return fValue;
	}
}

float MathsUtils::toDegree(float fRadian) const
{
	return (fRadian * 180) / m_fPiLowPres;
}

float MathsUtils::toRadian(float fDegree) const
{
	return (fDegree * m_fPiLowPres) / 180.f;
}

float MathsUtils::getPi() const
{
	return m_fPiLowPres;
}

double MathsUtils::getPiHighPres() const
{
	return m_fPiHighPres;
}

float MathsUtils::getMinimum(float a, float b)
{
	if (a < b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

float MathsUtils::getMinimum(VectorSim<float> values)
{
	float returnValue = values.at(0);	//Start the return value as the first value in the vector

	int i = 0;
	int vecSize = values.size();
	for (; i < vecSize; ++i)		//iterate through the vector
	{
		if (values.at(i) < returnValue)		//If the current checking valuse is less than the current minimum
		{
			returnValue = values.at(i);		//Set the return value to this new minimum
		}
	}

	return returnValue;		//Return the found minimum
}

float MathsUtils::getMaximum(float a, float b)
{
	if (a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

float MathsUtils::getMaximum(VectorSim<float> values)
{
	float returnValue = values.at(0);	//Start the return value as the first value in the vector

	int i = 0;
	int vecSize = values.size();
	for (; i < vecSize; ++i)		//iterate through the vector
	{
		if (values.at(i) > returnValue)		//If the current checking valuse is greater than the current maximum
		{
			returnValue = values.at(i);		//Set the return value to this new maximum
		}
	}

	return returnValue;		//Return the found maximum
}

glm::mat4 MathsUtils::getRotationMatrixAroundX(float angleRads)
{
	return glm::mat4x4 (1, 0, 0, 0,
						0, std::cos(angleRads), -std::sin(angleRads), 0,
						0, std::sin(angleRads), std::cos(angleRads), 0,
						0, 0, 0, 1);
}

glm::mat4 MathsUtils::getRotationMatrixAroundY(float angleRads)
{
	return glm::mat4x4 (std::cos(angleRads), 0, -std::sin(angleRads), 0,
						0, 1, 0, 0,
						std::sin(angleRads), 0, std::cos(angleRads), 0,
						0, 0, 0, 1);
}

glm::mat4 MathsUtils::getRotationMatrixAroundZ(float angleRads)
{
	return glm::mat4x4 (std::cos(angleRads), -std::sin(angleRads), 0, 0,
						std::sin(angleRads), std::cos(angleRads), 0, 0,
						0, 0, 1, 0,
						0, 0, 0, 1);
}

glm::vec3 MathsUtils::asUnit(glm::vec3 vec)
{
	float l = vec.length();
	return glm::vec3(vec.x / l, vec.y / l, vec.z / l);
}

float MathsUtils::dotProduct(glm::vec3 a, glm::vec3 b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

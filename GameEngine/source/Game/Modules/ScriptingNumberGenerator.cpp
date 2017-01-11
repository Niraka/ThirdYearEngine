#include "Game/Modules/ScriptingNumberGenerator.h"

ScriptingNumberGenerator::ScriptingNumberGenerator()
{
	m_generator.seed(0);
	m_distributor = std::uniform_real_distribution<float>(0, 1);
}

ScriptingNumberGenerator::~ScriptingNumberGenerator()
{
}

float ScriptingNumberGenerator::getValue(float fLower, float fUpper)
{
	if (fUpper <= fLower)
	{
		return -1;
	}

	m_distributor = std::uniform_real_distribution<float>(fLower, fUpper);
	float f = m_distributor(m_generator);
	return f;
}

int ScriptingNumberGenerator::getValue(int iLower, int iUpper)
{
	if (iUpper <= iLower)
	{
		return -1;
	}

	m_distributor = std::uniform_real_distribution<float>((float)iLower, (float)iUpper);
	int i = (int)m_distributor(m_generator);
	return i;
}
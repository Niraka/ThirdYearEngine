#include "Game/Modules/FunctionGetRandomFloat.h"

FunctionGetRandomFloat::FunctionGetRandomFloat(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::FLOAT)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::FLOAT, ScriptVar::SupportedTypes::FLOAT));

	m_lower = params.at(0);
	m_upper = params.at(1);
}

FunctionGetRandomFloat::~FunctionGetRandomFloat()
{
}

ScriptVar& FunctionGetRandomFloat::execute(ScriptInfoPack& pack)
{
	if (pack.numberGenerator)
	{
		m_returnVal.setFloat(pack.numberGenerator->getValue(
			m_lower.getValue(pack).getFloat(),
			m_upper.getValue(pack).getFloat()));
	}
	return m_returnVal;
}
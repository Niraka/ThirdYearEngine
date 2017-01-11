#include "Game/Modules/FunctionGetRandomInt.h"

FunctionGetRandomInt::FunctionGetRandomInt(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::INT)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::INT, ScriptVar::SupportedTypes::INT));

	m_lower = params.at(0);
	m_upper = params.at(1);
}

FunctionGetRandomInt::~FunctionGetRandomInt()
{
}

ScriptVar& FunctionGetRandomInt::execute(ScriptInfoPack& pack)
{
	if (pack.numberGenerator)
	{
		m_returnVal.setInt(pack.numberGenerator->getValue(
			m_lower.getValue(pack).getInt(),
			m_upper.getValue(pack).getInt()));
	}
	return m_returnVal;
}
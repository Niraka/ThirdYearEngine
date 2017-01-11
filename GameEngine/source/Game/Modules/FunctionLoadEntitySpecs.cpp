#include "Game/Modules/FunctionLoadEntitySpecs.h"

FunctionLoadEntitySpecs::FunctionLoadEntitySpecs(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::STRING));

	m_fileName = params.at(0);
}

FunctionLoadEntitySpecs::~FunctionLoadEntitySpecs()
{
}

ScriptVar& FunctionLoadEntitySpecs::execute(ScriptInfoPack& pack)
{
	if (pack.entityModule)
	{
		pack.entityModule->loadEntitySpecifications(m_fileName.getValue(pack).getString());
	}
	return m_returnVal;
}
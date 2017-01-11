#include "Game/Modules/FunctionLoadModels.h"

FunctionLoadModels::FunctionLoadModels(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::STRING));

	m_fileName = params.at(0);
}

FunctionLoadModels::~FunctionLoadModels()
{
}

ScriptVar& FunctionLoadModels::execute(ScriptInfoPack& pack)
{
	if (pack.actingModule)
	{
		pack.actingModule->loadModelsFromFile(m_fileName.getValue(pack).getString());
	}
	return m_returnVal;
}
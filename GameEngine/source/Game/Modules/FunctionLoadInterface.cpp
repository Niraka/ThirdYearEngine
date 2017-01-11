#include "Game/Modules/FunctionLoadInterface.h"

FunctionLoadInterface::FunctionLoadInterface(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::STRING));

	m_fileName = params.at(0);
}

FunctionLoadInterface::~FunctionLoadInterface()
{
}

ScriptVar& FunctionLoadInterface::execute(ScriptInfoPack& pack)
{
	if (pack.guiModule)
	{
		UILoader loader(pack.guiModule, pack.resourceModule);
		loader.load(m_fileName.getValue(pack).getString() + ".txt");
	}
	return m_returnVal;
}
#include "Game\Modules\FunctionDisplayInterface.h"

FunctionDisplayInterface::FunctionDisplayInterface(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::STRING));
	m_interfaceName = params.at(0);
}

FunctionDisplayInterface::~FunctionDisplayInterface()
{

}

ScriptVar& FunctionDisplayInterface::execute(ScriptInfoPack& pack)
{
	if (pack.guiModule)
	{
		pack.guiModule->setActiveUI(m_interfaceName.getValue(pack).getString());
	}
}

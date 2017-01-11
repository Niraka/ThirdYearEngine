#include "Game/Modules/FunctionDeleteScene.h"

FunctionDeleteScene::FunctionDeleteScene(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::STRING));
	m_sceneName = params.at(0);
}

FunctionDeleteScene::~FunctionDeleteScene()
{

}

ScriptVar& FunctionDeleteScene::execute(ScriptInfoPack& pack)
{
	if (pack.windowModule)
	{
		pack.windowModule->deleteScene(m_sceneName.getValue(pack).getString());
	}
	return m_returnVal;
}
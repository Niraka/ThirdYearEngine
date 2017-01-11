#include "Game/Modules/FunctionCreateScene.h"

FunctionCreateScene::FunctionCreateScene(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::STRING));
	m_sceneName = params.at(0);
}

FunctionCreateScene::~FunctionCreateScene()
{

}

ScriptVar& FunctionCreateScene::execute(ScriptInfoPack& pack)
{
	if (pack.windowModule)
	{
		pack.windowModule->createScene(m_sceneName.getValue(pack).getString());
	}
	return m_returnVal;
}
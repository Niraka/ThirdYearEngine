#include "Game/Modules/FunctionActivateScene.h"

FunctionActivateScene::FunctionActivateScene(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::BOOL)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::STRING));
	m_sceneName = params.at(0);
}

FunctionActivateScene::~FunctionActivateScene()
{

}

ScriptVar& FunctionActivateScene::execute(ScriptInfoPack& pack)
{
	if (pack.windowModule)
	{
		m_returnVal.setBool(pack.windowModule->activateScene(m_sceneName.getValue(pack).getString()));
	}
	return m_returnVal;
}
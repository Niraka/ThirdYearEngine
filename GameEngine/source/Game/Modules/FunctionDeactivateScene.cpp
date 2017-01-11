#include "Game/Modules/FunctionDeactivateScene.h"

FunctionDeactivateScene::FunctionDeactivateScene(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::BOOL)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::STRING));
	m_sceneName = params.at(0);
}

FunctionDeactivateScene::~FunctionDeactivateScene()
{

}

ScriptVar& FunctionDeactivateScene::execute(ScriptInfoPack& pack)
{
	if (pack.windowModule)
	{
		m_returnVal.setBool(pack.windowModule->deactivateScene(m_sceneName.getValue(pack).getString()));
	}
	return m_returnVal;
}
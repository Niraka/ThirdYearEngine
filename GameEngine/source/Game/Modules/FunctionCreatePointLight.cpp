#include "Game/Modules/FunctionCreatePointLight.h"

FunctionCreatePointLight::FunctionCreatePointLight(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::INT)
{
	addParamDefinition(ParamDefinition());
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::STRING));

	if (params.size() == 1)
	{
		m_sceneName = params.at(0);
	}
	else
	{
		m_sceneName = ScriptParam(ScriptVar(std::string("")), false);
	}
	m_returnVal.setInt(0);
}

FunctionCreatePointLight::~FunctionCreatePointLight()
{
}

ScriptVar& FunctionCreatePointLight::execute(ScriptInfoPack& pack)
{
	if (pack.windowModule)
	{
		std::shared_ptr<Scene> scene = pack.windowModule->getScene(m_sceneName.getValue(pack).getString());
		m_returnVal.setInt(scene->createLight(Scene::LightTypes::POINT));
	}
	return m_returnVal;
}
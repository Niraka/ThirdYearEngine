#include "Game/Modules/FunctionEnablePointLight.h"

FunctionEnablePointLight::FunctionEnablePointLight(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::INT));
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::INT, ScriptVar::SupportedTypes::STRING));

	m_lightId = params.at(0);
	if (params.size() == 2)
	{
		m_sceneName = params.at(1);
	}
	else
	{
		m_sceneName = ScriptParam(ScriptVar(std::string("")), false);
	}

	m_returnVal.setBool(false);
}

FunctionEnablePointLight::~FunctionEnablePointLight()
{
}

ScriptVar& FunctionEnablePointLight::execute(ScriptInfoPack& pack)
{
	if (pack.windowModule)
	{
		std::shared_ptr<Scene> scene = pack.windowModule->getScene(m_sceneName.getValue(pack).getString());
		std::shared_ptr<Light> light = scene->getPointLight(m_lightId.getValue(pack).getInt());
		if (light)
		{
			light->setEnabled(true);
		}
	}
	return m_returnVal;
}
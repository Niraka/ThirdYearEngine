#include "Game/Modules/FunctionDisableSpotLight.h"

FunctionDisableSpotLight::FunctionDisableSpotLight(std::vector<ScriptParam>& params) :
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

FunctionDisableSpotLight::~FunctionDisableSpotLight()
{
}

ScriptVar& FunctionDisableSpotLight::execute(ScriptInfoPack& pack)
{
	if (pack.windowModule)
	{
		std::shared_ptr<Scene> scene = pack.windowModule->getScene(m_sceneName.getValue(pack).getString());
		if (scene)
		{
			std::shared_ptr<Light> light = scene->getSpotLight(m_lightId.getValue(pack).getInt());
			if (light)
			{
				light->setEnabled(false);
			}
		}
	}
	return m_returnVal;
}
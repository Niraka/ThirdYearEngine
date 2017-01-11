#include "Game/Modules/FunctionSetSpotLightCone.h"

FunctionSetSpotLightCone::FunctionSetSpotLightCone(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	std::vector<ScriptVar::SupportedTypes> types;
	types.push_back(ScriptVar::SupportedTypes::INT);
	types.push_back(ScriptVar::SupportedTypes::FLOAT);
	addParamDefinition(ParamDefinition(types));

	types.push_back(ScriptVar::SupportedTypes::STRING);
	addParamDefinition(ParamDefinition(types));

	m_lightId = params.at(0);
	m_coneAngle = params.at(1);

	if (params.size() == 3)
	{
		m_sceneName = params.at(2);
	}
	else
	{
		m_sceneName = ScriptParam(ScriptVar(std::string("")), false);
	}
}

FunctionSetSpotLightCone::~FunctionSetSpotLightCone()
{
}

ScriptVar& FunctionSetSpotLightCone::execute(ScriptInfoPack& pack)
{
	if (pack.windowModule)
	{
		std::shared_ptr<Scene> scene = pack.windowModule->getScene(m_sceneName.getValue(pack).getString());
		if (scene)
		{
			std::shared_ptr<SpotLight> light = scene->getSpotLight(m_lightId.getValue(pack).getInt());
			if (light)
			{
				light->setConeAngle(m_coneAngle.getValue(pack).getFloat());
			}
		}
	}

	return m_returnVal;
}
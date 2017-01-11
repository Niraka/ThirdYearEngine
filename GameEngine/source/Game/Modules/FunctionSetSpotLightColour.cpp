#include "Game/Modules/FunctionSetSpotLightColour.h"

FunctionSetSpotLightColour::FunctionSetSpotLightColour(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	std::vector<ScriptVar::SupportedTypes> types;
	types.push_back(ScriptVar::SupportedTypes::INT);
	types.push_back(ScriptVar::SupportedTypes::FLOAT);
	types.push_back(ScriptVar::SupportedTypes::FLOAT);
	types.push_back(ScriptVar::SupportedTypes::FLOAT);
	addParamDefinition(ParamDefinition(types));
	
	types.push_back(ScriptVar::SupportedTypes::STRING);
	addParamDefinition(ParamDefinition(types));

	m_lightId = params.at(0);
	m_r = params.at(1);
	m_g = params.at(2);
	m_b = params.at(3);

	if (params.size() == 5)
	{
		m_sceneName = params.at(4);
	}
	else
	{
		m_sceneName = ScriptParam(ScriptVar(std::string("")), false);
	}
}

FunctionSetSpotLightColour::~FunctionSetSpotLightColour()
{
}

ScriptVar& FunctionSetSpotLightColour::execute(ScriptInfoPack& pack)
{
	std::shared_ptr<Scene> scene = pack.windowModule->getScene(m_sceneName.getValue(pack).getString());
	if (scene)
	{
		std::shared_ptr<Light> light = scene->getSpotLight(m_lightId.getValue(pack).getInt());
		if (light)
		{
			light->setColour(glm::vec3(m_r.getValue(pack).getFloat(), m_g.getValue(pack).getFloat(),
				m_b.getValue(pack).getFloat()));
		}
	}
	return m_returnVal;
}
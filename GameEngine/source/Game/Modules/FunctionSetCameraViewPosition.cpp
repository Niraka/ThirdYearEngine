#include "Game/Modules/FunctionSetCameraViewPosition.h"

FunctionSetCameraViewPosition::FunctionSetCameraViewPosition(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	std::vector<ScriptVar::SupportedTypes> types;
	types.push_back(ScriptVar::SupportedTypes::INT);
	types.push_back(ScriptVar::SupportedTypes::FLOAT);
	types.push_back(ScriptVar::SupportedTypes::FLOAT);
	addParamDefinition(ParamDefinition(types));

	types.push_back(ScriptVar::SupportedTypes::STRING);
	addParamDefinition(ParamDefinition(types));

	m_cameraId = params.at(0);
	m_x = params.at(1);
	m_y = params.at(2);

	if (params.size() == 4)
	{
		m_sceneName = params.at(3);
	}
	else
	{
		m_sceneName = ScriptParam(ScriptVar(std::string("")), false);
	}
}

FunctionSetCameraViewPosition::~FunctionSetCameraViewPosition()
{
}

ScriptVar& FunctionSetCameraViewPosition::execute(ScriptInfoPack& pack)
{
	std::shared_ptr<Scene> scene = pack.windowModule->getScene(m_sceneName.getValue(pack).getString());
	if (scene)
	{
		std::shared_ptr<Camera> camera = scene->getCamera(m_cameraId.getValue(pack).getInt());
		if (camera)
		{
			camera->setViewPosition(glm::vec2(m_x.getValue(pack).getFloat(), m_y.getValue(pack).getFloat()));
		}
	}
	return m_returnVal;
}
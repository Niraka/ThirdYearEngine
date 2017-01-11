#include "Game/Modules/FunctionSetCameraViewSize.h"

FunctionSetCameraViewSize::FunctionSetCameraViewSize(std::vector<ScriptParam>& params) :
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
	m_width = params.at(1);
	m_height = params.at(2);

	if (params.size() == 4)
	{
		m_sceneName = params.at(3);
	}
	else
	{
		m_sceneName = ScriptParam(ScriptVar(std::string("")), false);
	}
}

FunctionSetCameraViewSize::~FunctionSetCameraViewSize()
{
}

ScriptVar& FunctionSetCameraViewSize::execute(ScriptInfoPack& pack)
{
	std::shared_ptr<Scene> scene = pack.windowModule->getScene(m_sceneName.getValue(pack).getString());
	if (scene)
	{
		std::shared_ptr<Camera> camera = scene->getCamera(m_cameraId.getValue(pack).getInt());
		if (camera)
		{
			camera->setViewSize(glm::vec2(m_width.getValue(pack).getFloat(), m_height.getValue(pack).getFloat()));
		}
	}
	return m_returnVal;
}
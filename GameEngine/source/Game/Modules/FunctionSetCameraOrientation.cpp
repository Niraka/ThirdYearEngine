#include "Game/Modules/FunctionSetCameraOrientation.h"

FunctionSetCameraOrientation::FunctionSetCameraOrientation(std::vector<ScriptParam>& params) :
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

	m_cameraId = params.at(0);
	m_x = params.at(1);
	m_y = params.at(1);
	m_z = params.at(1);

	if (params.size() == 5)
	{
		m_sceneName = params.at(4);
	}
	else
	{
		m_sceneName = ScriptParam(ScriptVar(std::string("")), false);
	}
}

FunctionSetCameraOrientation::~FunctionSetCameraOrientation()
{
}

ScriptVar& FunctionSetCameraOrientation::execute(ScriptInfoPack& pack)
{
	if (pack.windowModule)
	{
		std::shared_ptr<Scene> scene = pack.windowModule->getScene(m_sceneName.getValue(pack).getString());
		if (scene)
		{
			std::shared_ptr<Camera> camera = scene->getCamera(m_cameraId.getValue(pack).getInt());
			if (camera)
			{
				camera->setOrientation(
					m_x.getValue(pack).getFloat(),
					m_y.getValue(pack).getFloat(),
					m_z.getValue(pack).getFloat());
			}
		}
	}

	return m_returnVal;
}
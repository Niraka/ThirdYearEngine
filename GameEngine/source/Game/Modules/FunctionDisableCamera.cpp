#include "Game/Modules/FunctionDisableCamera.h"

FunctionDisableCamera::FunctionDisableCamera(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::INT));
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::INT, ScriptVar::SupportedTypes::STRING));

	m_cameraId = params.at(0);
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

FunctionDisableCamera::~FunctionDisableCamera()
{
}

ScriptVar& FunctionDisableCamera::execute(ScriptInfoPack& pack)
{
	if (pack.windowModule)
	{
		std::shared_ptr<Scene> scene = pack.windowModule->getScene(m_sceneName.getValue(pack).getString());
		std::shared_ptr<Camera> camera = scene->getCamera(m_cameraId.getValue(pack).getInt());
		if (camera)
		{
			camera->setEnabled(false);
		}
	}
	return m_returnVal;
}
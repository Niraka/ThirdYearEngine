#include "Game/Modules/FunctionBindCameraToEntity.h"

FunctionBindCameraToEntity::FunctionBindCameraToEntity(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	std::vector<ScriptVar::SupportedTypes> types;
	types.push_back(ScriptVar::SupportedTypes::INT);
	types.push_back(ScriptVar::SupportedTypes::INT);
	addParamDefinition(ParamDefinition(types));

	types.push_back(ScriptVar::SupportedTypes::STRING);
	addParamDefinition(ParamDefinition(types));
	
	m_cameraId = params.at(0);
	m_entityId = params.at(1);	

	if (params.size() == 3)
	{
		m_sceneName = params.at(2);
	}
	else
	{
		m_sceneName = ScriptParam(ScriptVar(std::string("")), false);
	}
}

FunctionBindCameraToEntity::~FunctionBindCameraToEntity()
{
}

ScriptVar& FunctionBindCameraToEntity::execute(ScriptInfoPack& pack)
{
	if (pack.entityModule && pack.windowModule)
	{
		std::shared_ptr<Scene> scene = pack.windowModule->getScene(m_sceneName.getValue(pack).getString());
		if (scene)
		{
			std::shared_ptr<Camera> camera = scene->getCamera(m_cameraId.getValue(pack).getInt());
			if (camera)
			{
				std::shared_ptr<Entity> entity = pack.entityModule->getEntity(m_entityId.getValue(pack).getInt());
				if (entity)
				{
					entity->attachCamera(camera);
				}
			}
		}
	}
	return m_returnVal;
}
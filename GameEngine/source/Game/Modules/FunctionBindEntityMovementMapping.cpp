#include "Game/Modules/FunctionBindEntityMovementMapping.h"

FunctionBindEntityMovementMapping::FunctionBindEntityMovementMapping(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	std::vector<ScriptVar::SupportedTypes> types;
	types.push_back(ScriptVar::SupportedTypes::INT);
	types.push_back(ScriptVar::SupportedTypes::INT);
	addParamDefinition(ParamDefinition(types));

	types.push_back(ScriptVar::SupportedTypes::STRING);
	addParamDefinition(ParamDefinition(types));

	m_controlSetId = params.at(0);
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

FunctionBindEntityMovementMapping::~FunctionBindEntityMovementMapping()
{
}

ScriptVar& FunctionBindEntityMovementMapping::execute(ScriptInfoPack& pack)
{
	if (pack.windowModule && pack.entityModule)
	{
		std::shared_ptr<Scene> scene = pack.windowModule->getScene(m_sceneName.getValue(pack).getString());
		if (scene)
		{
			std::shared_ptr<Entity> entity = pack.entityModule->getEntity(m_entityId.getValue(pack).getInt());
			std::shared_ptr<ControlSet> controlSet = scene->getControlSet(m_controlSetId.getValue(pack).getInt());
			if (controlSet && entity)
			{
				controlSet->addMovementMapping(entity.get());
			}
		}
	}

	return m_returnVal;
}
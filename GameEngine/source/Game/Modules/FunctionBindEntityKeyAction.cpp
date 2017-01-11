#include "Game/Modules/FunctionBindEntityKeyAction.h"

FunctionBindEntityKeyAction::FunctionBindEntityKeyAction(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	std::vector<ScriptVar::SupportedTypes> types;
	types.push_back(ScriptVar::SupportedTypes::INT);
	types.push_back(ScriptVar::SupportedTypes::INT);
	types.push_back(ScriptVar::SupportedTypes::STRING);
	types.push_back(ScriptVar::SupportedTypes::INT);
	types.push_back(ScriptVar::SupportedTypes::INT);
	addParamDefinition(ParamDefinition(types));

	types.push_back(ScriptVar::SupportedTypes::STRING);
	addParamDefinition(ParamDefinition(types));

	m_controlSetId = params.at(0);
	m_entityId = params.at(1);
	m_actionName = params.at(2);
	m_keyCode = params.at(3);
	m_actionType = params.at(4);

	if (params.size() == 6)
	{
		m_sceneName = params.at(5);
	}
	else
	{
		m_sceneName = ScriptParam(ScriptVar(std::string("")), false);
	}
}

FunctionBindEntityKeyAction::~FunctionBindEntityKeyAction()
{
}

ScriptVar& FunctionBindEntityKeyAction::execute(ScriptInfoPack& pack)
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
				if (entity->bindKeyToAction(m_keyCode.getValue(pack).getInt(),
					0,
					m_actionType.getValue(pack).getInt(),
					m_actionName.getValue(pack).getString()))
				{
					controlSet->addKeyMapping(
						m_keyCode.getValue(pack).getInt(),
						m_actionType.getValue(pack).getInt(),
						0,
						entity.get());
				}
			}
		}
	}

	return m_returnVal;
}
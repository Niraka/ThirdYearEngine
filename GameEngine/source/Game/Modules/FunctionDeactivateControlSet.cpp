#include "Game/Modules/FunctionDeactivateControlSet.h"

FunctionDeactivateControlSet::FunctionDeactivateControlSet(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::INT));
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::INT, ScriptVar::SupportedTypes::STRING));

	m_controlSetId = params.at(0);

	if (params.size() == 2)
	{
		m_sceneName = params.at(1);
	}
	else
	{
		m_sceneName = ScriptParam(ScriptVar(std::string("")), false);
	}
}

FunctionDeactivateControlSet::~FunctionDeactivateControlSet()
{
}

ScriptVar& FunctionDeactivateControlSet::execute(ScriptInfoPack& pack)
{
	if (pack.windowModule && pack.entityModule)
	{
		std::shared_ptr<Scene> scene = pack.windowModule->getScene(m_sceneName.getValue(pack).getString());
		if (scene)
		{
			scene->deactivateControlSet(m_controlSetId.getValue(pack).getInt());
		}
	}

	return m_returnVal;
}
#include "Game/Modules/FunctionDeleteControlSet.h"

FunctionDeleteControlSet::FunctionDeleteControlSet(std::vector<ScriptParam>& params) :
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

	m_returnVal.setInt(0);
}

FunctionDeleteControlSet::~FunctionDeleteControlSet()
{
}

ScriptVar& FunctionDeleteControlSet::execute(ScriptInfoPack& pack)
{
	if (pack.windowModule)
	{
		std::shared_ptr<Scene> scene = pack.windowModule->getScene(m_sceneName.getValue(pack).getString());
		if (scene)
		{
			scene->deleteControlSet(m_controlSetId.getValue(pack).getInt());
		}
	}

	return m_returnVal;
}
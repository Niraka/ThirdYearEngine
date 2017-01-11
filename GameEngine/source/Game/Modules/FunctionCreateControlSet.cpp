#include "Game/Modules/FunctionCreateControlSet.h"

FunctionCreateControlSet::FunctionCreateControlSet(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::INT)
{
	addParamDefinition(ParamDefinition());
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::STRING));

	if (params.size() == 1)
	{
		m_sceneName = params.at(0);
	}
	else
	{
		m_sceneName = ScriptParam(ScriptVar(std::string("")), false);
	}

	m_returnVal.setInt(0);
}

FunctionCreateControlSet::~FunctionCreateControlSet()
{
}

ScriptVar& FunctionCreateControlSet::execute(ScriptInfoPack& pack)
{
	if (pack.windowModule)
	{
		std::shared_ptr<Scene> scene = pack.windowModule->getScene(m_sceneName.getValue(pack).getString());
		if (scene)
		{
			m_returnVal.setInt(scene->createControlSet());
		}
	}

	return m_returnVal;
}
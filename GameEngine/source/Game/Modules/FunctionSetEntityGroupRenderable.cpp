#include "Game/Modules/FunctionSetEntityGroupRenderable.h"

FunctionSetEntityGroupRenderable::FunctionSetEntityGroupRenderable(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	addParamDefinition(ParamDefinition(ScriptVar::SupportedTypes::STRING, ScriptVar::SupportedTypes::BOOL));

	m_groupName = params.at(0);
	m_renderable = params.at(1);
}

FunctionSetEntityGroupRenderable::~FunctionSetEntityGroupRenderable()
{
}

ScriptVar& FunctionSetEntityGroupRenderable::execute(ScriptInfoPack& pack)
{
	if (pack.entityModule)
	{
		pack.entityModule->setEntityGroupRenderable(
			m_groupName.getValue(pack).getString(),
			m_renderable.getValue(pack).getBool());
	}
	return m_returnVal;
}
#include "Game/Modules/FunctionSetEntityOrientation.h"

FunctionSetEntityOrientation::FunctionSetEntityOrientation(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	std::vector<ScriptVar::SupportedTypes> types;
	types.push_back(ScriptVar::SupportedTypes::INT);
	types.push_back(ScriptVar::SupportedTypes::FLOAT);
	types.push_back(ScriptVar::SupportedTypes::FLOAT);
	types.push_back(ScriptVar::SupportedTypes::FLOAT);
	addParamDefinition(ParamDefinition(types));

	m_entityId = params.at(0);
	m_x = params.at(1);
	m_y = params.at(2);
	m_z = params.at(3);
}

FunctionSetEntityOrientation::~FunctionSetEntityOrientation()
{
}

ScriptVar& FunctionSetEntityOrientation::execute(ScriptInfoPack& pack)
{
	if (pack.entityModule)
	{
		std::shared_ptr<Entity> entity = pack.entityModule->getEntity(
			(unsigned int)m_entityId.getValue(pack).getInt());
		if (entity)
		{
			entity->setOrientation(glm::vec3(
				m_x.getValue(pack).getFloat(),
				m_y.getValue(pack).getFloat(),
				m_z.getValue(pack).getFloat()));
		}
	}
	return m_returnVal;
}
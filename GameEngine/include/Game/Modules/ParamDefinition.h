/**
@author Nathan */

#ifndef PARAM_DEFINITION_H
#define PARAM_DEFINITION_H

#include "Game/Modules/ScriptVar.h"
#include <vector>
#include <string>

class ParamDefinition
{
	private:
		std::vector<ScriptVar::SupportedTypes> m_params;

	protected:

	public:
		ParamDefinition();
		ParamDefinition(ScriptVar::SupportedTypes type1);
		ParamDefinition(ScriptVar::SupportedTypes type1, ScriptVar::SupportedTypes type2);
		ParamDefinition(std::vector<ScriptVar::SupportedTypes> types);

		bool operator==(const ParamDefinition& other);

		std::string toString() const;
};

#endif
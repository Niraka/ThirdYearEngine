#ifndef FUNCTION_H
#define FUNCTION_H

#include "Game/Modules/ScriptInfoPack.h"
#include "Game/Modules/ParamDefinition.h"
#include "Game/Modules/ScriptVar.h"

class Function
{
	private:
		ScriptVar::SupportedTypes m_returnType;
		std::vector<ParamDefinition> m_paramDefinitions;

	protected:
		ScriptVar m_returnVal;

		Function(ScriptVar::SupportedTypes returnType);


		bool addParamDefinition(ParamDefinition& definition);

	public:
		bool hasParamDefinition(const ParamDefinition& definition);
		const std::vector<ParamDefinition>& getDefinitions() const;
		const ScriptVar::SupportedTypes& getReturnType() const;
		virtual ScriptVar& execute(ScriptInfoPack& pack) = 0;
};

#endif
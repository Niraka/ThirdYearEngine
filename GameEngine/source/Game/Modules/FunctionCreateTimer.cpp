#include "Game/Modules/FunctionCreateTimer.h"

FunctionCreateTimer::FunctionCreateTimer(std::vector<ScriptParam>& params) :
Function(ScriptVar::SupportedTypes::VOID)
{
	std::vector<ScriptVar::SupportedTypes> types;
	types.push_back(ScriptVar::SupportedTypes::STRING);
	types.push_back(ScriptVar::SupportedTypes::FLOAT);
	addParamDefinition(ParamDefinition(types));

	types.push_back(ScriptVar::SupportedTypes::STRING);
	addParamDefinition(ParamDefinition(types));

	m_timerName = params.at(0);
	m_duration = params.at(1);
	
	if (params.size() == 3)
	{
		m_scriptToRun = params.at(2);
		m_bScriptRunEnabled = true;
	}
	else
	{
		m_bScriptRunEnabled = false;
	}
}

FunctionCreateTimer::~FunctionCreateTimer()
{
}

ScriptVar& FunctionCreateTimer::execute(ScriptInfoPack& pack)
{
	if (m_bScriptRunEnabled)
	{
		if (pack.timingModule && pack.timerRegistrar)
		{
			std::shared_ptr<Timer> timer = std::make_shared<Timer>(
				m_timerName.getValue(pack).getString(),
				m_duration.getValue(pack).getFloat());
			pack.timingModule->addTimer(timer);
			pack.timerRegistrar->addTimer(
				m_timerName.getValue(pack).getString(), 
				m_scriptToRun.getValue(pack).getString());
		}
	}
	else
	{
		if (pack.timingModule)
		{
			std::shared_ptr<Timer> timer = std::make_shared<Timer>(
				m_timerName.getValue(pack).getString(),
				m_duration.getValue(pack).getFloat());
			pack.timingModule->addTimer(timer);
		}
	}

	return m_returnVal;
}
#include "Game/Modules/FunctionRegister.h"

FunctionRegister::FunctionRegister()
{
	std::vector<ScriptParam> fakeParams = std::vector<ScriptParam>(7, ScriptParam());

	// Add functions
	m_functions.emplace("assign", new FunctionAssign(fakeParams));
	m_functions.emplace("log", new FunctionLog(fakeParams));
	m_functions.emplace("getRandomInt", new FunctionGetRandomInt(fakeParams));
	m_functions.emplace("getRandomFloat", new FunctionGetRandomFloat(fakeParams));

	m_functions.emplace("createScene", new FunctionCreateScene(fakeParams));
	m_functions.emplace("deleteScene", new FunctionDeleteScene(fakeParams));
	m_functions.emplace("activateScene", new FunctionActivateScene(fakeParams));
	m_functions.emplace("deactivateScene", new FunctionDeactivateScene(fakeParams));

	m_functions.emplace("loadEntitySpecs", new FunctionLoadEntitySpecs(fakeParams));
	m_functions.emplace("loadInterface", new FunctionLoadInterface(fakeParams));
	m_functions.emplace("loadModels", new FunctionLoadModels(fakeParams));
	m_functions.emplace("loadMusic", new FunctionLoadMusic(fakeParams));
	m_functions.emplace("loadSound", new FunctionLoadSound(fakeParams));

	m_functions.emplace("loadScript", new FunctionLoadScript(fakeParams));
	m_functions.emplace("unloadScript", new FunctionUnloadScript(fakeParams));
	m_functions.emplace("executeScript", new FunctionExecuteScript(fakeParams));

	m_functions.emplace("createEntity", new FunctionCreateEntity(fakeParams));
	m_functions.emplace("deleteEntity", new FunctionDeleteEntity(fakeParams));
	m_functions.emplace("setEntityPosition", new FunctionSetEntityPosition(fakeParams));
	m_functions.emplace("setEntityScale", new FunctionSetEntityScale(fakeParams));
	m_functions.emplace("setEntityOrientation", new FunctionSetEntityOrientation(fakeParams));
	
	m_functions.emplace("createAmbientLight", new FunctionCreateAmbientLight(fakeParams));
	m_functions.emplace("createPointLight", new FunctionCreatePointLight(fakeParams));
	m_functions.emplace("createSpotLight", new FunctionCreateSpotLight(fakeParams));
	m_functions.emplace("createCamera", new FunctionCreateCamera(fakeParams));

	m_functions.emplace("deleteAmbientLight", new FunctionDeleteAmbientLight(fakeParams));
	m_functions.emplace("deletePointLight", new FunctionDeletePointLight(fakeParams));
	m_functions.emplace("deleteSpotLight", new FunctionDeleteSpotLight(fakeParams));
	m_functions.emplace("deleteCamera", new FunctionDeleteCamera(fakeParams));

	m_functions.emplace("enableAmbientLight", new FunctionEnableAmbientLight(fakeParams));
	m_functions.emplace("enablePointLight", new FunctionEnablePointLight(fakeParams));
	m_functions.emplace("enableSpotLight", new FunctionEnableSpotLight(fakeParams));
	m_functions.emplace("enableCamera", new FunctionEnableCamera(fakeParams));

	m_functions.emplace("disableAmbientLight", new FunctionDisableAmbientLight(fakeParams));
	m_functions.emplace("disablePointLight", new FunctionDisablePointLight(fakeParams));
	m_functions.emplace("disableSpotLight", new FunctionDisableSpotLight(fakeParams));
	m_functions.emplace("disableCamera", new FunctionDisableCamera(fakeParams));

	m_functions.emplace("setAmbientLightColour", new FunctionSetAmbientLightColour(fakeParams));
	m_functions.emplace("setPointLightColour", new FunctionSetPointLightColour(fakeParams));
	m_functions.emplace("setSpotLightColour", new FunctionSetSpotLightColour(fakeParams));
	m_functions.emplace("setPointLightPosition", new FunctionSetPointLightPosition(fakeParams));
	m_functions.emplace("setSpotLightPosition", new FunctionSetSpotLightPosition(fakeParams));
	m_functions.emplace("setSpotLightTarget", new FunctionSetSpotLightTarget(fakeParams));
	m_functions.emplace("setSpotLightCone", new FunctionSetSpotLightCone(fakeParams));
	m_functions.emplace("setCameraPosition", new FunctionSetCameraPosition(fakeParams));
	m_functions.emplace("setCameraViewPosition", new FunctionSetCameraViewPosition(fakeParams));
	m_functions.emplace("setCameraViewSize", new FunctionSetCameraViewSize(fakeParams));

	m_functions.emplace("playMusic", new FunctionPlayMusic(fakeParams));
	m_functions.emplace("setMusicVolume", new FunctionSetMusicVolume(fakeParams));
	m_functions.emplace("setCameraOrientation", new FunctionSetCameraOrientation(fakeParams));
	m_functions.emplace("createTimer", new FunctionCreateTimer(fakeParams));
	m_functions.emplace("setEntityVisible", new FunctionSetEntityVisible(fakeParams));

	m_functions.emplace("greaterThan", new FunctionGreaterThan(fakeParams));
	m_functions.emplace("lessThan", new FunctionLessThan(fakeParams));
	m_functions.emplace("equal", new FunctionEqual(fakeParams));
	m_functions.emplace("if", new FunctionIf(fakeParams));
	m_functions.emplace("add", new FunctionAdd(fakeParams));

	m_functions.emplace("createSound", new FunctionCreateSound(fakeParams));
	m_functions.emplace("createSoundChannel", new FunctionCreateSoundChannel(fakeParams));
	m_functions.emplace("deleteSound", new FunctionDeleteSound(fakeParams));
	m_functions.emplace("setSoundAttenuation", new FunctionSetSoundAttenuation(fakeParams));
	m_functions.emplace("setSoundBuffer", new FunctionSetSoundBuffer(fakeParams));
	m_functions.emplace("setSoundChannelVolume", new FunctionSetSoundChannelVolume(fakeParams));
	m_functions.emplace("setSoundListenerPosition", new FunctionSetSoundListenerPosition(fakeParams));
	m_functions.emplace("setSoundMinDistance", new FunctionSetSoundMinDistance(fakeParams));
	m_functions.emplace("playSound", new FunctionPlaySound(fakeParams));

	m_functions.emplace("createEntityGroup", new FunctionCreateEntityGroup(fakeParams));
	m_functions.emplace("setEntityGroupRenderable", new FunctionSetEntityGroupRenderable(fakeParams));

	m_functions.emplace("createControlSet", new FunctionCreateControlSet(fakeParams));
	m_functions.emplace("activateControlSet", new FunctionActivateControlSet(fakeParams));
	m_functions.emplace("deactivateControlSet", new FunctionDeactivateControlSet(fakeParams));
	m_functions.emplace("deleteControlSet", new FunctionDeleteControlSet(fakeParams));
	m_functions.emplace("bindScriptKeyAction", new FunctionBindScriptKeyAction(fakeParams));
	m_functions.emplace("bindEntityKeyAction", new FunctionBindEntityKeyAction(fakeParams));
	m_functions.emplace("bindCameraToEntity", new FunctionBindCameraToEntity(fakeParams));
	m_functions.emplace("bindSpotLightToEntity", new FunctionBindSpotLightToEntity(fakeParams));
	m_functions.emplace("bindEntityMovementMapping", new FunctionBindEntityMovementMapping(fakeParams));
	m_functions.emplace("setCursorMode", new FunctionSetCursorMode(fakeParams));

	// Build definitions
	for (std::pair<const std::string, Function*> function : m_functions)
	{
		const std::vector<ParamDefinition>& funcDefs = function.second->getDefinitions();
		for (const ParamDefinition& funcDef : funcDefs)
		{
			m_functionDefinitions.push_back(function.first + " " + funcDef.toString());
		}
	}
}

FunctionRegister::~FunctionRegister()
{
}

bool FunctionRegister::functionExists(const std::string& sFuncName) const
{
	return m_functions.find(sFuncName) != m_functions.end();
}

const std::vector<std::string>& FunctionRegister::getFunctionDefinitions()
{
	return m_functionDefinitions;
}

Function* FunctionRegister::buildFunction(std::string sFunctionName, std::vector<ScriptParam>& params)
{
	// Build a definition for the given params
	std::vector<ScriptVar::SupportedTypes> paramTypes;
	for (ScriptParam& param : params)
	{
		paramTypes.push_back(ScriptVar::SupportedTypes(param.getReturnType()));
	}
	ParamDefinition paramDefinition(paramTypes);

	// Look for the correct function. Both the name and parameters definitions must match
	std::map<std::string, Function*>::iterator funcIter = m_functions.find(sFunctionName);
	if (funcIter != m_functions.end())
	{		
		if (!funcIter->second->hasParamDefinition(paramDefinition))
		{
			return nullptr;
		}
	}
	else
	{
		return nullptr;
	}

	// Build and return the function
	Function* func = nullptr;

	if (sFunctionName == "assign"){func = new FunctionAssign(params);}
	else if (sFunctionName == "log"){func = new FunctionLog(params);}
	else if (sFunctionName == "getRandomInt"){func = new FunctionGetRandomInt(params);}
	else if (sFunctionName == "getRandomFloat"){func = new FunctionGetRandomFloat(params);}
	else if (sFunctionName == "createScene"){func = new FunctionCreateScene(params);}
	else if (sFunctionName == "deleteScene"){func = new FunctionDeleteScene(params);}
	else if (sFunctionName == "activateScene"){func = new FunctionActivateScene(params);}
	else if (sFunctionName == "deactivateScene"){func = new FunctionDeactivateScene(params);}
	else if (sFunctionName == "loadEntitySpecs"){func = new FunctionLoadEntitySpecs(params);}
	else if (sFunctionName == "loadInterface"){func = new FunctionLoadInterface(params);}
	else if (sFunctionName == "loadModels"){func = new FunctionLoadModels(params);}
	else if (sFunctionName == "loadMusic"){	func = new FunctionLoadMusic(params);}
	else if (sFunctionName == "loadSound"){	func = new FunctionLoadSound(params);}
	else if (sFunctionName == "loadScript"){func = new FunctionLoadScript(params);}
	else if (sFunctionName == "unloadScript"){func = new FunctionUnloadScript(params);}
	else if (sFunctionName == "executeScript"){func = new FunctionExecuteScript(params);}
	else if (sFunctionName == "createEntity"){func = new FunctionCreateEntity(params);}
	else if (sFunctionName == "deleteEntity"){func = new FunctionDeleteEntity(params);}
	else if (sFunctionName == "setEntityPosition"){func = new FunctionSetEntityPosition(params);}
	else if (sFunctionName == "setEntityScale"){func = new FunctionSetEntityScale(params);}
	else if (sFunctionName == "setEntityOrientation"){ func = new FunctionSetEntityOrientation(params);}
	else if (sFunctionName == "createAmbientLight"){ func = new FunctionCreateAmbientLight(params); }
	else if (sFunctionName == "createPointLight"){ func = new FunctionCreatePointLight(params); }
	else if (sFunctionName == "createSpotLight"){ func = new FunctionCreateSpotLight(params); }
	else if (sFunctionName == "createCamera"){ func = new FunctionCreateCamera(params); }
	else if (sFunctionName == "deleteAmbientLight"){ func = new FunctionDeleteAmbientLight(params); }
	else if (sFunctionName == "deletePointLight"){ func = new FunctionDeletePointLight(params); }
	else if (sFunctionName == "deleteSpotLight"){ func = new FunctionDeleteSpotLight(params); }
	else if (sFunctionName == "deleteCamera"){ func = new FunctionDeleteCamera(params); }
	else if (sFunctionName == "enableAmbientLight"){ func = new FunctionEnableAmbientLight(params); }
	else if (sFunctionName == "enablePointLight"){ func = new FunctionEnablePointLight(params); }
	else if (sFunctionName == "enableSpotLight"){ func = new FunctionEnableSpotLight(params); }
	else if (sFunctionName == "enableCamera"){ func = new FunctionEnableCamera(params); }
	else if (sFunctionName == "disableAmbientLight"){ func = new FunctionDisableAmbientLight(params); }
	else if (sFunctionName == "disablePointLight"){ func = new FunctionDisablePointLight(params); }
	else if (sFunctionName == "disableSpotLight"){ func = new FunctionDisableSpotLight(params); }
	else if (sFunctionName == "disableCamera"){ func = new FunctionDisableCamera(params); }
	else if (sFunctionName == "setAmbientLightColour"){ func = new FunctionSetAmbientLightColour(params); }
	else if (sFunctionName == "setPointLightColour"){ func = new FunctionSetPointLightColour(params); }
	else if (sFunctionName == "setSpotLightColour"){ func = new FunctionSetSpotLightColour(params); }
	else if (sFunctionName == "setPointLightPosition"){ func = new FunctionSetPointLightPosition(params); }
	else if (sFunctionName == "setSpotLightPosition"){ func = new FunctionSetSpotLightPosition(params); }
	else if (sFunctionName == "setSpotLightTarget"){ func = new FunctionSetSpotLightTarget(params); }
	else if (sFunctionName == "setSpotLightCone"){ func = new FunctionSetSpotLightCone(params); }
	else if (sFunctionName == "setCameraPosition"){ func = new FunctionSetCameraPosition(params); }
	else if (sFunctionName == "setCameraViewPosition"){ func = new FunctionSetCameraViewPosition(params); }
	else if (sFunctionName == "setCameraViewSize"){ func = new FunctionSetCameraViewSize(params); }
	else if (sFunctionName == "playMusic"){ func = new FunctionPlayMusic(params); }
	else if (sFunctionName == "setMusicVolume"){ func = new FunctionSetMusicVolume(params); }
	else if (sFunctionName == "createTimer"){ func = new FunctionCreateTimer(params); }
	else if (sFunctionName == "setCameraOrientation"){ func = new FunctionSetCameraOrientation(params); }
	else if (sFunctionName == "setEntityVisible"){ func = new FunctionSetEntityVisible(params); }
	else if (sFunctionName == "greaterThan"){ func = new FunctionGreaterThan(params); }
	else if (sFunctionName == "lessThan"){ func = new FunctionLessThan(params); }
	else if (sFunctionName == "equal"){ func = new FunctionEqual(params); }
	else if (sFunctionName == "createSound"){ func = new FunctionCreateSound(params); }
	else if (sFunctionName == "createSoundChannel"){ func = new FunctionCreateSoundChannel(params); }
	else if (sFunctionName == "deleteSound"){ func = new FunctionDeleteSound(params); }
	else if (sFunctionName == "setSoundAttenuation"){ func = new FunctionSetSoundAttenuation(params); }
	else if (sFunctionName == "setSoundBuffer"){ func = new FunctionSetSoundBuffer(params); }
	else if (sFunctionName == "setSoundChannelVolume"){ func = new FunctionSetSoundChannelVolume(params); }
	else if (sFunctionName == "setSoundListenerPosition"){ func = new FunctionSetSoundListenerPosition(params); }
	else if (sFunctionName == "setSoundMinDistance"){ func = new FunctionSetSoundMinDistance(params); }
	else if (sFunctionName == "playSound"){ func = new FunctionPlaySound(params); }
	else if (sFunctionName == "if"){ func = new FunctionIf(params); }
	else if (sFunctionName == "add"){ func = new FunctionAdd(params); }
	else if (sFunctionName == "createEntityGroup"){ func = new FunctionCreateEntityGroup(params); }
	else if (sFunctionName == "setEntityGroupRenderable"){ func = new FunctionSetEntityGroupRenderable(params); }
	else if (sFunctionName == "createControlSet"){ func = new FunctionCreateControlSet(params); }
	else if (sFunctionName == "activateControlSet"){ func = new FunctionActivateControlSet(params); }
	else if (sFunctionName == "deactivateControlSet"){ func = new FunctionDeactivateControlSet(params); }
	else if (sFunctionName == "deleteControlSet"){ func = new FunctionDeleteControlSet(params); }
	else if (sFunctionName == "bindScriptKeyAction"){ func = new FunctionBindScriptKeyAction(params); }
	else if (sFunctionName == "bindEntityKeyAction"){ func = new FunctionBindEntityKeyAction(params); }
	else if (sFunctionName == "bindCameraToEntity"){ func = new FunctionBindCameraToEntity(params); }
	else if (sFunctionName == "bindSpotLightToEntity"){ func = new FunctionBindSpotLightToEntity(params); }
	else if (sFunctionName == "bindEntityMovementMapping"){ func = new FunctionBindEntityMovementMapping(params); }
	else if (sFunctionName == "setCursorMode"){ func = new FunctionSetCursorMode(params); }

	return func;
}
#ifndef FUNCTION_REGISTER_H
#define FUNCTION_REGISTER_H

#include "Game/Modules/FunctionAssign.h"
#include "Game/Modules/FunctionLog.h"
#include "Game/Modules/FunctionGetRandomInt.h"
#include "Game/Modules/FunctionGetRandomFloat.h"

#include "Game/Modules/FunctionCreateScene.h"
#include "Game/Modules/FunctionDeleteScene.h"
#include "Game/Modules/FunctionActivateScene.h"
#include "Game/Modules/FunctionDeactivateScene.h"

#include "Game/Modules/FunctionLoadEntitySpecs.h"
#include "Game/Modules/FunctionLoadInterface.h"
#include "Game/Modules/FunctionLoadModels.h"
#include "Game/Modules/FunctionLoadMusic.h"
#include "Game/Modules/FunctionLoadSound.h"

#include "Game/Modules/FunctionLoadScript.h"
#include "Game/Modules/FunctionUnloadScript.h"
#include "Game/Modules/FunctionExecuteScript.h"

#include "Game/Modules/FunctionCreateEntity.h"
#include "Game/Modules/FunctionDeleteEntity.h"
#include "Game/Modules/FunctionSetEntityPosition.h"
#include "Game/Modules/FunctionSetEntityScale.h"
#include "Game/Modules/FunctionSetEntityOrientation.h"

#include "Game/Modules/FunctionCreateAmbientLight.h"
#include "Game/Modules/FunctionCreatePointLight.h"
#include "Game/Modules/FunctionCreateSpotLight.h"
#include "Game/Modules/FunctionCreateCamera.h"
#include "Game/Modules/FunctionDeleteAmbientLight.h"
#include "Game/Modules/FunctionDeletePointLight.h"
#include "Game/Modules/FunctionDeleteSpotLight.h"
#include "Game/Modules/FunctionDeleteCamera.h"
#include "Game/Modules/FunctionEnableAmbientLight.h"
#include "Game/Modules/FunctionEnablePointLight.h"
#include "Game/Modules/FunctionEnableSpotLight.h"
#include "Game/Modules/FunctionEnableCamera.h"
#include "Game/Modules/FunctionDisableAmbientLight.h"
#include "Game/Modules/FunctionDisablePointLight.h"
#include "Game/Modules/FunctionDisableSpotLight.h"
#include "Game/Modules/FunctionDisableCamera.h"

#include "Game/Modules/FunctionSetAmbientLightColour.h"
#include "Game/Modules/FunctionSetPointLightColour.h"
#include "Game/Modules/FunctionSetSpotLightColour.h"
#include "Game/Modules/FunctionSetPointLightPosition.h"
#include "Game/Modules/FunctionSetSpotLightPosition.h"
#include "Game/Modules/FunctionSetSpotLightTarget.h"
#include "Game/Modules/FunctionSetSpotLightCone.h"
#include "Game/Modules/FunctionSetCameraPosition.h"
#include "Game/Modules/FunctionSetCameraViewPosition.h"
#include "Game/Modules/FunctionSetCameraViewSize.h"

#include "Game/Modules/FunctionPlayMusic.h"
#include "Game/Modules/FunctionSetMusicVolume.h"

#include "Game/Modules/FunctionCreateTimer.h"
#include "Game/Modules/FunctionSetCameraOrientation.h"
#include "Game/Modules/FunctionSetEntityVisible.h"

#include "Game/Modules/FunctionGreaterThan.h"
#include "Game/Modules/FunctionLessThan.h"
#include "Game/Modules/FunctionEqual.h"
#include "Game/Modules/FunctionIf.h"
#include "Game/Modules/FunctionAdd.h"

#include "Game/Modules/FunctionCreateSound.h"
#include "Game/Modules/FunctionCreateSoundChannel.h"
#include "Game/Modules/FunctionDeleteSound.h"
#include "Game/Modules/FunctionSetSoundAttenuation.h"
#include "Game/Modules/FunctionSetSoundBuffer.h"
#include "Game/Modules/FunctionSetSoundChannelVolume.h"
#include "Game/Modules/FunctionSetSoundListenerPosition.h"
#include "Game/Modules/FunctionSetSoundMinDistance.h"
#include "Game/Modules/FunctionPlaySound.h"

#include "Game/Modules/FunctionCreateEntityGroup.h"
#include "Game/Modules/FunctionSetEntityGroupRenderable.h"

#include "Game/Modules/FunctionCreateControlSet.h"
#include "Game/Modules/FunctionActivateControlSet.h"
#include "Game/Modules/FunctionDeactivateControlSet.h"
#include "Game/Modules/FunctionDeleteControlSet.h"
#include "Game/Modules/FunctionBindScriptKeyAction.h"
#include "Game/Modules/FunctionBindEntityKeyAction.h"
#include "Game/Modules/FunctionBindCameraToEntity.h"
#include "Game/Modules/FunctionBindSpotLightToEntity.h"
#include "Game/Modules/FunctionBindEntityMovementMapping.h"
#include "Game/Modules/FunctionSetCursorMode.h"

#include <map>
#include <vector>
#include <string>

class FunctionRegister
{
	private:
		std::map<std::string, Function*> m_functions;
		std::vector<std::string> m_functionDefinitions;

	protected:

	public:
		FunctionRegister();
		~FunctionRegister();

		bool functionExists(const std::string& sFuncName) const;
		const std::vector<std::string>& getFunctionDefinitions();
		Function* buildFunction(std::string sFunctionName, std::vector<ScriptParam>& params);
};

#endif
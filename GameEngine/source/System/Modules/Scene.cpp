#include "System/Modules/Scene.h"

Scene::Scene()
{
}

Scene::Scene(std::string sName) :
m_sShaderKeyNumAmbLgts("iNumAmbientLights"),
m_sShaderKeyNumPoiLgts("iNumPointLights"),
m_sShaderKeyNumSpoLgts("iNumSpotLights")
{
	m_sName = sName;
	WindowEventsManager::getInstance()->addWindowListener(this);

	m_iCursorMode = GLFW_CURSOR_NORMAL;

	m_window = nullptr;
	m_shaderManager = nullptr;
	for (int i = 0; i < 20; ++i)
	{
		m_renderables[i] = std::make_pair(nullptr, RenderModes::PER_CAMERA);
	}
	
	m_uiNumEnabledCameras = 0;

	// Initialise id trackers. Starting at 1 so that id 0 can be used to indicate "no id" when
	// using unsigned integers
	m_uiNextLightId = 1;
	m_uiNextCameraId = 1;

	m_fLastCursorX = 0;
	m_fLastCursorY = 0;
}

Scene::~Scene()
{
	InputManager::getInstance()->removeInputListener(this);
	WindowEventsManager::getInstance()->removeWindowListener(this);
}

void Scene::onCharacterTyped(unsigned int uiChar)
{
}

void Scene::onScroll(double fXOffset, double fYOffset)
{
}

void Scene::onCursorEnter()
{
}

void Scene::onCursorExit()
{
}

void Scene::onCursorMoved(double fXPos, double fYPos)
{
	double xDelta = fXPos - m_fLastCursorX;
	double yDelta = fYPos - m_fLastCursorY;

	if (m_activeControlSet)
	{
		if (m_activeControlSet->hasMovementMapping())
		{
			m_activeControlSet->getMovementMapping()->onMouseMoved(xDelta, yDelta);
		}
	}

	m_fLastCursorX = fXPos;
	m_fLastCursorY = fYPos;
}

void Scene::onMousePressed(int iButton, int iMods)
{
	if (m_activeControlSet)
	{
		if (m_activeControlSet->hasMouseMapping(iButton, GLFW_PRESS, iMods))
		{
			m_activeControlSet->getMouseAction(iButton, GLFW_PRESS, iMods)->onMousePressed(iButton, iMods);
		}
	}
}

void Scene::onMouseReleased(int iButton, int iMods)
{
	if (m_activeControlSet)
	{
		if (m_activeControlSet->hasMouseMapping(iButton, GLFW_RELEASE, iMods))
		{
			m_activeControlSet->getMouseAction(iButton, GLFW_RELEASE, iMods)->onMousePressed(iButton, iMods);
		}
	}
}

void Scene::onKeyPressed(int iKey, int iScancode, int iMods)
{
	if (m_activeControlSet)
	{
		if (m_activeControlSet->hasKeyMapping(iKey, GLFW_PRESS, iMods))
		{
			m_activeControlSet->getKeyAction(iKey, GLFW_PRESS, iMods)->onKeyPressed(iKey, iMods);
		}
	}
}

void Scene::onKeyReleased(int iKey, int iScancode, int iMods)
{
	if (m_activeControlSet)
	{
		if (m_activeControlSet->hasKeyMapping(iKey, GLFW_RELEASE, iMods))
		{
			m_activeControlSet->getKeyAction(iKey, GLFW_RELEASE, iMods)->onKeyReleased(iKey, iMods);
		}
	}
}

std::string Scene::getName() const
{
	return m_sName;
}

void Scene::onActivation()
{
	InputManager::getInstance()->addInputListener(this);

	// Update the last known window and frame buffer sizes
	if (m_window)
	{
		int iWidth;
		int iHeight;

		glfwGetWindowSize(m_window, &iWidth, &iHeight);
		m_fWindowWidth = (float)iWidth;
		m_fWindowHeight = (float)iHeight;

		glfwGetFramebufferSize(m_window, &iWidth, &iHeight);
		m_fFrameBufferWidth = (float)iWidth;
		m_fFrameBufferHeight = (float)iHeight;
	}

	// Configure the shader
	m_shaderManager->activateShader("multi_light");
	Shader* shader = m_shaderManager->getShader("multi_light");
	if (shader)
	{
		// Resend number of active lights
		shader->postInt(m_sShaderKeyNumAmbLgts, m_activeAmbientLights.size());
		shader->postInt(m_sShaderKeyNumPoiLgts, m_activePointLights.size());
		shader->postInt(m_sShaderKeyNumSpoLgts, m_activeSpotLights.size());

		// Also resend all of the light information
		unsigned int uiIndex = 0;
		for (std::shared_ptr<AmbientLight>& light : m_activeAmbientLights)
		{
			if (light->hasBeenModified())
			{
				std::string sTargetIndexAsString = std::to_string(uiIndex);
				light->postConfigToShader(shader, sTargetIndexAsString);
			}
			++uiIndex;
		}

		uiIndex = 0;
		for (std::shared_ptr<PointLight>& light : m_activePointLights)
		{
			if (light->hasBeenModified())
			{
				std::string sTargetIndexAsString = std::to_string(uiIndex);
				light->postConfigToShader(shader, sTargetIndexAsString);
			}
			++uiIndex;
		}

		uiIndex = 0;
		for (std::shared_ptr<SpotLight>& light : m_activeSpotLights)
		{
			if (light->hasBeenModified())
			{
				std::string sTargetIndexAsString = std::to_string(uiIndex);
				light->postConfigToShader(shader, sTargetIndexAsString);
			}
			++uiIndex;
		}
	}
	
	// Switch to the desired cursor mode
	if (m_window)
	{
		glfwSetInputMode(m_window, GLFW_CURSOR, m_iCursorMode);
	}
}

void Scene::onDeactivation()
{
	InputManager::getInstance()->removeInputListener(this);
}

void Scene::onUpdate()
{
}

void Scene::onRender()
{
	// Clear the previous frame
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Check the minimum requirements to render a frame
	if (!m_shaderManager || m_uiNumEnabledCameras == 0)
	{
		return;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////
	// Send light updates where necessary
	Shader* shader = m_shaderManager->getShader("multi_light");
	if (shader)
	{
		unsigned int uiIndex = 0;
		for (std::shared_ptr<AmbientLight>& light : m_activeAmbientLights)
		{
			if (light->hasBeenModified())
			{
				std::string sTargetIndexAsString = std::to_string(uiIndex);
				light->postConfigToShader(shader, sTargetIndexAsString);
			}
			++uiIndex;
		}

		uiIndex = 0;
		for (std::shared_ptr<PointLight>& light : m_activePointLights)
		{
			if (light->hasBeenModified())
			{
				std::string sTargetIndexAsString = std::to_string(uiIndex);
				light->postConfigToShader(shader, sTargetIndexAsString);
			}
			++uiIndex;
		}

		uiIndex = 0;
		for (std::shared_ptr<SpotLight>& light : m_activeSpotLights)
		{
			if (light->hasBeenModified())
			{
				std::string sTargetIndexAsString = std::to_string(uiIndex);
				light->postConfigToShader(shader, sTargetIndexAsString);
			}
			++uiIndex;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////

	// Draw each renderable that is registered with the Scene
	for (int i = 0; i < 20; ++i)
	{
		if (m_renderables[i].first != nullptr)
		{
			if (m_renderables[i].second == RenderModes::PER_CAMERA)
			{
				// Render the renderable for each camera
				for (std::shared_ptr<Camera>& camera : m_cameras)
				{
					if (camera->isEnabled())
					{
						m_shaderManager->activateShader("multi_light");
						std::string s11 = "vEyePos";
						shader->postVec3(s11, camera->getPosition());

						// Set the viewport
						glm::vec2 size = camera->getViewSize();
						glm::vec2 pos = camera->getViewPosition();
						size.x *= m_fFrameBufferWidth;
						size.y *= m_fFrameBufferHeight;
						pos.x *= m_fFrameBufferWidth;
						pos.y *= m_fFrameBufferHeight;
						glViewport((int)pos.x, (int)pos.y, (int)size.x, (int)size.y);

						// Create the render data. We cant just send the camera matrix from
						// here because the active shader might not use it
						RenderData m_renderData;
						m_renderData.projMatrix = camera->getProjMatrix();
						m_renderData.viewMatrix = camera->getViewMatrix();

						// Render
						m_renderables[i].first->render(*m_shaderManager, m_renderData);
					}
				}
			}
			else
			{
				// Set the viewport to fullscreen
				glViewport(0, 0, (int)m_fFrameBufferWidth, (int)m_fFrameBufferHeight);
			
				// Create the render data. Note that some values will be invalid when not
				// rendering relative to a Camera
				RenderData m_renderData;

				// Render
				m_renderables[i].first->render(*m_shaderManager, m_renderData);
			}
		}
	}
}

void Scene::onFramebufferResized(int iWidth, int iHeight)
{
	m_fFrameBufferWidth = (float)iWidth;
	m_fFrameBufferHeight = (float)iHeight;
}

void Scene::onWindowResized(int iWidth, int iHeight)
{
	m_fWindowWidth = (float)iWidth;
	m_fWindowHeight = (float)iHeight;

	// Update camera aspect ratios where appropriate
	for (std::shared_ptr<Camera>& camera : m_cameras)
	{
		if (camera->isEnabled() && camera->isAutoAspectRatioEnabled())
		{
			camera->setAspectRatio(m_fFrameBufferWidth * camera->getViewSize().x,
								   m_fFrameBufferHeight * camera->getViewSize().y);
		}
	}
}

void Scene::linkComponents(GLFWwindow* window, ShaderManager* shaderManager)
{
	m_window = window;
	m_shaderManager = shaderManager;
}

void Scene::addRenderable(Renderable* r, int iIndex, RenderModes mode)
{
	// This function has default values for compatibility reasons. They will eventually
	// be removed and replaced with mandatory decisions
	if (iIndex == -1)
	{
		// Take the next available slot
		unsigned int uiCrnt = 0;
		for (; uiCrnt < 20; ++uiCrnt)
		{
			if (m_renderables[uiCrnt].first == nullptr)
			{
				m_renderables[uiCrnt] = std::make_pair(r, mode);
				return;
			}
		}
	}
	else if (iIndex > -1 && iIndex < 20)
	{
		m_renderables[iIndex] = std::make_pair(r, mode);
	}
}

void Scene::removeRenderable(Renderable* r)
{
	unsigned int uiCrnt = 0;
	for (; uiCrnt < 20; ++uiCrnt)
	{
		if (m_renderables[uiCrnt].first == r)
		{
			m_renderables[uiCrnt].first = nullptr;
		}
	}
}

void Scene::setCursorMode(int iCursorMode)
{
	// Store the new mode only if it was valid
	if (iCursorMode == GLFW_CURSOR_NORMAL || 
		iCursorMode == GLFW_CURSOR_HIDDEN || 
		iCursorMode == GLFW_CURSOR_DISABLED)
	{	
		m_iCursorMode = iCursorMode;
	}	
	
	// Apply the new mode if the window was valid
	if (m_window)
	{
		glfwSetInputMode(m_window, GLFW_CURSOR, m_iCursorMode);
	}
}

unsigned int Scene::createLight(LightTypes type)
{
	if (type == LightTypes::AMBIENT)
	{
		std::shared_ptr<AmbientLight> ambientLight = std::make_shared<AmbientLight>();
		m_ambientLights.push_back(ambientLight);
		ambientLight->setId(m_uiNextLightId);
		ambientLight->addLightListener(this);
		++m_uiNextLightId;

		return ambientLight->getId();
	}
	else if(type == LightTypes::POINT)
	{
		std::shared_ptr<PointLight> pointLight = std::make_shared<PointLight>();
		m_pointLights.push_back(pointLight);
		pointLight->setId(m_uiNextLightId);
		pointLight->addLightListener(this);
		++m_uiNextLightId;

		return pointLight->getId();
	}
	else if (type == LightTypes::SPOT)
	{
		std::shared_ptr<SpotLight> spotLight = std::make_shared<SpotLight>();
		m_spotLights.push_back(spotLight);
		spotLight->setId(m_uiNextLightId);
		spotLight->addLightListener(this);
		++m_uiNextLightId;

		return spotLight->getId();
	}
	else
	{
		return 0;
	}
}

std::shared_ptr<AmbientLight> Scene::getAmbientLight(unsigned int uiLightId)
{
	for (std::shared_ptr<AmbientLight>& light : m_ambientLights)
	{
		if (light->getId() == uiLightId)
		{
			return light;
		}
	}

	return nullptr;
}

std::shared_ptr<PointLight> Scene::getPointLight(unsigned int uiLightId)
{
	for (std::shared_ptr<PointLight>& light : m_pointLights)
	{
		if (light->getId() == uiLightId)
		{
			return light;
		}
	}

	return nullptr;
}

std::shared_ptr<SpotLight> Scene::getSpotLight(unsigned int uiLightId)
{
	for (std::shared_ptr<SpotLight>& light : m_spotLights)
	{
		if (light->getId() == uiLightId)
		{
			return light;
		}
	}

	return nullptr;
}

bool Scene::deleteLight(unsigned int uiLightId)
{
	LightTypes type = getLightType(uiLightId);

	if (type == LightTypes::AMBIENT)
	{
		// If the light is enabled, disable it
		std::shared_ptr<AmbientLight> ambLight = getAmbientLight(uiLightId);
		if (ambLight->isEnabled())
		{
			ambLight->setEnabled(false);
		}

		// Delete the light
		unsigned int uiCrnt = 0;
		unsigned int uiSize = m_ambientLights.size();
		for (; uiCrnt < uiSize; ++uiCrnt)
		{
			if (m_ambientLights.at(uiCrnt)->getId() == uiLightId)
			{
				m_ambientLights.erase(m_ambientLights.begin() + uiCrnt);
				return true;
			}
		}

		return false;
	}
	else if (type == LightTypes::POINT)
	{
		// If the light is enabled, disable it
		std::shared_ptr<PointLight> pointLight = getPointLight(uiLightId);
		if (pointLight->isEnabled())
		{
			pointLight->setEnabled(false);
		}

		// Delete the light
		unsigned int uiCrnt = 0;
		unsigned int uiSize = m_pointLights.size();
		for (; uiCrnt < uiSize; ++uiCrnt)
		{
			if (m_pointLights.at(uiCrnt)->getId() == uiLightId)
			{
				m_pointLights.erase(m_pointLights.begin() + uiCrnt);
				return true;
			}
		}

		return false;
	}
	else if (type == LightTypes::SPOT)
	{
		// If the light is enabled, disable it
		std::shared_ptr<SpotLight> spotLight = getSpotLight(uiLightId);
		if (spotLight->isEnabled())
		{
			spotLight->setEnabled(false);
		}

		// Delete the light
		unsigned int uiCrnt = 0;
		unsigned int uiSize = m_spotLights.size();
		for (; uiCrnt < uiSize; ++uiCrnt)
		{
			if (m_spotLights.at(uiCrnt)->getId() == uiLightId)
			{
				m_spotLights.erase(m_spotLights.begin() + uiCrnt);
				return true;
			}
		}

		return false;
	}

	return false;
}

void Scene::onLightEnabled(unsigned int uiLightId)
{
	if (!m_shaderManager)
	{
		return;
	}

	LightTypes type = getLightType(uiLightId);

	if (type == LightTypes::AMBIENT)
	{
		std::shared_ptr<AmbientLight> ambLight = getAmbientLight(uiLightId);

		// Check there is space to add another light. If there isnt, this light will replace the
		// most recently added light.
		if (m_activeAmbientLights.size() >= m_lightingLimits.getMaxAmbientLights())
		{
			m_activeAmbientLights.pop_back();
		}
		m_activeAmbientLights.push_back(ambLight);

		// Post the new light data to the shader
		m_shaderManager->activateShader("multi_light");
		std::string sTargetIndexAsString = std::to_string(m_activeAmbientLights.size() - 1);
		ambLight->postConfigToShader(m_shaderManager->getShader("multi_light"), sTargetIndexAsString);
	
		m_shaderManager->getShader("multi_light")->postInt(m_sShaderKeyNumAmbLgts, m_activeAmbientLights.size());
	}
	else if (type == LightTypes::POINT)
	{
		std::shared_ptr<PointLight> pointLight = getPointLight(uiLightId);

		// Check there is space to add another light. If there isnt, this light will replace the
		// most recently added light.
		if (m_activePointLights.size() >= m_lightingLimits.getMaxPointLights())
		{
			m_activePointLights.pop_back();
		}
		m_activePointLights.push_back(pointLight);

		// Post the new light data to the shader
		m_shaderManager->activateShader("multi_light");
		std::string sTargetIndexAsString = std::to_string(m_activePointLights.size() - 1);
		pointLight->postConfigToShader(m_shaderManager->getShader("multi_light"), sTargetIndexAsString);

		m_shaderManager->getShader("multi_light")->postInt(m_sShaderKeyNumPoiLgts, m_activePointLights.size());
	}
	else if (type == LightTypes::SPOT)
	{
		std::shared_ptr<SpotLight> spotLight = getSpotLight(uiLightId);

		// Check there is space to add another light. If there isnt, this light will replace the
		// most recently added light.
		if (m_activeSpotLights.size() >= m_lightingLimits.getMaxSpotLights())
		{
			m_activeSpotLights.pop_back();
		}
		m_activeSpotLights.push_back(spotLight);

		// Post the new light data to the shader
		m_shaderManager->activateShader("multi_light");
		std::string sTargetIndexAsString = std::to_string(m_activeSpotLights.size() - 1);
		spotLight->postConfigToShader(m_shaderManager->getShader("multi_light"), sTargetIndexAsString);

		m_shaderManager->getShader("multi_light")->postInt(m_sShaderKeyNumSpoLgts, m_activeSpotLights.size());
	}
	else
	{
		// Unknown light type
	}
}

void Scene::onLightDisabled(unsigned int uiLightId)
{
	if (!m_shaderManager)
	{
		return;
	}

	LightTypes type = getLightType(uiLightId);

	if (type == LightTypes::AMBIENT)
	{
		// Remove the light from the active lights vector
		unsigned int uiCrnt = 0;
		unsigned int uiSize = m_activeAmbientLights.size();
		for (; uiCrnt < uiSize ; ++uiCrnt)
		{
			if (m_activeAmbientLights.at(uiCrnt)->getId() == uiLightId)
			{
				m_activeAmbientLights.erase(m_activeAmbientLights.begin() + uiCrnt);
				break;
			}
		}

		// Resend all light information that has moved
		--uiCrnt;
		uiSize = m_activeAmbientLights.size();
		m_shaderManager->activateShader("multi_light");
		Shader* shader = m_shaderManager->getShader("multi_light");
		for (; uiCrnt < uiSize; ++uiCrnt)
		{
			std::string sTargetIndexAsString = std::to_string(uiCrnt);
			m_activeAmbientLights.at(uiCrnt)->postConfigToShader(shader, sTargetIndexAsString);
		}

		// Resend the active number of lights
		shader->postInt(m_sShaderKeyNumAmbLgts, m_activeAmbientLights.size());
	}
	else if (type == LightTypes::POINT)
	{
		// Remove the light from the active lights vector
		unsigned int uiCrnt = 0;
		unsigned int uiSize = m_activePointLights.size();
		for (; uiCrnt < uiSize; ++uiCrnt)
		{
			if (m_activePointLights.at(uiCrnt)->getId() == uiLightId)
			{
				m_activePointLights.erase(m_activePointLights.begin() + uiCrnt);
				break;
			}
		}

		// Resend all light information that has moved
		--uiCrnt;
		uiSize = m_activePointLights.size();
		m_shaderManager->activateShader("multi_light");
		Shader* shader = m_shaderManager->getShader("multi_light");
		for (; uiCrnt < uiSize; ++uiCrnt)
		{
			std::string sTargetIndexAsString = std::to_string(uiCrnt);
			m_activePointLights.at(uiCrnt)->postConfigToShader(shader, sTargetIndexAsString);
		}

		// Resend the active number of lights
		shader->postInt(m_sShaderKeyNumPoiLgts, m_activePointLights.size());
	}
	else if (type == LightTypes::SPOT)
	{
		// Remove the light from the active lights vector
		unsigned int uiCrnt = 0;
		unsigned int uiSize = m_activeSpotLights.size();
		for (; uiCrnt < uiSize; ++uiCrnt)
		{
			if (m_activeSpotLights.at(uiCrnt)->getId() == uiLightId)
			{
				m_activeSpotLights.erase(m_activeSpotLights.begin() + uiCrnt);
				break;
			}
		}

		// Resend all light information that has moved
		--uiCrnt;
		uiSize = m_activeSpotLights.size();
		m_shaderManager->activateShader("multi_light");
		Shader* shader = m_shaderManager->getShader("multi_light");
		for (; uiCrnt < uiSize; ++uiCrnt)
		{
			std::string sTargetIndexAsString = std::to_string(uiCrnt);
			m_activeSpotLights.at(uiCrnt)->postConfigToShader(shader, sTargetIndexAsString);
		}

		// Resend the active number of lights
		shader->postInt(m_sShaderKeyNumSpoLgts, m_activeSpotLights.size());
	}
	else
	{
		// Unknown light type
	}
}

Scene::LightTypes Scene::getLightType(unsigned int uiLightId) const 
{
	for (const std::shared_ptr<PointLight>& light : m_pointLights)
	{
		if (light->getId() == uiLightId)
		{
			return LightTypes::POINT;
		}
	}	
	
	for (const std::shared_ptr<SpotLight>& light : m_spotLights)
	{
		if (light->getId() == uiLightId)
		{
			return LightTypes::SPOT;
		}
	}	
	
	for (const std::shared_ptr<AmbientLight>& light : m_ambientLights)
	{
		if (light->getId() == uiLightId)
		{
			return LightTypes::AMBIENT;
		}
	}

	return LightTypes::UNKNOWN_TYPE;
}

unsigned int Scene::createCamera()
{
	std::shared_ptr<Camera> camera = std::make_shared<Camera>();
	m_cameras.push_back(camera);
	camera->setId(m_uiNextCameraId);
	camera->addListener(this);
	++m_uiNextCameraId;

	return camera->getId();
}

std::shared_ptr<Camera> Scene::getCamera(unsigned int uiCameraId)
{
	for (std::shared_ptr<Camera>& camera : m_cameras)
	{
		if (camera->getId() == uiCameraId)
		{
			return camera;
		}
	}

	return nullptr;
}

bool Scene::deleteCamera(unsigned int uiCameraId)
{
	unsigned int uiCrntIndex = 0;
	for (std::shared_ptr<Camera>& camera : m_cameras)
	{
		if (camera->getId() == uiCameraId)
		{
			m_cameras.erase(m_cameras.begin() + uiCrntIndex);
			return true;
		}
		++uiCrntIndex;
	}

	return false;
}

void Scene::onCameraEnabled(int iCameraId)
{
	for (std::shared_ptr<Camera>& camera : m_cameras)
	{
		if (camera->getId() == iCameraId)
		{
			++m_uiNumEnabledCameras;
			if (camera->isAutoAspectRatioEnabled())
			{
				camera->setAspectRatio(m_fFrameBufferWidth * camera->getViewSize().x,
								   	   m_fFrameBufferHeight * camera->getViewSize().y);
				return;
			}		
		}
	}
}

void Scene::onCameraDisabled(int iCameraId)
{
	--m_uiNumEnabledCameras;
}

void Scene::onAutoAspectEnabled(int iCameraId)
{
	for (std::shared_ptr<Camera>& camera : m_cameras)
	{
		if (camera->getId() == iCameraId)
		{
			camera->setAspectRatio(m_fFrameBufferWidth * camera->getViewSize().x,
								   m_fFrameBufferHeight * camera->getViewSize().y);
			return;
		}
	}
}

void Scene::onAutoAspectDisabled(int iCameraId)
{
}

void Scene::onViewResized(int iCameraId)
{
	for (std::shared_ptr<Camera>& camera : m_cameras)
	{
		if (camera->getId() == iCameraId)
		{
			camera->setAspectRatio(m_fFrameBufferWidth * camera->getViewSize().x,
								   m_fFrameBufferHeight * camera->getViewSize().y);
			return;
		}
	}
}

unsigned int Scene::createControlSet()
{
	return m_controlSets.add(std::make_shared<ControlSet>());
}

void Scene::activateControlSet(unsigned int uiId)
{
	if (m_controlSets.exists(uiId))
	{
		m_activeControlSet = m_controlSets.get(uiId);
	}
}

void Scene::deactivateControlSet(unsigned int uiId)
{
	if (m_controlSets.exists(uiId))
	{
		if (m_controlSets.get(uiId) == m_activeControlSet)
		{
			m_activeControlSet = nullptr;
		}
	}
}

std::shared_ptr<ControlSet> Scene::getControlSet(unsigned int uiId)
{
	return m_controlSets.get(uiId);
}

void Scene::deleteControlSet(unsigned int uiId)
{
	if (m_controlSets.exists(uiId))
	{
		if (m_controlSets.get(uiId) == m_activeControlSet)
		{
			m_activeControlSet = nullptr;
		}	
		m_controlSets.remove(uiId);
	}
}
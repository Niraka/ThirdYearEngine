#include "System/Modules/Camera.h"

Camera::Camera() :
HasId(false)
{
	reset();
}

Camera::~Camera()
{
}

void Camera::addListener(CameraListener* l)
{
	m_listeners.add(l);
}

int Camera::removeListener(CameraListener* l)
{
	return m_listeners.remove(l);
}

void Camera::setEnabled(bool bEnabled)
{
	if (bEnabled && !m_bEnabled)
	{
		m_bEnabled = bEnabled;
		unsigned int uiCrnt = 0;
		unsigned int uiSize = m_listeners.size();
		for (; uiCrnt < uiSize; ++uiCrnt)
		{
			m_listeners.at(uiCrnt)->onCameraEnabled(getId());
		}
	}
	else if (!bEnabled && m_bEnabled)
	{
		m_bEnabled = bEnabled;
		unsigned int uiCrnt = 0;
		unsigned int uiSize = m_listeners.size();
		for (; uiCrnt < uiSize; ++uiCrnt)
		{
			m_listeners.at(uiCrnt)->onCameraDisabled(getId());
		}
	}
}

bool Camera::isEnabled() const
{
	return m_bEnabled;
}

void Camera::setAutoAspectRatioEnabled(bool bEnabled)
{
	if (bEnabled && !m_bAutoAspectRatio)
	{
		m_bAutoAspectRatio = bEnabled;

		unsigned int uiCrnt = 0;
		unsigned int uiSize = m_listeners.size();
		for (; uiCrnt < uiSize; ++uiCrnt)
		{
			m_listeners.at(uiCrnt)->onAutoAspectDisabled(getId());
		}
	}
	else if (!bEnabled && m_bAutoAspectRatio)
	{
		m_bAutoAspectRatio = bEnabled;

		unsigned int uiCrnt = 0;
		unsigned int uiSize = m_listeners.size();
		for (; uiCrnt < uiSize; ++uiCrnt)
		{
			m_listeners.at(uiCrnt)->onAutoAspectEnabled(getId());
		}
	}
}

bool Camera::isAutoAspectRatioEnabled() const
{
	return m_bAutoAspectRatio;
}

void Camera::setViewSize(glm::vec2 size)
{
	m_viewSize = size;
}

void Camera::setViewPosition(glm::vec2 position)
{
	m_viewPosition = position;
}

glm::vec2 Camera::getViewSize() const
{
	return m_viewSize;
}

glm::vec2 Camera::getViewPosition() const
{
	return m_viewPosition;
}

void Camera::buildProjectionMatrix()
{
	m_projection = glm::perspective(m_fFieldOfView, m_fAspectRatio, m_fNearClip, m_fFarClip);
}

float Camera::getFOV() const
{
	return m_mathsUtils.toDegree(m_fFieldOfView);
}

float Camera::getAspectRatio() const
{
	return m_fAspectRatio;
}

float Camera::getNearClip() const
{
	return m_fNearClip;
}

float Camera::getFarClip() const
{
	return m_fFarClip;
}

void Camera::setFOV(float fFOV)
{
	if (fFOV > 0.f && fFOV < 180.f)
	{
		m_fFieldOfView = m_mathsUtils.toRadian(fFOV);
		buildProjectionMatrix();
	}
}

void Camera::setAspectRatio(float fWidth, float fHeight)
{
	float fAspect = fWidth / fHeight;
	if (fAspect > 0.f)
	{
		m_fAspectRatio = fAspect;
		buildProjectionMatrix();
	}
}

void Camera::setClippingPlanes(float fNear, float fFar)
{
	if (fNear > 0.f && fFar > fNear)
	{
		m_fNearClip = fNear;
		m_fFarClip = fFar;
		buildProjectionMatrix();
	}
}

void Camera::reset()
{
	m_viewSize.x = 1.f;
	m_viewSize.y = 1.f;
	m_viewPosition.x = 0;
	m_viewPosition.y = 0;

	m_bEnabled = false;
	m_bAutoAspectRatio = true;

	m_bInvertXAxis = true;
	m_bInvertYAxis = false;
	m_bInvertZAxis = false;

	m_position = glm::vec3(9.0f, 3.0f, 0.0f);
	m_targetPos = glm::vec3(-1.0f, 3.0f, 0.0f);

	m_fFieldOfView = m_mathsUtils.toRadian(100.0f);
	m_fNearClip = 0.01f;
	m_fFarClip = 200.0f;
	m_fAspectRatio = 4.0f / 3.0f;

	buildProjectionMatrix();
	buildViewMatrix();
}

void Camera::move(float fX, float fY, float fZ)
{
	if (m_bInvertXAxis)
	{
		m_position += m_xaxis * -fX;
	}
	else
	{
		m_position += m_xaxis * fX;
	}
	if (m_bInvertYAxis)
	{
		m_position += m_yaxis * -fY;
	}
	else
	{
		m_position += m_yaxis * fY;
	}
	if (m_bInvertZAxis)
	{
		m_position += m_zaxis * -fZ;
	}
	else
	{
		m_position += m_zaxis * fZ;
	}


	m_position.x += fX;
	m_position.y += fY;
	m_position.z += fZ;

	buildViewMatrix();
}

glm::vec3 Camera::getPosition() const
{
	return m_position;
}

void Camera::setPosition(glm::vec3 pos)
{
	m_position = pos;
	buildViewMatrix();
}

void Camera::setTarget(glm::vec3 pos)
{
	m_targetPos = pos;
	buildViewMatrix();
}

glm::mat4 Camera::getViewMatrix()
{
	return m_view;
}

glm::mat4 Camera::getProjMatrix()
{
	return m_projection;
}

void Camera::setOrientation(float fX, float fY, float fZ)
{
	rotate(fX, fY, fZ);
}

void Camera::rotate(float fX, float fY, float fZ)// this function is ???????????
{
	if (m_bInvertXAxis)
	{
		fX *= -1;
	}

	// Y need to be back to front to work correctly
	if (!m_bInvertYAxis)
	{
		fY *= -1;
	}
	if (m_bInvertZAxis)
	{
		fZ *= -1;
	}

	buildViewMatrix();
}

void Camera::buildViewMatrix()
{
	m_view = glm::lookAt(m_position, m_targetPos, glm::vec3(0, 1, 0));
}

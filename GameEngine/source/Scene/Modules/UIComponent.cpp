#include "Scene/Modules/UIComponent.h"

UIComponent::UIComponent()
{

}

UIComponent::~UIComponent()
{

}

void UIComponent::render(ShaderManager& shaderManager, const RenderData& data)
{
	if (m_bIsVisible)
	{
		
		this->onRender(shaderManager, data);
	}
}

void UIComponent::setVisible(bool vis)
{
	m_bIsVisible = vis;
}

bool UIComponent::getVisibile()
{
	return m_bIsVisible;
}

void UIComponent::setPosition(int x, int y)
{
	m_XPos = x;
	m_YPos = y;
}

int UIComponent::getX()
{
	return m_XPos;
}

int UIComponent::getY()
{
	return m_YPos;
}

void UIComponent::setSize(int w, int h)
{
	m_width = w;
	m_height = h;
}

int UIComponent::getWidth()
{
	return m_width;
}

int UIComponent::getHeight()
{
	return m_height;
}

bool UIComponent::checkClick(int xClick, int yClick)
{
	if (xClick > (m_XPos * m_screenWidth) - ((m_width * m_screenWidth) / 2) && (xClick < (m_XPos * m_screenWidth) + ((m_width * m_screenWidth) / 2)))
	{
		if (yClick > (m_YPos * m_screenHeight) - ((m_height * m_screenHeight) / 2) && (yClick < (m_YPos * m_screenHeight) + ((m_height * m_screenHeight) / 2)))
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

std::string UIComponent::getName()
{
	return m_name;
}

void UIComponent::updateWidth(int newWidth)
{
	m_screenWidth = newWidth;
}


void UIComponent::updateHeight(int newHeight)
{
	m_screenHeight = newHeight;
}
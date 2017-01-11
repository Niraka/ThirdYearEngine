#include "Scene/Modules/UIImage.h"


UIImage::UIImage()
{

}

UIImage::~UIImage()
{

}

void UIImage::onRender(ShaderManager& shaderManager, const RenderData& data)
{
	shaderManager.activateShader("image_shader");
	m_drawImage->setPosition(m_XPos*m_screenWidth, m_YPos*m_screenHeight);		//set the position and size of the image to be relative to the window size
	m_drawImage->setSize(m_width*m_screenWidth, m_height*m_screenHeight);
	m_drawImage->render(*(shaderManager.getShader("image_shader")));
}

UIImage::UIImage(std::string idName, Image* i, int x, int y, int w, int h, std::shared_ptr<GUIModule> GMod)
{
	m_name = idName;
	m_bIsVisible = true;
	m_drawImage = i;
	m_XPos = x;
	m_YPos = y;
	m_width = w;
	m_height = h;
	m_parentModule = GMod;
}

UIComponent::UIType UIImage::getType()
{
	return UIType::IMAGE;
}
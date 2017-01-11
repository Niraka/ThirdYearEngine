#include "Scene/Modules/UIText.h"
#include "Scene/Modules/GUIModule.h"

UIText::UIText()
{
}

UIText::~UIText()
{
}

UIText::UIText(std::string idName, Image* i, int x, int y, int w, int h, std::string text, std::shared_ptr<GUIModule> GMod)
{
	m_drawImage = i;
	m_name = idName;
	m_bIsVisible = true;
	m_textString = text;
	m_XPos = x;
	m_YPos = y;
	m_width = w;
	m_height = h;
	m_parentModule = GMod;

	this->setImageToText(text);
}

void UIText::onRender(ShaderManager& shaderManager, const RenderData& data)
{	
	int x = m_XPos;
	int y = m_YPos;

	int stringLength = std::strlen(m_textString.c_str());

	for (int i = 0; i < stringLength; i++)
	{
		/*FT_UInt glyph_index;

		glyph_index = FT_Get_Char_Index(m_parentModule->m_face, m_textString.at(i));

		FT_Load_Glyph(m_parentModule->m_face, glyph_index, FT_LOAD_DEFAULT);

		FT_Render_Glyph(m_parentModule->m_face->glyph, FT_RENDER_MODE_NORMAL);
		
		Bitmap drawBit(m_parentModule->g->bitmap.width, m_parentModule->g->bitmap.rows, Bitmap::Format::Format_RGBA, m_parentModule->g->bitmap.buffer);
		std::shared_ptr<Texture> drawTex = std::make_shared<Texture>(drawBit);
		Image drawImg(drawTex, x, y, drawBit.width(), drawBit.height());
		
		
		shaderManager.activateShader("image_shader");
		drawImg.render(*(shaderManager.getShader("image_shader")));

		x += m_parentModule->g->advance.x >> 6;
		y += m_parentModule->g->advance.y >> 6;*/
	}
}

UIComponent::UIType UIText::getType()
{
	return UIType::TEXT;
}

void UIText::setImageToText(std::string textString)
{	
	int stringLength = std::strlen(textString.c_str());		//get the number of characters in the string

	for (int i = 0; i < stringLength; ++i)
	{
		int asciiValue = textString.at(i);	//get the numerical ASCII value for the character
		int x = asciiValue / 10;	//The x xo-oridnate in the FontSet image is equal to the tens in the ASCII value
		int y = asciiValue - (x * 10);	//The y co-ordinate in the font set is equal to the units in ASCII value		E.g - ASCII value 36 = (3,6)
		std::pair<int, int> xy(x, y);
		
		m_textImages.add(xy);		//Add them to the VectorSim
	}
}


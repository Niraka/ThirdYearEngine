#include "System/Modules/Image.h"

const std::string Image::m_sSUTexture = "tex";
const std::string Image::m_sSUXOffset = "fXOffset";
const std::string Image::m_sSUYOffset = "fYOffset";
const std::string Image::m_sSUViewWidth = "fViewWidth";
const std::string Image::m_sSUViewHeight = "fViewHeight";

Image::Image()
{
	m_uiXPosition = 0;
	m_uiYPosition = 0;
	m_uiWidth = 100;
	m_uiHeight = 100;
}

Image::~Image()
{
}

Image::Image(std::shared_ptr<Texture> tex, unsigned int x, unsigned int y, unsigned int wd, unsigned int ht)
{
	m_texture = tex;
	m_uiXPosition = 0;
	m_uiYPosition = y;
	m_uiWidth = wd;
	m_uiHeight = ht;
}

bool Image::init()
{
	// Generate a 2D recentangle that will host the image
	float positionData[12];
	positionData[0] = m_uiXPosition;
	positionData[1] = m_uiYPosition;
	positionData[2] = m_uiXPosition + m_uiWidth;
	positionData[3] = m_uiYPosition;
	positionData[4] = m_uiXPosition + m_uiWidth;
	positionData[5] = m_uiYPosition + m_uiHeight;

	positionData[6] = m_uiXPosition;
	positionData[7] = m_uiYPosition;
	positionData[8] = m_uiXPosition;
	positionData[9] = m_uiYPosition + m_uiHeight;
	positionData[10] = m_uiXPosition + m_uiWidth;
	positionData[11] = m_uiYPosition + m_uiHeight;

	float uvData[12];
	uvData[0] = 0.f;
	uvData[1] = 1.f;
	uvData[2] = 1.f;
	uvData[3] = 1.f;
	uvData[4] = 1.f;
	uvData[5] = 0.f;

	uvData[6] = 0.f;
	uvData[7] = 1.f;
	uvData[8] = 0.f;
	uvData[9] = 0.f;
	uvData[10] = 1.f;
	uvData[11] = 0.f;

	// Send the data to the shader
	glGenVertexArrays(1, &m_uiVertexArrayId);
	glBindVertexArray(m_uiVertexArrayId);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &m_uiVertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_uiVertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, m_uiNumPoints * 2 * sizeof(float), &positionData, GL_STREAM_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glGenBuffers(1, &m_uiUVBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_uiUVBufferId);
	glBufferData(GL_ARRAY_BUFFER, m_uiNumPoints * 2 * sizeof(float), &uvData, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	return true;
}

void Image::setTexture(std::shared_ptr<Texture> texture)
{
	m_texture = texture;
}

void Image::setPosition(unsigned int uiXPos, unsigned int uiYPos)
{
	m_uiXPosition = uiXPos;
	m_uiYPosition = uiYPos;
}

void Image::setSize(unsigned int uiWidth, unsigned int uiHeight)
{
	if (uiWidth < 1)
	{
		uiWidth = 1;
	}
	if (uiHeight < 1)
	{
		uiHeight = 1;
	}
	m_uiWidth = uiWidth;
	m_uiHeight = uiHeight;

	//glBufferSubData();
}

void Image::render(Shader& shader)
{
	if (!m_texture)
	{
		return;
	}

	shader.postFloat(m_sSUXOffset, m_uiXPosition);
	shader.postFloat(m_sSUYOffset, m_uiYPosition);
	shader.postFloat(m_sSUViewWidth, 100);
	shader.postFloat(m_sSUViewHeight, 100);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture->getId());
	shader.postUnsignedInt(m_sSUTexture, 0);

	glBindVertexArray(m_uiVertexArrayId);
	glDrawArrays(GL_TRIANGLES, 0, m_uiNumPoints);
}
#include "texture.h"

Texture::Texture()
{
}

Texture::~Texture()
{
}

GLuint Texture::loadTexture(std::string texture)
{
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	m_textureData = SOIL_load_image(texture.c_str(), &m_width, &m_height, 0, SOIL_LOAD_RGBA);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_textureData);
	glDisable(GL_TEXTURE_2D);

	SOIL_free_image_data(m_textureData);
	return m_textureID;
}

void Texture::bind()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

const GLint Texture::getWidth() const
{
	return m_width;
}

const GLint Texture::getHeight() const
{
	return m_height;
}

const GLuint Texture::getTextureID() const
{
	return m_textureID;
}

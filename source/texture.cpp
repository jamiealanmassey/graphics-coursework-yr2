#include "texture.h"

Texture::Texture()
{
}

Texture::~Texture()
{
}

GLuint Texture::loadTexture(std::string texture)
{
	GLuint width, height;
	GLuint error = lodepng::decode(m_textureData, width, height, texture);

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &m_textureData[0]);
	glBindTexture(GL_TEXTURE_2D, 0);
	return m_textureID;
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
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

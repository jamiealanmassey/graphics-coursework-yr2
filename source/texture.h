#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <GL/freeglut.h>
#include <GL/GL.h>

#include <iostream>
#include <string>
#include <vector>
#include <SOIL.h>

class Texture
{
public:
	Texture();
	~Texture();

	GLuint loadTexture(std::string texture);
	void bind();
	void unbind();

	const GLint getWidth() const;
	const GLint getHeight() const;
	const GLuint getTextureID() const;
	
private:
	GLint	 m_width;
	GLint	 m_height;
	GLuint	 m_textureID;
	GLubyte* m_textureData;
};

#endif // _TEXTURE_H

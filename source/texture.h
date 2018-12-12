#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <iostream>
#include <string>
#include <vector>
#include <SOIL.h>

#include "ogl_include.h"

/**
 * \brief Describes a Texture
 * \details Stores and loads a texture via the 3rd party library SOIL (http://www.lonesock.net/soil.html)
 * \version 1.0
 * \author Jamie Massey
 * \date 17.11.2018
 */
class Texture
{
public:
	/** Texture Constructor **/
	Texture();

	/** Texture Destructor **/
	~Texture();

	/**
	 * Loads a Texture into memory via a path relative to directory where the application is
	 * currently running from. SOIL will load the texture into OpenGL and this will give us
	 * an ID to use.
	 *
	 * \param texture Path location of the texture relative to running location
	 * \returns OpenGL GLuint ID that identifies the texture in memory
	 */
	GLuint loadTexture(std::string texture);

	/** Bind texture for use by enabling GL_TEXTURE_2D and calling glBindTexture with the ID **/
	void bind();

	/** Unbinds the texture for use by calling glBindTexture with 0 and disabling GL_TEXTURE_2D **/
	void unbind();

	/** Gets the width of the loaded texture in pixels **/
	const GLint getWidth() const;

	/** Gets the height of the loaded texture in pixels **/
	const GLint getHeight() const;

	/** Gets the OpenGL ID of the loaded texture **/
	const GLuint getTextureID() const;
	
private:
	GLint	 m_width;		///< Width of the texture in pixels
	GLint	 m_height;		///< Height of the texture in pixels
	GLuint	 m_textureID;   ///< Generated OpenGL ID for the texture
	GLubyte* m_textureData; ///< Stored texture data
};

#endif // _TEXTURE_H

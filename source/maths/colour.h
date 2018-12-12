#ifndef _COLOUR_H
#define _COLOUR_H

#include "../ogl_include.h"

/**
 * \brief Specifies a Colour object
 * \details C++ implementation of the Colour.java class found in GraphicsLab
 * \version 1.0
 * \author Jamie Massey
 * \date 17.11.2018
 */
class Colour
{
public:
	Colour();

	/**
	 * Constructs a Colour object from its RGB components with a float in the range 0-1.

	 * \param red The Colour's red component
	 * \param green The Colour's green component
	 * \param blue The Colour's blue component
	 */
	Colour(GLfloat r, GLfloat g, GLfloat b);

	/**
	 * Constructs a Colour object from its RGB components as integers

	 * \param red The Colour's red component (int 0-255)
	 * \param green The Colour's green component (int 0-255)
	 * \param blue The Colour's blue component (int 0-255)
	 */
	Colour(GLint r, GLint g, GLint b);

	/** Colour Destructor **/
	~Colour();

	/** Calls to OpenGL to change the current colour to render **/
	void assign();

private:
	GLfloat m_channelR; ///< Red component of this colour
	GLfloat m_channelG; ///< Green component of this colour
	GLfloat m_channelB; ///< Blue component of this colour
};

static Colour COLOUR_RED(1.0f, 0.0f, 0.0f);
static Colour COLOUR_GREEN(0.0f, 1.0f, 0.0f);
static Colour COLOUR_BLUE(0.0f, 0.0f, 1.0f);

static Colour COLOUR_YELLOW(1.0f, 1.0f, 0.0f);
static Colour COLOUR_PINK(1.0f, 0.0f, 1.0f);
static Colour COLOUR_CYAN(0.0f, 1.0f, 1.0f);

static Colour COLOUR_BLACK(0.0f, 0.0f, 0.0f);
static Colour COLOUR_WHITE(1.0f, 1.0f, 1.0f);

static Colour COLOUR_ORANGE(238, 154, 0);

#endif // _COLOUR_H

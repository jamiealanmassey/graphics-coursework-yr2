#ifndef _COLOUR_H
#define _COLOUR_H

#include <GL/freeglut.h>
#include <GL/GL.h>

class Colour
{
public:
	Colour(GLfloat r, GLfloat g, GLfloat b);
	Colour(GLint r, GLint g, GLint b);
	~Colour();

	void drawColour();

private:
	GLfloat m_channelR;
	GLfloat m_channelG;
	GLfloat m_channelB;
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

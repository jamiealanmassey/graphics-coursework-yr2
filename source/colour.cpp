#include "colour.h"

Colour::Colour(GLfloat r, GLfloat g, GLfloat b)
{
	m_channelR = r;
	m_channelG = g;
	m_channelB = b;
}

Colour::Colour(GLint r, GLint g, GLint b)
{
	m_channelR = ((GLfloat)r) / 255.0f;
	m_channelG = ((GLfloat)g) / 255.0f;
	m_channelB = ((GLfloat)b) / 255.0f;
}

Colour::~Colour()
{
	// TODO
}

void Colour::drawColour()
{
	glColor3f(m_channelR, m_channelG, m_channelB);
}

#include "vertex.h"

Vertex::Vertex(GLfloat x, GLfloat y, GLfloat z)
{
	m_coordX = x;
	m_coordY = y;
	m_coordZ = z;
}

Vertex::~Vertex()
{
}

const GLfloat Vertex::getCoordX() const
{
	return m_coordX;
}

const GLfloat Vertex::getCoordY() const
{
	return m_coordY;
}

const GLfloat Vertex::getCoordZ() const
{
	return m_coordZ;
}

void Vertex::drawVertex()
{
	glVertex3f(m_coordX, m_coordY, m_coordZ);
}

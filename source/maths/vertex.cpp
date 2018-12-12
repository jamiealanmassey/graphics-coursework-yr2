#include "vertex.h"
#include "vector3.h"

Vertex::Vertex(GLfloat x, GLfloat y, GLfloat z)
{
	m_coordX = x;
	m_coordY = y;
	m_coordZ = z;
}

Vertex::~Vertex()
{
}

const GLfloat Vertex::getX() const
{
	return m_coordX;
}

const GLfloat Vertex::getY() const
{
	return m_coordY;
}

const GLfloat Vertex::getZ() const
{
	return m_coordZ;
}

Vector3 Vertex::vector3() const
{
	return Vector3(*this);
}

void Vertex::assign()
{
	glVertex3f(m_coordX, m_coordY, m_coordZ);
}

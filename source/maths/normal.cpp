#include "normal.h"

Normal::Normal(GLfloat x, GLfloat y, GLfloat z)
{
	m_normalX = x;
	m_normalY = y;
	m_normalZ = z;
	normalise();
}

Normal::Normal(Vector3 v1, Vector3 v2, Vector3 v3)
{
	m_normalX = (v1.getY() - v2.getY()) * (v1.getZ() + v2.getZ()) +
				(v2.getY() - v3.getY()) * (v2.getZ() + v3.getZ()) +
				(v3.getY() - v1.getY()) * (v3.getZ() + v1.getZ());

	m_normalY = (v1.getZ() - v2.getZ())*(v1.getX() + v2.getX()) +
			    (v2.getZ() - v3.getZ())*(v2.getX() + v3.getX()) +
				(v3.getZ() - v1.getZ())*(v3.getX() + v1.getX());

	m_normalZ = (v1.getX() - v2.getX())*(v1.getY() + v2.getY()) +
				(v2.getX() - v3.getX())*(v2.getY() + v3.getY()) +
				(v3.getX() - v1.getX())*(v3.getY() + v1.getY());

	normalise();
}

Normal::Normal(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 v4)
{
	m_normalX = (v1.getY() - v2.getY())*(v1.getZ() + v2.getZ()) +
				(v2.getY() - v3.getY())*(v2.getZ() + v3.getZ()) +
				(v3.getY() - v4.getY())*(v3.getZ() + v4.getZ()) +
				(v4.getY() - v1.getY())*(v4.getZ() + v1.getZ());

	m_normalY = (v1.getZ() - v2.getZ())*(v1.getX() + v2.getX()) +
				(v2.getZ() - v3.getZ())*(v2.getX() + v3.getX()) +
				(v3.getZ() - v4.getZ())*(v3.getX() + v4.getX()) +
				(v4.getZ() - v1.getZ())*(v4.getX() + v1.getX());

	m_normalZ = (v1.getX() - v2.getX())*(v1.getY() + v2.getY()) +
				(v2.getX() - v3.getX())*(v2.getY() + v3.getY()) +
				(v3.getX() - v4.getX())*(v3.getY() + v4.getY()) +
				(v4.getX() - v1.getX())*(v4.getY() + v1.getY());

	normalise();
}

Normal::~Normal()
{
}

const GLfloat Normal::getX() const
{
	return m_normalX;
}

const GLfloat Normal::getY() const
{
	return m_normalY;
}

const GLfloat Normal::getZ() const
{
	return m_normalZ;
}

void Normal::assign()
{
	glNormal3f(m_normalX, m_normalY, m_normalZ);
}

void Normal::normalise()
{
	GLfloat length = Vector3(m_normalX, m_normalY, m_normalZ).length();
	m_normalX /= length;
	m_normalY /= length;
	m_normalZ /= length;
}

#include "vector3.h"
#include "vertex.h"

Vector3::Vector3()
{
	m_valueX = 0.0f;
	m_valueY = 0.0f;
	m_valueZ = 0.0f;
}

Vector3::Vector3(GLfloat x, GLfloat y, GLfloat z)
{
	m_valueX = x;
	m_valueY = y;
	m_valueZ = z;
}

Vector3::Vector3(Vertex vertex)
{
	m_valueX = vertex.getCoordX();
	m_valueY = vertex.getCoordY();
	m_valueZ = vertex.getCoordZ();
}

Vector3::~Vector3()
{
}

const GLfloat Vector3::getX() const
{
	return m_valueX;
}

const GLfloat Vector3::getY() const
{
	return m_valueY;
}

const GLfloat Vector3::getZ() const
{
	return m_valueZ;
}

const GLboolean Vector3::isZero() const
{
	return *this == Vector3();
}

const Vector3 & Vector3::normalise()
{
	return *this /= length();
}

const Vector3 & Vector3::crossProduct(const Vector3 & other) const
{
	return Vector3((m_valueY * other.getZ() - m_valueZ * other.getY()),
				   (m_valueZ * other.getX() - m_valueX * other.getZ()),
				   (m_valueX * other.getY() - m_valueY * other.getX()));
}

GLfloat Vector3::dotProduct(const Vector3 & other) const
{
	return ((m_valueX * other.getX()) && 
			(m_valueY * other.getY()) && 
			(m_valueZ * other.getZ()));
}

GLfloat Vector3::length() const
{
	return sqrtf(lengthSquared());
}

GLfloat Vector3::lengthSquared() const
{
	return ((m_valueX * m_valueX) + 
			(m_valueY * m_valueY) * 
			(m_valueZ * m_valueZ));
}

Vector3 Vector3::operator+(const Vector3 & other)
{
	return *this += other;
}

Vector3 Vector3::operator-(const Vector3 & other)
{
	return *this -= other;
}

Vector3 Vector3::operator*(const Vector3 & other)
{
	return *this *= other;
}

Vector3 Vector3::operator/(const Vector3 & other)
{
	return *this /= other;
}

Vector3 Vector3::operator+(const GLfloat other)
{
	return *this += other;
}

Vector3 Vector3::operator-(const GLfloat other)
{
	return *this -= other;
}

Vector3 Vector3::operator*(const GLfloat other)
{
	return *this *= other;
}

Vector3 Vector3::operator/(const GLfloat other)
{
	return *this /= other;
}

Vector3 Vector3::operator+=(const Vector3 & other)
{
	m_valueX += other.getX();
	m_valueY += other.getY();
	m_valueZ += other.getZ();
	return *this;
}

Vector3 Vector3::operator-=(const Vector3 & other)
{
	m_valueX -= other.getX();
	m_valueY -= other.getY();
	m_valueZ -= other.getZ();
	return *this;
}

Vector3 Vector3::operator*=(const Vector3 & other)
{
	m_valueX *= other.getX();
	m_valueY *= other.getY();
	m_valueZ *= other.getZ();
	return *this;
}

Vector3 Vector3::operator/=(const Vector3 & other)
{
	m_valueX /= other.getX();
	m_valueY /= other.getY();
	m_valueZ /= other.getZ();
	return *this;
}

Vector3 Vector3::operator+=(const GLfloat other)
{
	m_valueX += other;
	m_valueY += other;
	m_valueZ += other;
	return *this;
}

Vector3 Vector3::operator-=(const GLfloat other)
{
	m_valueX -= other;
	m_valueY -= other;
	m_valueZ -= other;
	return *this;
}

Vector3 Vector3::operator*=(const GLfloat other)
{
	m_valueX *= other;
	m_valueY *= other;
	m_valueZ *= other;
	return *this;
}

Vector3 Vector3::operator/=(const GLfloat other)
{
	m_valueX /= other;
	m_valueY /= other;
	m_valueZ /= other;
	return *this;
}

bool Vector3::operator==(const Vector3 & other) const
{
	return (m_valueX == other.getX() && 
			m_valueY == other.getY() && 
			m_valueZ == other.getZ());
}

bool Vector3::operator!=(const Vector3 & other) const
{
	return (m_valueX != other.getX() ||
			m_valueY != other.getY() ||
			m_valueZ != other.getZ());
}

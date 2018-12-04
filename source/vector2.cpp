#include "vector2.h"

Vector2::Vector2()
{
	m_valueX = 0.0f;
	m_valueY = 0.0f;
}

Vector2::Vector2(GLfloat x, GLfloat y)
{
	m_valueX = x;
	m_valueY = y;
}

Vector2::~Vector2()
{
}

const GLfloat Vector2::getX() const
{
	return m_valueX;
}

const GLfloat Vector2::getY() const
{
	return m_valueY;
}

const GLboolean Vector2::isZero() const
{
	return (m_valueX == 0 && m_valueY == 0);
}

Vector2 Vector2::operator+(const Vector2 & other)
{
	return *this += other;
}

Vector2 Vector2::operator-(const Vector2 & other)
{
	return *this -= other;
}

Vector2 Vector2::operator*(const Vector2 & other)
{
	return *this *= other;
}

Vector2 Vector2::operator/(const Vector2 & other)
{
	return *this /= other;
}

Vector2 Vector2::operator+(const GLfloat other)
{
	return *this += other;
}

Vector2 Vector2::operator-(const GLfloat other)
{
	return *this -= other;
}

Vector2 Vector2::operator*(const GLfloat other)
{
	return *this *= other;
}

Vector2 Vector2::operator/(const GLfloat other)
{
	return *this /= other;
}

Vector2 Vector2::operator+=(const Vector2 & other)
{
	m_valueX += other.getX();
	m_valueY += other.getY();
	return *this;
}

Vector2 Vector2::operator-=(const Vector2 & other)
{
	m_valueX -= other.getX();
	m_valueY -= other.getY();
	return *this;
}

Vector2 Vector2::operator*=(const Vector2 & other)
{
	m_valueX *= other.getX();
	m_valueY *= other.getY();
	return *this;
}

Vector2 Vector2::operator/=(const Vector2 & other)
{
	m_valueX /= other.getX();
	m_valueY /= other.getY();
	return *this;
}

Vector2 Vector2::operator+=(const GLfloat other)
{
	m_valueX += other;
	m_valueY += other;
	return *this;
}

Vector2 Vector2::operator-=(const GLfloat other)
{
	m_valueX -= other;
	m_valueY -= other;
	return *this;
}

Vector2 Vector2::operator*=(const GLfloat other)
{
	m_valueX *= other;
	m_valueY *= other;
	return *this;
}

Vector2 Vector2::operator/=(const GLfloat other)
{
	m_valueX /= other;
	m_valueY /= other;
	return *this;
}

bool Vector2::operator==(const Vector2 & other) const
{
	return (m_valueX == other.getX() &&
			m_valueY == other.getY());
}

bool Vector2::operator!=(const Vector2 & other) const
{
	return (m_valueX != other.getX() ||
			m_valueY != other.getY());
}


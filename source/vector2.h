#ifndef _VECTOR2_H
#define _VECTOR2_H

#include "ogl_include.h"

class Vector2
{
public:
	Vector2();
	Vector2(GLfloat x, GLfloat y);
	~Vector2();

	const GLfloat getX() const;
	const GLfloat getY() const;
	const GLboolean isZero() const;

	Vector2 operator+ (const Vector2& other);
	Vector2 operator- (const Vector2& other);
	Vector2 operator* (const Vector2& other);
	Vector2 operator/ (const Vector2& other);

	Vector2 operator+ (const GLfloat other);
	Vector2 operator- (const GLfloat other);
	Vector2 operator* (const GLfloat other);
	Vector2 operator/ (const GLfloat other);

	Vector2 operator+= (const Vector2& other);
	Vector2 operator-= (const Vector2& other);
	Vector2 operator*= (const Vector2& other);
	Vector2 operator/= (const Vector2& other);

	Vector2 operator+= (const GLfloat other);
	Vector2 operator-= (const GLfloat other);
	Vector2 operator*= (const GLfloat other);
	Vector2 operator/= (const GLfloat other);

	bool operator== (const Vector2& other) const;
	bool operator!= (const Vector2& other) const;

private:
	GLfloat m_valueX;
	GLfloat m_valueY;
};

#endif // _VECTOR2_H

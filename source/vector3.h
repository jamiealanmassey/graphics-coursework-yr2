#ifndef _VECTOR3_H
#define _VECTOR3_H

#include <math.h>

#include "ogl_include.h"

class Vertex;
class Vector3
{
public:
	Vector3();
	Vector3(GLfloat x, GLfloat y, GLfloat z);
	Vector3(Vertex vertex);
	~Vector3();

	const GLfloat getX() const;
	const GLfloat getY() const;
	const GLfloat getZ() const;
	const GLboolean isZero() const;

	const Vector3& normalise();
	const Vector3& crossProduct(const Vector3& other) const;

	GLfloat dotProduct(const Vector3& other) const;
	GLfloat length() const;
	GLfloat lengthSquared() const;

	Vector3 operator+ (const Vector3& other);
	Vector3 operator- (const Vector3& other);
	Vector3 operator* (const Vector3& other);
	Vector3 operator/ (const Vector3& other);

	Vector3 operator+ (const GLfloat other);
	Vector3 operator- (const GLfloat other);
	Vector3 operator* (const GLfloat other);
	Vector3 operator/ (const GLfloat other);

	Vector3 operator+= (const Vector3& other);
	Vector3 operator-= (const Vector3& other);
	Vector3 operator*= (const Vector3& other);
	Vector3 operator/= (const Vector3& other);

	Vector3 operator+= (const GLfloat other);
	Vector3 operator-= (const GLfloat other);
	Vector3 operator*= (const GLfloat other);
	Vector3 operator/= (const GLfloat other);

	bool operator== (const Vector3& other) const;
	bool operator!= (const Vector3& other) const;

private:
	GLfloat m_valueX;
	GLfloat m_valueY;
	GLfloat m_valueZ;
};

#endif // _VECTOR3_H

#ifndef _VECTOR2_H
#define _VECTOR2_H

#include "../ogl_include.h"

/**
 * \brief Specifies a Vector direction in 2D space
 * \details C++ implementation of the Vector.java class found in GraphicsLab with extra functionality and operator overloading
 * \version 1.0
 * \author Jamie Massey
 * \date 29.11.2018
 */
class Vector2
{
public:
	/** Vector2 Constructor with (0, 0) **/
	Vector2();

	/**
	 * Defines a Vector2
	 *
	 * \param x Length along the X-Axis
	 * \param y Length along the Y-Axis
	 */
	Vector2(GLfloat x, GLfloat y);

	/** Vector2 Destructor **/
	~Vector2();

	/** \returns Length of this Vector along the X-Axis **/
	const GLfloat getX() const;

	/** \returns Length of this Vector along the Y-Axis **/
	const GLfloat getY() const;

	/** \returns 1 -> all components == 0. 0 -> otherwise **/
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
	GLfloat m_valueX; ///< X-Axis component for this Vector2
	GLfloat m_valueY; ///< Y-Axis component for this Vector2
};

#endif // _VECTOR2_H

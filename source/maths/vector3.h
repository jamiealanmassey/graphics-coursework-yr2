#ifndef _VECTOR3_H
#define _VECTOR3_H

#include <math.h>

#include "../ogl_include.h"

class Vertex;

/**
 * \brief Specifies a Vector direction in 3D space 
 * \details C++ implementation of the Vector.java class found in GraphicsLab with extra functionality and operator overloading
 * \version 1.0
 * \author Jamie Massey
 * \date 17.11.2018
 */
class Vector3
{
public:
	/** Vector3 Constructor with (0, 0, 0) **/
	Vector3();

	/**
	 * Defines a Vector3
	 *
	 * \param x Length along the X-Axis
	 * \param y Length along the Y-Axis
	 * \param y Length along the Z-Axis
	 */
	Vector3(GLfloat x, GLfloat y, GLfloat z);

	/**
	 * Defines a Vector3 from a Vertex
	 *
	 * \param vertex Vertex we want to extract from
	 */
	Vector3(Vertex vertex);

	/** Vector3 Destructor **/
	~Vector3();

	/** \returns Length of this Vector along the X-Axis **/
	const GLfloat getX() const;

	/** \returns Length of this Vector along the Y-Axis **/
	const GLfloat getY() const;

	/** \returns Length of this Vector along the Z-Axis **/
	const GLfloat getZ() const;

	/** \returns 1 -> all components == 0. 0 -> otherwise **/
	const GLboolean isZero() const;

	/**
	 * Normalise function that will compose the Vector3 to its unit length.
	 * Normalises this Vector3 itself and returns the result.
	 *
	 * \returns Returns itself with the normalised values
	 **/
	const Vector3 normalise();

	/**
	 * Produces a perpendicular vector to both the given vector and this
	 * vector itself.
	 *
	 * \param other Vector3 with which to produce cross product with
	 * \returns Calculated cross product from both vectors
	 */
	const Vector3 crossProduct(const Vector3& other);

	/**
	 * Calculates the dot product between this Vector and another
	 *
	 * \param other Vector with which to produce dot product with
	 * \returns Calculated dot product from both vectors
	 */
	GLfloat dotProduct(const Vector3& other) const;

	/**
	 * Find the length of this Vector
	 *
	 * \returns Single float representation of the Vector length
	 */
	GLfloat length() const;

	/**
	 * Find the squared length of this Vector
	 *
	 * \returns Single float representation of the Vector squared length
	 */
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
	GLfloat m_valueX; ///< X-Axis component for this Vector3
	GLfloat m_valueY; ///< Y-Axis component for this Vector3
	GLfloat m_valueZ; ///< Z-Axis component for this Vector3
};

#endif // _VECTOR3_H

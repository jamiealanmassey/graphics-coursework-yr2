#ifndef _NORMAL_H
#define _NORMAL_H

#include "vector3.h"

/**
 * \brief Normal class for defining normals
 * \details C++ implementation of the Normal.java class found in GraphicsLab
 * \version 1.0
 * \author Jamie Massey
 * \date 12.12.2018
 */
class Normal
{
public:
	/** 
	 * Normal Constructor
	 *
	 * \param x Normal's X component
	 * \param y Normal's Y component
	 * \param z Normal's Z component
	 */
	Normal(GLfloat x, GLfloat y, GLfloat z);

	/**
	 * Constructs a normal vector by taking 3 co-planar points (not co-linear):
	 * Based on computing two vectors in the plane, then taking the vector cross product
	 * between these to compute the normal; to get the sign right the vectors must be
	 * passed in anti-clockwise order.
	 */
	Normal(Vector3 v1, Vector3 v2, Vector3 v3);

	/**
	 * Constructs a normal vector by taking 4 co-planar points (not co-linear):
	 * Based on computing two vectors in the plane, then taking the vector cross product
	 * between these to compute the normal; to get the sign right the vectors must be
	 * passed in anti-clockwise order.
	 */
	Normal(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 v4);

	/** Normal Destructor **/
	~Normal();

	/** \returns X-Component of this Normal **/
	const GLfloat getX() const;

	/** \returns Y-Component of this Normal **/
	const GLfloat getY() const;

	/** \returns Z-Component of this Normal **/
	const GLfloat getZ() const;

	/**
	 * Calls to the glNormal3f method from OpenGL to apply this normal to the given set of
	 * vertices we want to affect
	 */
	void assign();

	/** Normalise this Normal with the help of Vector3 **/
	void normalise();

private:
	GLfloat m_normalX; ///< The X-Component of this Normal
	GLfloat m_normalY; ///< The Y-Component of this Normal
	GLfloat m_normalZ; ///< The Z-Component of this Normal
};

#endif // _NORMAL_H

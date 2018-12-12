#ifndef _VERTEX_H
#define _VERTEX_H

#include "../ogl_include.h"

class Vector3;

/**
 * \brief Specifies a Vertex in 3D space
 * \details C++ implementation of the Vertex.java class found in GraphicsLab
 * \version 1.0
 * \author Jamie Massey
 * \date 17.11.2018
 */
class Vertex
{
public:
	/**
	 * Vertex Constructor to be produced from x, y, z components
	 *
	 * \param x The Vertex's x component
	 * \param y The Vertex's Y component
	 * \param z The Vertex's Z component
	 */
	Vertex(GLfloat x, GLfloat y, GLfloat z);

	/** Vertex Destructor **/
	~Vertex();

	/** \returns The X value of the Vertex **/
	const GLfloat getX() const;

	/** \returns The Y value of the Vertex **/
	const GLfloat getY() const;

	/** \returns The Z value of the Vertex **/
	const GLfloat getZ() const;

	/** \returns This Vertex as a Vector3 converted from the coordinates **/
	Vector3 vector3() const;

	/** Calls to OpenGL for drawing this Vertex when flushed **/
	void assign();

private:
	GLfloat m_coordX; ///< Position of this Vertex on the X-Axis
	GLfloat m_coordY; ///< Position of this Vertex on the Y-Axis
	GLfloat m_coordZ; ///< Position of this Vertex on the Z-Axis
};

#endif // _VERTEX_H

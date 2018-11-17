#ifndef _VERTEX_H
#define _VERTEX_H

#include <GL/freeglut.h>
#include <GL/GL.h>

class Vector3;
class Vertex
{
public:
	Vertex(GLfloat x, GLfloat y, GLfloat z);
	~Vertex();

	const GLfloat getCoordX() const;
	const GLfloat getCoordY() const;
	const GLfloat getCoordZ() const;

	Vector3 vector3() const;

	void drawVertex();

private:
	GLfloat m_coordX;
	GLfloat m_coordY;
	GLfloat m_coordZ;
};

#endif // _VERTEX_H

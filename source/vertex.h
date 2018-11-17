#ifndef _VERTEX_H
#define _VERTEX_H

#include <GL/freeglut.h>
#include <GL/GL.h>

class Vertex
{
public:
	Vertex(GLfloat x, GLfloat y, GLfloat z);
	~Vertex();

	const GLfloat getCoordX() const;
	const GLfloat getCoordY() const;
	const GLfloat getCoordZ() const;

	/*Vector2 toVector2() const*/
	/*Vector3 toVector3() const*/

	void drawVertex();

private:
	GLfloat m_coordX;
	GLfloat m_coordY;
	GLfloat m_coordZ;
};

#endif // _VERTEX_H

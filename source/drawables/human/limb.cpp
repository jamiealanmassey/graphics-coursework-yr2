#include "limb.h"

Limb::Limb(GLfloat width, GLfloat height, GLfloat depth) :
	Drawable()
{
	m_limbWidth = width;
	m_limbHeight = height;
	m_limbDepth = depth;
}

Limb::~Limb()
{
}

void Limb::initialise()
{
	GLfloat halfWidth = m_limbWidth / 2.0f;
	GLfloat halfHeight = m_limbHeight / 2.0f;
	GLfloat halfDepth = m_limbDepth / 2.0f;

	m_vertices.push_back(Vertex( halfWidth,  halfHeight,  halfDepth)); // m_vertices[0]
	m_vertices.push_back(Vertex(-halfWidth,  halfHeight,  halfDepth)); // m_vertices[1]
	m_vertices.push_back(Vertex(-halfWidth, -halfHeight,  halfDepth)); // m_vertices[2]
	m_vertices.push_back(Vertex( halfWidth, -halfHeight,  halfDepth)); // m_vertices[3]
	m_vertices.push_back(Vertex(-halfWidth,  halfHeight, -halfDepth)); // m_vertices[4]
	m_vertices.push_back(Vertex( halfWidth,  halfHeight, -halfDepth)); // m_vertices[5]
	m_vertices.push_back(Vertex( halfWidth, -halfHeight, -halfDepth)); // m_vertices[6]
	m_vertices.push_back(Vertex(-halfWidth, -halfHeight, -halfDepth)); // m_vertices[7]
}

void Limb::draw()
{
	// Special transform
	glPushMatrix();
	glScalef(m_scale.getX(), m_scale.getY(), m_scale.getZ());
	glRotatef(m_rotation, m_rotationAxis.getX(), m_rotationAxis.getY(), m_rotationAxis.getZ());
	glTranslatef(m_translation.getX(), m_translation.getY(), m_translation.getZ());
	
	// Draw front face
	glBegin(GL_POLYGON);
	glTexCoord2f(m_uvs[4].getX(), m_uvs[4].getY());
	m_vertices[0].assign();
	glTexCoord2f(m_uvs[5].getX(), m_uvs[5].getY());
	m_vertices[1].assign();
	glTexCoord2f(m_uvs[6].getX(), m_uvs[6].getY());
	m_vertices[2].assign();
	glTexCoord2f(m_uvs[7].getX(), m_uvs[7].getY());
	m_vertices[3].assign();
	glEnd();

	// Draw back face
	glBegin(GL_POLYGON);
	glTexCoord2f(m_uvs[12].getX(), m_uvs[12].getY());
	m_vertices[4].assign();
	glTexCoord2f(m_uvs[13].getX(), m_uvs[13].getY());
	m_vertices[5].assign();
	glTexCoord2f(m_uvs[14].getX(), m_uvs[14].getY());
	m_vertices[6].assign();
	glTexCoord2f(m_uvs[15].getX(), m_uvs[15].getY());
	m_vertices[7].assign();
	glEnd();

	// Draw top face
	glBegin(GL_POLYGON);
	glTexCoord2f(m_uvs[16].getX(), m_uvs[16].getY());
	m_vertices[5].assign();
	glTexCoord2f(m_uvs[17].getX(), m_uvs[17].getY());
	m_vertices[4].assign();
	glTexCoord2f(m_uvs[18].getX(), m_uvs[18].getY());
	m_vertices[1].assign();
	glTexCoord2f(m_uvs[19].getX(), m_uvs[19].getY());
	m_vertices[0].assign();
	glEnd();

	// Draw bottom face
	glBegin(GL_POLYGON);
	glTexCoord2f(m_uvs[20].getX(), m_uvs[20].getY());
	m_vertices[3].assign();
	glTexCoord2f(m_uvs[21].getX(), m_uvs[21].getY());
	m_vertices[2].assign();
	glTexCoord2f(m_uvs[22].getX(), m_uvs[22].getY());
	m_vertices[7].assign();
	glTexCoord2f(m_uvs[23].getX(), m_uvs[23].getY());
	m_vertices[6].assign();
	glEnd();

	// Draw left side face
	glBegin(GL_POLYGON);
	glTexCoord2f(m_uvs[0].getX(), m_uvs[0].getY());
	m_vertices[1].assign();
	glTexCoord2f(m_uvs[1].getX(), m_uvs[1].getY());
	m_vertices[4].assign();
	glTexCoord2f(m_uvs[2].getX(), m_uvs[2].getY());
	m_vertices[7].assign();
	glTexCoord2f(m_uvs[3].getX(), m_uvs[3].getY());
	m_vertices[2].assign();
	glEnd();

	// Draw right side face
	glBegin(GL_POLYGON);
	glTexCoord2f(m_uvs[8].getX(), m_uvs[8].getY());
	m_vertices[5].assign();
	glTexCoord2f(m_uvs[9].getX(), m_uvs[9].getY());
	m_vertices[0].assign();
	glTexCoord2f(m_uvs[10].getX(), m_uvs[10].getY());
	m_vertices[3].assign();
	glTexCoord2f(m_uvs[11].getX(), m_uvs[11].getY());
	m_vertices[6].assign();
	glEnd();
	glPopMatrix();
}

void Limb::update()
{
}

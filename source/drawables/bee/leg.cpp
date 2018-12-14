#include "leg.h"

Leg::Leg()
{
	m_flipped = false;
}

Leg::~Leg()
{
}

void Leg::initialise()
{
	m_vertices.push_back(Vertex( 0.5f, 0.0f, -0.5f)); // m_vertices[0]
	m_vertices.push_back(Vertex(-0.5f, 0.0f, -0.5f)); // m_vertices[1]
	m_vertices.push_back(Vertex(-0.5f, 0.0f,  0.5f)); // m_vertices[2]
	m_vertices.push_back(Vertex( 0.5f, 0.0f,  0.5f)); // m_vertices[3]

	m_vertices.push_back(Vertex( 0.5f, -3.0f, -0.8f)); // m_vertices[4]
	m_vertices.push_back(Vertex(-0.5f, -3.0f, -0.8f)); // m_vertices[5]
	m_vertices.push_back(Vertex(-0.5f, -3.0f,  0.2f)); // m_vertices[6]
	m_vertices.push_back(Vertex( 0.5f, -3.0f,  0.2f)); // m_vertices[7]

	m_vertices.push_back(Vertex( 0.5f, -3.8f,  0.4f)); // m_vertices[4]
	m_vertices.push_back(Vertex(-0.5f, -3.8f,  0.4f)); // m_vertices[5]
	m_vertices.push_back(Vertex(-0.5f, -4.2f, -0.6f)); // m_vertices[6]
	m_vertices.push_back(Vertex( 0.5f, -4.2f, -0.6f)); // m_vertices[7]
}

void Leg::draw()
{
	glPushMatrix();
	glRotatef(90.0f * (m_flipped ? 1.0f : -1.0f), 0.0f, 1.0f, 0.0f); // Rotate correctly based on side
	glScalef(m_scale.getX(), m_scale.getY(), m_scale.getZ());
	glTranslatef(m_translation.getX(), m_translation.getY(), m_translation.getZ());

	// Leg Top
	glBegin(GL_POLYGON);
	Normal( m_vertices[0], 
			m_vertices[1], 
			m_vertices[2], 
			m_vertices[3] ).assign();

	glTexCoord2f(m_uvs[4].getX(), m_uvs[4].getY());
	m_vertices[0].assign();
	glTexCoord2f(m_uvs[5].getX(), m_uvs[5].getY());
	m_vertices[1].assign();
	glTexCoord2f(m_uvs[6].getX(), m_uvs[6].getY());
	m_vertices[2].assign();
	glTexCoord2f(m_uvs[7].getX(), m_uvs[7].getY());
	m_vertices[3].assign();
	glEnd();

	// Leg Big Left
	glBegin(GL_POLYGON);
	Normal( m_vertices[2],
			m_vertices[1],
			m_vertices[5],
			m_vertices[6] ).assign();

	glTexCoord2f(m_uvs[0].getX(), m_uvs[0].getY());
	m_vertices[2].assign();
	glTexCoord2f(m_uvs[1].getX(), m_uvs[1].getY());
	m_vertices[1].assign();
	glTexCoord2f(m_uvs[2].getX(), m_uvs[2].getY());
	m_vertices[5].assign();
	glTexCoord2f(m_uvs[3].getX(), m_uvs[3].getY());
	m_vertices[6].assign();
	glEnd();

	// Leg Big Back
	glBegin(GL_POLYGON);
	Normal( m_vertices[1],
			m_vertices[0],
			m_vertices[4],
			m_vertices[5] ).assign();

	glTexCoord2f(m_uvs[0].getX(), m_uvs[0].getY());
	m_vertices[1].assign();
	glTexCoord2f(m_uvs[1].getX(), m_uvs[1].getY());
	m_vertices[0].assign();
	glTexCoord2f(m_uvs[2].getX(), m_uvs[2].getY());
	m_vertices[4].assign();
	glTexCoord2f(m_uvs[3].getX(), m_uvs[3].getY());
	m_vertices[5].assign();
	glEnd();

	// Leg Big Right
	glBegin(GL_POLYGON);
	Normal( m_vertices[0],
			m_vertices[3],
			m_vertices[7],
			m_vertices[4] ).assign();

	glTexCoord2f(m_uvs[0].getX(), m_uvs[0].getY());
	m_vertices[0].assign();
	glTexCoord2f(m_uvs[1].getX(), m_uvs[1].getY());
	m_vertices[3].assign();
	glTexCoord2f(m_uvs[2].getX(), m_uvs[2].getY());
	m_vertices[7].assign();
	glTexCoord2f(m_uvs[3].getX(), m_uvs[3].getY());
	m_vertices[4].assign();
	glEnd();

	// Leg Big Front
	glBegin(GL_POLYGON);
	Normal( m_vertices[3],
			m_vertices[2],
			m_vertices[6],
			m_vertices[7] ).assign();

	glTexCoord2f(m_uvs[0].getX(), m_uvs[0].getY());
	m_vertices[3].assign();
	glTexCoord2f(m_uvs[1].getX(), m_uvs[1].getY());
	m_vertices[2].assign();
	glTexCoord2f(m_uvs[2].getX(), m_uvs[2].getY());
	m_vertices[6].assign();
	glTexCoord2f(m_uvs[3].getX(), m_uvs[3].getY());
	m_vertices[7].assign();
	glEnd();

	// Leg Small Left
	glBegin(GL_POLYGON);
	Normal( m_vertices[6],
			m_vertices[5],
			m_vertices[10],
			m_vertices[9] ).assign();

	glTexCoord2f(m_uvs[0].getX(), m_uvs[0].getY());
	m_vertices[6].assign();
	glTexCoord2f(m_uvs[1].getX(), m_uvs[1].getY());
	m_vertices[5].assign();
	glTexCoord2f(m_uvs[2].getX(), m_uvs[2].getY());
	m_vertices[10].assign();
	glTexCoord2f(m_uvs[3].getX(), m_uvs[3].getY());
	m_vertices[9].assign();
	glEnd();

	// Leg Small Back
	glBegin(GL_POLYGON);
	Normal( m_vertices[5],
			m_vertices[4],
			m_vertices[11],
			m_vertices[10] ).assign();

	glTexCoord2f(m_uvs[0].getX(), m_uvs[0].getY());
	m_vertices[5].assign();
	glTexCoord2f(m_uvs[1].getX(), m_uvs[1].getY());
	m_vertices[4].assign();
	glTexCoord2f(m_uvs[2].getX(), m_uvs[2].getY());
	m_vertices[11].assign();
	glTexCoord2f(m_uvs[3].getX(), m_uvs[3].getY());
	m_vertices[10].assign();
	glEnd();

	// Leg Small Right
	glBegin(GL_POLYGON);
	Normal( m_vertices[4],
			m_vertices[7],
			m_vertices[8],
			m_vertices[11] ).assign();

	glTexCoord2f(m_uvs[0].getX(), m_uvs[0].getY());
	m_vertices[4].assign();
	glTexCoord2f(m_uvs[1].getX(), m_uvs[1].getY());
	m_vertices[7].assign();
	glTexCoord2f(m_uvs[2].getX(), m_uvs[2].getY());
	m_vertices[8].assign();
	glTexCoord2f(m_uvs[3].getX(), m_uvs[3].getY());
	m_vertices[11].assign();
	glEnd();

	// Leg Small Front
	glBegin(GL_POLYGON);
	Normal( m_vertices[7],
			m_vertices[6],
			m_vertices[9],
			m_vertices[8] ).assign();

	glTexCoord2f(m_uvs[0].getX(), m_uvs[0].getY());
	m_vertices[7].assign();
	glTexCoord2f(m_uvs[1].getX(), m_uvs[1].getY());
	m_vertices[6].assign();
	glTexCoord2f(m_uvs[2].getX(), m_uvs[2].getY());
	m_vertices[9].assign();
	glTexCoord2f(m_uvs[3].getX(), m_uvs[3].getY());
	m_vertices[8].assign();
	glEnd();

	// Leg Bottom
	glBegin(GL_POLYGON);
	Normal( m_vertices[8],
			m_vertices[9],
			m_vertices[10],
			m_vertices[11] ).assign();

	glTexCoord2f(m_uvs[4].getX(), m_uvs[4].getY());
	m_vertices[8].assign();
	glTexCoord2f(m_uvs[5].getX(), m_uvs[5].getY());
	m_vertices[9].assign();
	glTexCoord2f(m_uvs[6].getX(), m_uvs[6].getY());
	m_vertices[10].assign();
	glTexCoord2f(m_uvs[7].getX(), m_uvs[7].getY());
	m_vertices[11].assign();
	glEnd();

	glPopMatrix();
}

void Leg::update()
{
}

void Leg::setFlipped(GLboolean isFlipped)
{
	m_flipped = isFlipped;
}

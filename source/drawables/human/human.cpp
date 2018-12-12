#include "human.h"

Human::Human()
{
}

Human::~Human()
{
}

void Human::initialise(Application * application)
{
	m_currentRot = 0.0f;

	m_vertices.push_back(Vertex( 0.5f,  0.75f,  0.25f)); // m_vertices[0]
	m_vertices.push_back(Vertex(-0.5f,  0.75f,  0.25f)); // m_vertices[1]
	m_vertices.push_back(Vertex(-0.5f, -0.75f,  0.25f)); // m_vertices[2]
	m_vertices.push_back(Vertex( 0.5f, -0.75f,  0.25f)); // m_vertices[3]
	m_vertices.push_back(Vertex(-0.5f,  0.75f, -0.25f)); // m_vertices[4]
	m_vertices.push_back(Vertex( 0.5f,  0.75f, -0.25f)); // m_vertices[5]
	m_vertices.push_back(Vertex( 0.5f, -0.75f, -0.25f)); // m_vertices[6]
	m_vertices.push_back(Vertex(-0.5f, -0.75f, -0.25f)); // m_vertices[7]
}

void Human::draw(Application * application)
{
	// Call down to Drawable::transform() to apply any pre-transformations on the object
	glPushMatrix();
	this->transform();
	
	// Draw front face
	glBegin(GL_POLYGON);
	m_vertices[0].assign();
	m_vertices[1].assign();
	m_vertices[2].assign();
	m_vertices[3].assign();
	glEnd();

	// Draw back face
	glBegin(GL_POLYGON);
	m_vertices[4].assign();
	m_vertices[5].assign();
	m_vertices[6].assign();
	m_vertices[7].assign();
	glEnd();

	// Draw top face
	glBegin(GL_POLYGON);
	m_vertices[5].assign();
	m_vertices[4].assign();
	m_vertices[1].assign();
	m_vertices[0].assign();
	glEnd();

	// Draw bottom face
	glBegin(GL_POLYGON);
	m_vertices[3].assign();
	m_vertices[2].assign();
	m_vertices[7].assign();
	m_vertices[6].assign();
	glEnd();

	// Draw left side face
	glBegin(GL_POLYGON);
	m_vertices[1].assign();
	m_vertices[4].assign();
	m_vertices[7].assign();
	m_vertices[2].assign();
	glEnd();

	// Draw right side face
	glBegin(GL_POLYGON);
	m_vertices[5].assign();
	m_vertices[0].assign();
	m_vertices[3].assign();
	m_vertices[6].assign();
	glEnd();

	glPopMatrix();
}

void Human::update(Application* application)
{
	if (application->getKeyStates()['c']) {
		m_currentRot += 100.0f * DELTA_TIME_SECONDS;
		if (m_currentRot >= 360.0f)
			m_currentRot = 0.0f;
	}
	else if (application->getKeyStates()['v']) {
		m_currentRot -= 100.0f * DELTA_TIME_SECONDS;
		if (m_currentRot <= 0.0f)
			m_currentRot = 360.0f;
	}

	setRotation(m_currentRot, Vector3(1.0f, 0.0f, 0.0f));
}


#include "bee.h"

Bee::Bee()
{
	m_bodyWidth = 0.5f;
	m_bodyHeight = 0.5f;
	m_bodyDepth = 0.8f;
}

Bee::~Bee()
{
}

void Bee::initialise()
{
	m_vertices.push_back(Vertex( m_bodyWidth,  m_bodyHeight, m_bodyDepth)); // m_vertices[0]
	m_vertices.push_back(Vertex(-m_bodyWidth,  m_bodyHeight, m_bodyDepth)); // m_vertices[1]
	m_vertices.push_back(Vertex(-m_bodyWidth, -m_bodyHeight, m_bodyDepth)); // m_vertices[2]
	m_vertices.push_back(Vertex( m_bodyWidth, -m_bodyHeight, m_bodyDepth)); // m_vertices[3]

	m_vertices.push_back(Vertex(-m_bodyWidth,  m_bodyHeight, -m_bodyDepth)); // m_vertices[4]
	m_vertices.push_back(Vertex( m_bodyWidth,  m_bodyHeight, -m_bodyDepth)); // m_vertices[5]
	m_vertices.push_back(Vertex( m_bodyWidth, -m_bodyHeight, -m_bodyDepth)); // m_vertices[6]
	m_vertices.push_back(Vertex(-m_bodyWidth, -m_bodyHeight, -m_bodyDepth)); // m_vertices[7]

	m_vertices.push_back(Vertex( 0.4f,  0.4f, m_bodyDepth + 0.4f)); // m_vertices[8]
	m_vertices.push_back(Vertex(-0.4f,  0.4f, m_bodyDepth + 0.4f)); // m_vertices[9]
	m_vertices.push_back(Vertex(-0.4f, -0.4f, m_bodyDepth + 0.4f)); // m_vertices[10]
	m_vertices.push_back(Vertex( 0.4f, -0.4f, m_bodyDepth + 0.4f)); // m_vertices[11]

	m_vertices.push_back(Vertex(-0.4f,  0.4f, m_bodyDepth)); // m_vertices[12]
	m_vertices.push_back(Vertex( 0.4f,  0.4f, m_bodyDepth)); // m_vertices[13]
	m_vertices.push_back(Vertex( 0.4f, -0.4f, m_bodyDepth)); // m_vertices[14]
	m_vertices.push_back(Vertex(-0.4f, -0.4f, m_bodyDepth)); // m_vertices[15]

	for (int i = 0; i < 6; i++)
	{
		m_legs[i] = std::make_unique<Leg>();
		m_legs[i]->initialise();
		m_legs[i]->setScale(0.2f);
	}
	
	m_legs[0]->setTranslation(Vector3( 0.0f, -1.8f, -1.4f));
	m_legs[1]->setTranslation(Vector3(-3.0f, -1.8f, -1.4f));
	m_legs[2]->setTranslation(Vector3( 3.0f, -1.8f, -1.4f));
	m_legs[3]->setTranslation(Vector3( 0.0f, -1.8f, -1.4f));
	m_legs[4]->setTranslation(Vector3(-3.0f, -1.8f, -1.4f));
	m_legs[5]->setTranslation(Vector3( 3.0f, -1.8f, -1.4f));

	m_legs[3]->setFlipped(true);
	m_legs[4]->setFlipped(true);
	m_legs[5]->setFlipped(true);
}

void Bee::draw()
{
	glPushMatrix();
	this->transform();
	this->drawBody();
	this->drawHead();
	
	for (int i = 0; i < 6; i++)
		m_legs[i]->draw();

	glPopMatrix();
}

void Bee::update()
{
}

void Bee::drawBody()
{
	// Body Face Left
	glBegin(GL_POLYGON);
	Normal( m_vertices[12], 
			m_vertices[1], 
			m_vertices[2], 
			m_vertices[15] ).assign();

	m_vertices[12].assign();
	m_vertices[1].assign();
	m_vertices[2].assign();
	m_vertices[15].assign();
	glEnd();

	// Body Face Top
	glBegin(GL_POLYGON);
	Normal( m_vertices[0], 
			m_vertices[1], 
			m_vertices[12], 
			m_vertices[13] ).assign();

	m_vertices[0].assign();
	m_vertices[1].assign();
	m_vertices[12].assign();
	m_vertices[13].assign();
	glEnd();

	// Body Face Right
	glBegin(GL_POLYGON);
	Normal( m_vertices[0], 
			m_vertices[13], 
			m_vertices[14], 
			m_vertices[3] ).assign();

	m_vertices[0].assign();
	m_vertices[13].assign();
	m_vertices[14].assign();
	m_vertices[3].assign();
	glEnd();

	// Body Face Bottom
	glBegin(GL_POLYGON);
	Normal( m_vertices[14], 
			m_vertices[15], 
			m_vertices[2], 
			m_vertices[3] ).assign();

	m_vertices[14].assign();
	m_vertices[15].assign();
	m_vertices[2].assign();
	m_vertices[3].assign();
	glEnd();

	// Body Back
	glBegin(GL_POLYGON);
	Normal( m_vertices[4], 
			m_vertices[5], 
			m_vertices[6], 
			m_vertices[7] ).assign();

	m_vertices[4].assign();
	m_vertices[5].assign();
	m_vertices[6].assign();
	m_vertices[7].assign();
	glEnd();

	// Body Main Left
	glBegin(GL_POLYGON);
	Normal( m_vertices[1], 
			m_vertices[4], 
			m_vertices[7], 
			m_vertices[2] ).assign();

	m_vertices[1].assign();
	m_vertices[4].assign();
	m_vertices[7].assign();
	m_vertices[2].assign();
	glEnd();

	// Body Main Top
	glBegin(GL_POLYGON);
	Normal( m_vertices[5],
			m_vertices[4],
			m_vertices[1],
			m_vertices[0] ).assign();

	m_vertices[5].assign();
	m_vertices[4].assign();
	m_vertices[1].assign();
	m_vertices[0].assign();
	glEnd();

	// Body Main Right
	glBegin(GL_POLYGON);
	Normal( m_vertices[5],
			m_vertices[0],
			m_vertices[3],
			m_vertices[6] ).assign();

	m_vertices[5].assign();
	m_vertices[0].assign();
	m_vertices[3].assign();
	m_vertices[6].assign();
	glEnd();

	// Body Main Bottom
	glBegin(GL_POLYGON);
	Normal( m_vertices[3],
			m_vertices[2],
			m_vertices[7],
			m_vertices[6] ).assign();

	m_vertices[3].assign();
	m_vertices[2].assign();
	m_vertices[7].assign();
	m_vertices[6].assign();
	glEnd();
}

void Bee::drawHead()
{
	// Face Front
	glBegin(GL_POLYGON);
	Normal( m_vertices[8],
			m_vertices[9],
			m_vertices[10],
			m_vertices[11] ).assign();

	m_vertices[8].assign();
	m_vertices[9].assign();
	m_vertices[10].assign();
	m_vertices[11].assign();
	glEnd();

	// Face Left
	glBegin(GL_POLYGON);
	Normal( m_vertices[9],
			m_vertices[12],
			m_vertices[15],
			m_vertices[10] ).assign();

	m_vertices[9].assign();
	m_vertices[12].assign();
	m_vertices[15].assign();
	m_vertices[10].assign();
	glEnd();

	// Face Top
	glBegin(GL_POLYGON);
	Normal( m_vertices[13],
			m_vertices[12],
			m_vertices[9],
			m_vertices[8] ).assign();

	m_vertices[13].assign();
	m_vertices[12].assign();
	m_vertices[9].assign();
	m_vertices[8].assign();
	glEnd();

	// Face Right
	glBegin(GL_POLYGON);
	Normal( m_vertices[13],
			m_vertices[8],
			m_vertices[11],
			m_vertices[14] ).assign();

	m_vertices[13].assign();
	m_vertices[8].assign();
	m_vertices[11].assign();
	m_vertices[14].assign();
	glEnd();

	// Face Bottom
	glBegin(GL_POLYGON);
	Normal( m_vertices[11],
			m_vertices[10],
			m_vertices[15],
			m_vertices[14] ).assign();

	m_vertices[11].assign();
	m_vertices[10].assign();
	m_vertices[15].assign();
	m_vertices[14].assign();
	glEnd();
}

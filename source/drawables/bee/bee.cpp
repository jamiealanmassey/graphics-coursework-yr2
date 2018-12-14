#include "bee.h"

Bee::Bee()
{
	m_bodyWidth = 0.5f;
	m_bodyHeight = 0.5f;
	m_bodyDepth = 0.8f;
	m_attacked = false;
}

Bee::~Bee()
{
}

void Bee::initialise()
{
	m_textures.emplace_back(std::make_unique<Texture>());
	m_textures[0]->loadTexture("../textures/bee.png");

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

	m_pathSpeed = 2.0f;
	m_pathNext = 0;
	m_path = new Vector3[4]{
		Vector3(-1.5f, 0.8f, -1.5f),
		Vector3(-1.5f, 0.8f,  1.5f),
		Vector3( 1.5f, 0.8f,  1.5f),
		Vector3( 1.5f, 0.8f, -1.5f)
	};

	setupLegUVs();
}

void Bee::draw()
{
	glPushMatrix();
	m_textures[0]->bind();
	setRotation(m_rotation, Vector3(0.0f, 1.0f, 0.0f));
	this->transform();
	this->drawBody();
	this->drawHead();
	
	for (int i = 0; i < 6; i++)
		m_legs[i]->draw();

	m_textures[0]->unbind();
	glPopMatrix();
}

void Bee::update()
{
	float distanceX = m_translation.getX() - m_path[m_pathNext].getX();
	float distanceZ = m_translation.getZ() - m_path[m_pathNext].getZ();

	float distanceYMax = m_translation.getY() - 2.0f;
	float distanceYMin = m_translation.getY() - 0.8f;

	if (std::fabsf(distanceX) > 0.2f)
		m_translation -= Vector3((distanceX < 0.0f ? -m_pathSpeed : m_pathSpeed) * DELTA_TIME_SECONDS, 0.0f, 0.0f);

	if (std::fabsf(distanceZ) > 0.2f)
		m_translation -= Vector3(0.0f, 0.0f, (distanceZ < 0.0f ? -m_pathSpeed : m_pathSpeed) * DELTA_TIME_SECONDS);

	distanceX = m_translation.getX() - m_path[m_pathNext].getX();
	distanceZ = m_translation.getZ() - m_path[m_pathNext].getZ();

	if (std::fabsf(distanceX) < 0.2f && std::fabsf(distanceZ) < 0.2f)
	{
		m_pathNext++;
		if (m_pathNext == 4)
			m_pathNext = 0;
	}

	if (m_attacked && std::fabs(distanceYMax) > 0.2f)
		m_translation += Vector3(0.0f, m_pathSpeed * DELTA_TIME_SECONDS, 0.0f);
	else if (!m_attacked && std::fabsf(distanceYMin) > 0.2f)
		m_translation -= Vector3(0.0f, m_pathSpeed * DELTA_TIME_SECONDS, 0.0f);

	if (m_pathNext == 0)
		m_rotation = 270.0f;
	else if (m_pathNext == 1)
		m_rotation = 0.0f;
	else if (m_pathNext == 2)
		m_rotation = 90.0f;
	else if (m_pathNext == 3)
		m_rotation = 180.0f;
}

const GLboolean Bee::isAttacked() const
{
	return m_attacked;
}

void Bee::setAttacked(GLboolean flag)
{
	m_attacked = flag;
}

void Bee::drawBody()
{
	// Body Face Left
	glBegin(GL_POLYGON);
	Normal( m_vertices[12], 
			m_vertices[1], 
			m_vertices[2], 
			m_vertices[15] ).assign();

	glTexCoord2f(28.0f / 80.0f, 2.0f / 80.0f);
	m_vertices[12].assign();
	glTexCoord2f(25.0f / 80.0f, 2.0f / 80.0f);
	m_vertices[1].assign();
	glTexCoord2f(25.0f / 80.0f, 29.0f / 80.0f);
	m_vertices[2].assign();
	glTexCoord2f(28.0f / 80.0f, 29.0f / 80.0f);
	m_vertices[15].assign();
	glEnd();

	// Body Face Top
	glBegin(GL_POLYGON);
	Normal( m_vertices[0], 
			m_vertices[1], 
			m_vertices[12], 
			m_vertices[13] ).assign();

	glTexCoord2f(28.0f / 80.0f, 2.0f / 80.0f);
	m_vertices[0].assign();
	glTexCoord2f(25.0f / 80.0f, 2.0f / 80.0f);
	m_vertices[1].assign();
	glTexCoord2f(25.0f / 80.0f, 29.0f / 80.0f);
	m_vertices[12].assign();
	glTexCoord2f(28.0f / 80.0f, 29.0f / 80.0f);
	m_vertices[13].assign();
	glEnd();

	// Body Face Right
	glBegin(GL_POLYGON);
	Normal( m_vertices[0], 
			m_vertices[13], 
			m_vertices[14], 
			m_vertices[3] ).assign();

	glTexCoord2f(28.0f / 80.0f, 2.0f / 80.0f);
	m_vertices[0].assign();
	glTexCoord2f(25.0f / 80.0f, 2.0f / 80.0f);
	m_vertices[13].assign();
	glTexCoord2f(25.0f / 80.0f, 29.0f / 80.0f);
	m_vertices[14].assign();
	glTexCoord2f(28.0f / 80.0f, 29.0f / 80.0f);
	m_vertices[3].assign();
	glEnd();

	// Body Face Bottom
	glBegin(GL_POLYGON);
	Normal( m_vertices[14], 
			m_vertices[15], 
			m_vertices[2], 
			m_vertices[3] ).assign();

	glTexCoord2f(28.0f / 80.0f, 2.0f / 80.0f);
	m_vertices[14].assign();
	glTexCoord2f(25.0f / 80.0f, 2.0f / 80.0f);
	m_vertices[15].assign();
	glTexCoord2f(25.0f / 80.0f, 29.0f / 80.0f);
	m_vertices[2].assign();
	glTexCoord2f(28.0f / 80.0f, 29.0f / 80.0f);
	m_vertices[3].assign();
	glEnd();

	// Body Back
	glBegin(GL_POLYGON);
	Normal( m_vertices[4], 
			m_vertices[5], 
			m_vertices[6], 
			m_vertices[7] ).assign();

	glTexCoord2f(45.0f / 80.0f, 31.0f / 80.0f);
	m_vertices[4].assign();
	glTexCoord2f(14.0f / 80.0f, 31.0f / 80.0f);
	m_vertices[5].assign();
	glTexCoord2f(14.0f / 80.0f, 62.0f / 80.0f);
	m_vertices[6].assign();
	glTexCoord2f(45.0f / 80.0f, 62.0f / 80.0f);
	m_vertices[7].assign();
	glEnd();

	// Body Main Left
	glBegin(GL_POLYGON);
	Normal( m_vertices[1], 
			m_vertices[4], 
			m_vertices[7], 
			m_vertices[2] ).assign();

	glTexCoord2f(70.0f / 80.0f, 2.0f / 80.0f);
	m_vertices[1].assign();
	glTexCoord2f(32.0f / 80.0f, 2.0f / 80.0f);
	m_vertices[4].assign();
	glTexCoord2f(32.0f / 80.0f, 29.0f / 80.0f);
	m_vertices[7].assign();
	glTexCoord2f(70.0f / 80.0f, 29.0f / 80.0f);
	m_vertices[2].assign();
	glEnd();

	// Body Main Top
	glBegin(GL_POLYGON);
	Normal( m_vertices[5],
			m_vertices[4],
			m_vertices[1],
			m_vertices[0] ).assign();

	
	glTexCoord2f(70.0f / 80.0f, 29.0f / 80.0f);
	m_vertices[5].assign();
	glTexCoord2f(70.0f / 80.0f, 2.0f / 80.0f);
	m_vertices[4].assign();
	glTexCoord2f(32.0f / 80.0f, 2.0f / 80.0f);
	m_vertices[1].assign();
	glTexCoord2f(32.0f / 80.0f, 29.0f / 80.0f);
	m_vertices[0].assign();
	glEnd();

	// Body Main Right
	glBegin(GL_POLYGON);
	Normal( m_vertices[5],
			m_vertices[0],
			m_vertices[3],
			m_vertices[6] ).assign();

	glTexCoord2f(70.0f / 80.0f, 2.0f / 80.0f);
	m_vertices[5].assign();
	glTexCoord2f(32.0f / 80.0f, 2.0f / 80.0f);
	m_vertices[0].assign();
	glTexCoord2f(32.0f / 80.0f, 29.0f / 80.0f);
	m_vertices[3].assign();
	glTexCoord2f(70.0f / 80.0f, 29.0f / 80.0f);
	m_vertices[6].assign();
	glEnd();

	// Body Main Bottom
	glBegin(GL_POLYGON);
	Normal( m_vertices[3],
			m_vertices[2],
			m_vertices[7],
			m_vertices[6] ).assign();

	glTexCoord2f(70.0f / 80.0f, 29.0f / 80.0f);
	m_vertices[3].assign();
	glTexCoord2f(70.0f / 80.0f, 2.0f / 80.0f);
	m_vertices[2].assign();
	glTexCoord2f(32.0f / 80.0f, 2.0f / 80.0f);
	m_vertices[7].assign();
	glTexCoord2f(32.0f / 80.0f, 29.0f / 80.0f);
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

	glTexCoord2f(29.0f / 80.0f, 2.0f / 80.0f);
	m_vertices[8].assign();
	glTexCoord2f(2.0f / 80.0f, 2.0f / 80.0f);
	m_vertices[9].assign();
	glTexCoord2f(2.0f / 80.0f, 29.0f / 80.0f);
	m_vertices[10].assign();
	glTexCoord2f(29.0f / 80.0f, 29.0f / 80.0f);
	m_vertices[11].assign();
	glEnd();

	// Face Left
	glBegin(GL_POLYGON);
	Normal( m_vertices[9],
			m_vertices[12],
			m_vertices[15],
			m_vertices[10] ).assign();

	glTexCoord2f(28.0f / 80.0f, 2.0f / 80.0f);
	m_vertices[9].assign();
	glTexCoord2f(25.0f / 80.0f, 2.0f / 80.0f);
	m_vertices[12].assign();
	glTexCoord2f(25.0f / 80.0f, 29.0f / 80.0f);
	m_vertices[15].assign();
	glTexCoord2f(28.0f / 80.0f, 29.0f / 80.0f);
	m_vertices[10].assign();
	glEnd();

	// Face Top
	glBegin(GL_POLYGON);
	Normal( m_vertices[13],
			m_vertices[12],
			m_vertices[9],
			m_vertices[8] ).assign();

	glTexCoord2f(28.0f / 80.0f, 2.0f / 80.0f);
	m_vertices[13].assign();
	glTexCoord2f(25.0f / 80.0f, 2.0f / 80.0f);
	m_vertices[12].assign();
	glTexCoord2f(25.0f / 80.0f, 29.0f / 80.0f);
	m_vertices[9].assign();
	glTexCoord2f(28.0f / 80.0f, 29.0f / 80.0f);
	m_vertices[8].assign();
	glEnd();

	// Face Right
	glBegin(GL_POLYGON);
	Normal( m_vertices[13],
			m_vertices[8],
			m_vertices[11],
			m_vertices[14] ).assign();

	glTexCoord2f(28.0f / 80.0f, 2.0f / 80.0f);
	m_vertices[13].assign();
	glTexCoord2f(25.0f / 80.0f, 2.0f / 80.0f);
	m_vertices[8].assign();
	glTexCoord2f(25.0f / 80.0f, 29.0f / 80.0f);
	m_vertices[11].assign();
	glTexCoord2f(28.0f / 80.0f, 29.0f / 80.0f);
	m_vertices[14].assign();
	glEnd();

	// Face Bottom
	glBegin(GL_POLYGON);
	Normal( m_vertices[11],
			m_vertices[10],
			m_vertices[15],
			m_vertices[14] ).assign();

	glTexCoord2f(28.0f / 80.0f, 2.0f / 80.0f);
	m_vertices[11].assign();
	glTexCoord2f(25.0f / 80.0f, 2.0f / 80.0f);
	m_vertices[10].assign();
	glTexCoord2f(25.0f / 80.0f, 29.0f / 80.0f);
	m_vertices[15].assign();
	glTexCoord2f(28.0f / 80.0f, 29.0f / 80.0f);
	m_vertices[14].assign();
	glEnd();
}

void Bee::setupLegUVs()
{
	std::vector<Vector2> uvs;

	uvs.push_back(Vector2(11.0f / 80.0f, 31.0f / 80.0f));
	uvs.push_back(Vector2(2.0f / 80.0f, 31.0f / 80.0f));
	uvs.push_back(Vector2(2.0f / 80.0f, 62.0f / 80.0f));
	uvs.push_back(Vector2(11.0f / 80.0f, 62.0f / 80.0f));

	uvs.push_back(Vector2(11.0f / 80.0f, 31.0f / 80.0f));
	uvs.push_back(Vector2(2.0f / 80.0f, 31.0f / 80.0f));
	uvs.push_back(Vector2(2.0f / 80.0f, 40.0f / 80.0f));
	uvs.push_back(Vector2(11.0f / 80.0f, 40.0f / 80.0f));

	for (int i = 0; i < 6; i++)
		m_legs[i]->setUVS(uvs);
}

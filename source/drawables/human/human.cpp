#include "human.h"

Human::Human()
{
}

Human::~Human()
{
}

void Human::initialise(Application* application)
{
	m_textures.emplace_back(std::make_unique<Texture>());
	m_textures[0].get()->loadTexture("../textures/steve-player.png");

	m_arms[0] = std::make_unique<Limb>(0.4f, 1.3f, 0.4f);
	m_arms[1] = std::make_unique<Limb>(0.4f, 1.3f, 0.4f);
	m_arms[0].get()->initialise(application);
	m_arms[1].get()->initialise(application);
	m_arms[0]->setTranslation(Vector3(-0.65f, 0.0f, 0.0f));
	m_arms[1]->setTranslation(Vector3( 0.65f, 0.0f, 0.0f));

	m_legs[0] = std::make_unique<Limb>(0.45f, 1.3f, 0.45f);
	m_legs[1] = std::make_unique<Limb>(0.45f, 1.3f, 0.45f);
	m_legs[0].get()->initialise(application);
	m_legs[1].get()->initialise(application);
	m_legs[0]->setTranslation(Vector3(-0.225f, -1.3f, 0.0f));
	m_legs[1]->setTranslation(Vector3( 0.225f, -1.3f, 0.0f));

	m_currentRot = 0.0f;

	m_vertices.push_back(Vertex( 0.45f,  0.65f,  0.2f)); // m_vertices[0]
	m_vertices.push_back(Vertex(-0.45f,  0.65f,  0.2f)); // m_vertices[1]
	m_vertices.push_back(Vertex(-0.45f, -0.65f,  0.2f)); // m_vertices[2]
	m_vertices.push_back(Vertex( 0.45f, -0.65f,  0.2f)); // m_vertices[3]
	m_vertices.push_back(Vertex(-0.45f,  0.65f, -0.2f)); // m_vertices[4]
	m_vertices.push_back(Vertex( 0.45f,  0.65f, -0.2f)); // m_vertices[5]
	m_vertices.push_back(Vertex( 0.45f, -0.65f, -0.2f)); // m_vertices[6]
	m_vertices.push_back(Vertex(-0.45f, -0.65f, -0.2f)); // m_vertices[7]

	m_vertices.push_back(Vertex( 0.45f,  0.45f,  0.45f)); // m_vertices[8]
	m_vertices.push_back(Vertex(-0.45f,  0.45f,  0.45f)); // m_vertices[9]
	m_vertices.push_back(Vertex(-0.45f, -0.45f,  0.45f)); // m_vertices[10]
	m_vertices.push_back(Vertex( 0.45f, -0.45f,  0.45f)); // m_vertices[11]
	m_vertices.push_back(Vertex(-0.45f,  0.45f, -0.45f)); // m_vertices[12]
	m_vertices.push_back(Vertex( 0.45f,  0.45f, -0.45f)); // m_vertices[13]
	m_vertices.push_back(Vertex( 0.45f, -0.45f, -0.45f)); // m_vertices[14]
	m_vertices.push_back(Vertex(-0.45f, -0.45f, -0.45f)); // m_vertices[15]

	setupArmUVs();
	setupLegUVs();
}

void Human::draw(Application* application)
{
	// Call down to Drawable::transform() to apply any pre-transformations on the object
	glPushMatrix();
	this->transform();
	m_textures[0]->bind();
	glColor3f(1.0f, 1.0f, 1.0f);
	m_arms[0].get()->draw(application);
	m_arms[1].get()->draw(application);
	m_legs[0].get()->draw(application);
	m_legs[1].get()->draw(application);
	this->drawTorso();
	glTranslatef(0.0f, 1.1f, 0.0f);
	this->drawHead();
	m_textures[0]->unbind();
	glPopMatrix();
}

void Human::update(Application* application)
{
	if (application->getKeyStates()[GLFW_KEY_UP]) 
	{
		m_currentRot += 100.0f * DELTA_TIME_SECONDS;
		if (m_currentRot >= 360.0f)
			m_currentRot = 0.0f;
	}
	else if (application->getKeyStates()[GLFW_KEY_DOWN]) 
	{
		m_currentRot -= 100.0f * DELTA_TIME_SECONDS;
		if (m_currentRot <= 0.0f)
			m_currentRot = 360.0f;
	}

	if (application->getKeyStates()[GLFW_KEY_D])
		setTranslation(getTranslation() + Vector3(4.0f * DELTA_TIME_SECONDS, 0.0f, 0.0f));
	else if (application->getKeyStates()[GLFW_KEY_A])
		setTranslation(getTranslation() + Vector3(-4.0f * DELTA_TIME_SECONDS, 0.0f, 0.0f));
	else if (application->getKeyStates()[GLFW_KEY_S])
		setTranslation(getTranslation() + Vector3(0.0f, 0.0f, 4.0f * DELTA_TIME_SECONDS));
	else if (application->getKeyStates()[GLFW_KEY_W])
		setTranslation(getTranslation() + Vector3(0.0f, 0.0f, -4.0f * DELTA_TIME_SECONDS));
	else if (application->getKeyStates()[GLFW_KEY_O])
		setTranslation(getTranslation() + Vector3(0.0f, 4.0f * DELTA_TIME_SECONDS, 0.0f));
	else if (application->getKeyStates()[GLFW_KEY_L])
		setTranslation(getTranslation() + Vector3(0.0f, -4.0f * DELTA_TIME_SECONDS, 0.0f));

	setRotation(m_currentRot, Vector3(0.0f, 1.0f, 0.0f));
}

void Human::drawTorso()
{
	// Draw front face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.4375f, 0.625f);
	m_vertices[0].assign();
	glTexCoord2f(0.3125f, 0.625f);
	m_vertices[1].assign();
	glTexCoord2f(0.3125f, 1.0f);
	m_vertices[2].assign();
	glTexCoord2f(0.4375f, 1.0f);
	m_vertices[3].assign();
	glEnd();

	// Draw back face
	glBegin(GL_POLYGON);
	glTexCoord2f(40.0f / 64.0f, 20.0f / 32.0f);
	m_vertices[4].assign();
	glTexCoord2f(32.0f / 64.0f, 20.0f / 32.0f);
	m_vertices[5].assign();
	glTexCoord2f(32.0f / 64.0f, 1.0f);
	m_vertices[6].assign();
	glTexCoord2f(40.0f / 64.0f, 1.0f);
	m_vertices[7].assign();
	glEnd();

	// Draw top face
	glBegin(GL_POLYGON);
	glTexCoord2f(28.0f / 64.0f, 0.5f);
	m_vertices[5].assign();
	glTexCoord2f(20.0f / 64.0f, 0.5f);
	m_vertices[4].assign();
	glTexCoord2f(20.0f / 64.0f, 20.0f / 32.0f);
	m_vertices[1].assign();
	glTexCoord2f(28.0f / 64.0f, 20.0f / 32.0f);
	m_vertices[0].assign();
	glEnd();

	// Draw bottom face
	glBegin(GL_POLYGON);
	glTexCoord2f(36.0f / 64.0f, 0.5f);
	m_vertices[3].assign();
	glTexCoord2f(28.0f / 64.0f, 0.5f);
	m_vertices[2].assign();
	glTexCoord2f(28.0f / 64.0f, 20.0f / 32.0f);
	m_vertices[7].assign();
	glTexCoord2f(36.0f / 64.0f, 20.0f / 32.0f);
	m_vertices[6].assign();
	glEnd();

	// Draw left side face
	glBegin(GL_POLYGON);
	glTexCoord2f(20.0f / 64.0f, 20.0f / 32.0f);
	m_vertices[1].assign();
	glTexCoord2f(0.25f, 20.0f / 32.0f);
	m_vertices[4].assign();
	glTexCoord2f(0.25f, 1.0f);
	m_vertices[7].assign();
	glTexCoord2f(20.0f / 64.0f, 1.0f);
	m_vertices[2].assign();
	glEnd();

	// Draw right side face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.5f, 20.0f / 32.0f);
	m_vertices[5].assign();
	glTexCoord2f(28.0f / 64.0f, 20.0f / 32.0f);
	m_vertices[0].assign();
	glTexCoord2f(28.0f / 64.0f, 1.0f);
	m_vertices[3].assign();
	glTexCoord2f(0.5f, 1.0f);
	m_vertices[6].assign();
	glEnd();
}

void Human::drawHead()
{
	// Draw front face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.25f, 0.25f);
	m_vertices[8].assign();
	glTexCoord2f(0.125f, 0.25f);
	m_vertices[9].assign();
	glTexCoord2f(0.125f, 0.5f);
	m_vertices[10].assign();
	glTexCoord2f(0.25f, 0.5f);
	m_vertices[11].assign();
	glEnd();

	// Draw back face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.5f, 0.25f);
	m_vertices[12].assign();
	glTexCoord2f(0.375f, 0.25f);
	m_vertices[13].assign();
	glTexCoord2f(0.375f, 0.5f);
	m_vertices[14].assign();
	glTexCoord2f(0.5f, 0.5f);
	m_vertices[15].assign();
	glEnd();

	// Draw left side face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.125f, 0.25f);
	m_vertices[9].assign();
	glTexCoord2f(0.0f, 0.25f);
	m_vertices[12].assign();
	glTexCoord2f(0.0f, 0.5f);
	m_vertices[15].assign();
	glTexCoord2f(0.125f, 0.5f);
	m_vertices[10].assign();
	glEnd();

	// Draw right side face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.375f, 0.25f);
	m_vertices[13].assign();
	glTexCoord2f(0.25f, 0.25f);
	m_vertices[8].assign();
	glTexCoord2f(0.25f, 0.5f);
	m_vertices[11].assign();
	glTexCoord2f(0.375f, 0.5f);
	m_vertices[14].assign();
	glEnd();

	// Draw bottom face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.375f, 0.0f);
	m_vertices[11].assign();
	glTexCoord2f(0.25f, 0.0f);
	m_vertices[10].assign();
	glTexCoord2f(0.25f, 0.25f);
	m_vertices[15].assign();
	glTexCoord2f(0.375f, 0.25f);
	m_vertices[14].assign();
	glEnd();

	// Draw top face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.25f, 0.0f);
	m_vertices[13].assign();
	glTexCoord2f(0.125f, 0.0f);
	m_vertices[12].assign();
	glTexCoord2f(0.125f, 0.25f);
	m_vertices[9].assign();
	glTexCoord2f(0.25f, 0.25f);
	m_vertices[8].assign();
	glEnd();
}

void Human::setupArmUVs()
{
	std::vector<Vector2> uvs;
	uvs.push_back(Vector2(44.0f / 64.0f, 20.0f / 32.0f)); // Left arm
	uvs.push_back(Vector2(40.0f / 64.0f, 20.0f / 32.0f));
	uvs.push_back(Vector2(40.0f / 64.0f, 1.0f));
	uvs.push_back(Vector2(44.0f / 64.0f, 1.0f));

	uvs.push_back(Vector2(48.0f / 64.0f, 20.0f / 32.0f)); // Front arm
	uvs.push_back(Vector2(44.0f / 64.0f, 20.0f / 32.0f));
	uvs.push_back(Vector2(44.0f / 64.0f, 1.0f));
	uvs.push_back(Vector2(48.0f / 64.0f, 1.0f));

	uvs.push_back(Vector2(52.0f / 64.0f, 20.0f / 32.0f)); // Right arm
	uvs.push_back(Vector2(48.0f / 64.0f, 20.0f / 32.0f));
	uvs.push_back(Vector2(48.0f / 64.0f, 1.0f));
	uvs.push_back(Vector2(52.0f / 64.0f, 1.0f));

	uvs.push_back(Vector2(56.0f / 64.0f, 20.0f / 32.0f)); // Back arm
	uvs.push_back(Vector2(52.0f / 64.0f, 20.0f / 32.0f));
	uvs.push_back(Vector2(52.0f / 64.0f, 1.0f));
	uvs.push_back(Vector2(56.0f / 64.0f, 1.0f));

	uvs.push_back(Vector2(48.0f / 64.0f, 0.5f)); // Top arm
	uvs.push_back(Vector2(44.0f / 64.0f, 0.5f));
	uvs.push_back(Vector2(44.0f / 64.0f, 20.0f / 32.0f));
	uvs.push_back(Vector2(48.0f / 64.0f, 20.0f / 32.0f));

	uvs.push_back(Vector2(52.0f / 64.0f, 0.5f)); // Bottom arm
	uvs.push_back(Vector2(48.0f / 64.0f, 0.5f));
	uvs.push_back(Vector2(48.0f / 64.0f, 20.0f / 32.0f));
	uvs.push_back(Vector2(52.0f / 64.0f, 20.0f / 32.0f));

	m_arms[0].get()->setUVS(uvs);
	m_arms[1].get()->setUVS(uvs);
}

void Human::setupLegUVs()
{
	std::vector<Vector2> uvs;
	uvs.push_back(Vector2(4.0f / 64.0f, 20.0f / 32.0f)); // Left leg
	uvs.push_back(Vector2(0.0f, 20.0f / 32.0f));
	uvs.push_back(Vector2(0.0f, 1.0f));
	uvs.push_back(Vector2(4.0f / 64.0f, 1.0f));

	uvs.push_back(Vector2(8.0f / 64.0f, 20.0f / 32.0f)); // Front leg
	uvs.push_back(Vector2(4.0f / 64.0f, 20.0f / 32.0f));
	uvs.push_back(Vector2(4.0f / 64.0f, 1.0f));
	uvs.push_back(Vector2(8.0f / 64.0f, 1.0f));

	uvs.push_back(Vector2(12.0f / 64.0f, 20.0f / 32.0f)); // Right leg
	uvs.push_back(Vector2(8.0f / 64.0f, 20.0f / 32.0f));
	uvs.push_back(Vector2(8.0f / 64.0f, 1.0f));
	uvs.push_back(Vector2(12.0f / 64.0f, 1.0f));

	uvs.push_back(Vector2(16.0f / 64.0f, 20.0f / 32.0f)); // Back leg
	uvs.push_back(Vector2(12.0f / 64.0f, 20.0f / 32.0f));
	uvs.push_back(Vector2(12.0f / 64.0f, 1.0f));
	uvs.push_back(Vector2(16.0f / 64.0f, 1.0f));

	uvs.push_back(Vector2(8.0f / 64.0f, 0.5f)); // Top leg
	uvs.push_back(Vector2(4.0f / 64.0f, 0.5f));
	uvs.push_back(Vector2(4.0f / 64.0f, 20.0f / 32.0f));
	uvs.push_back(Vector2(8.0f / 64.0f, 20.0f / 32.0f));

	uvs.push_back(Vector2(12.0f / 64.0f, 0.5f)); // Bottom leg
	uvs.push_back(Vector2(8.0f / 64.0f, 0.5f));
	uvs.push_back(Vector2(8.0f / 64.0f, 20.0f / 32.0f));
	uvs.push_back(Vector2(12.0f / 64.0f, 20.0f / 32.0f));

	m_legs[0].get()->setUVS(uvs);
	m_legs[1].get()->setUVS(uvs);
}


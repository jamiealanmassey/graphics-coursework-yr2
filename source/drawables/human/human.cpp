#include "human.h"

Human::Human()
{
	m_state = eHumanState::IDLE;
	m_stateLast = eHumanState::IDLE;
	m_currentRot = 0.0f;
	m_armSwayRot = 0.0f;
	m_armSwayRotMax = 10.0f;
	m_armSwaySpeed = 10.0f;
	m_runningRot = 0.0f;
	m_runningRotMax = 15.0f;
	m_runningSpeed = 80.0f;
	m_pathSpeed = 3.5f;
	m_armSwayDir = false;
	m_runningDir = false;
	m_offsetDir = true;
	m_stoppedPress = false;
	m_offset = Vector3();
	m_offsetLimit = Vector3();
}

Human::~Human()
{
}

void Human::initialise()
{
	m_humanAmbient  = new GLfloat[4]{ 0.7f, 0.7f, 0.7f, 1.0f };
	m_humanDiffuse  = new GLfloat[4]{ 0.6f, 0.6f, 0.6f, 1.0f };
	m_humanSpecular = new GLfloat[4]{ 0.1f, 0.1f, 0.1f, 1.0f };

	m_textures.emplace_back(std::make_unique<Texture>());
	m_textures[0].get()->loadTexture("../textures/steve-player.png");

	m_armPosition = Vector3(0.65, 0.0f, 0.0f);
	m_arms[0] = std::make_unique<Limb>(0.4f, 1.3f, 0.4f);
	m_arms[1] = std::make_unique<Limb>(0.4f, 1.3f, 0.4f);
	m_arms[0].get()->initialise();
	m_arms[1].get()->initialise();
	m_arms[0]->setTranslation(Vector3(-m_armPosition.getX(), m_armPosition.getY(), m_armPosition.getZ()));
	m_arms[1]->setTranslation(Vector3( m_armPosition.getY(), m_armPosition.getY(), m_armPosition.getZ()));

	m_legs[0] = std::make_unique<Limb>(0.45f, 1.3f, 0.45f);
	m_legs[1] = std::make_unique<Limb>(0.45f, 1.3f, 0.45f);
	m_legs[0].get()->initialise();
	m_legs[1].get()->initialise();
	m_legs[0]->setTranslation(Vector3(-0.225f, -1.3f, 0.0f));
	m_legs[1]->setTranslation(Vector3( 0.225f, -1.3f, 0.0f));

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
	
	m_pathNext = 0;
	m_path = new Vector3[4] {
		Vector3( 5.0f, 3.5f,  5.0f),
		Vector3( 5.0f, 3.5f, 12.0f),
		Vector3(12.0f, 3.5f, 12.0f),
		Vector3(12.0f, 3.5f,  5.0f)
	};

	m_bee.initialise();
	m_bee.setScale(0.4f);
	m_bee.setTranslation(Vector3(-1.0f, 0.8f, -1.5f));

	setupArmUVs();
	setupLegUVs();
	setState(eHumanState::RUNNING);
}

void Human::draw()
{
	// Call down to Drawable::transform() to apply any pre-transformations on the object
	glPushMatrix();
	this->transform();

	glMaterialfv(GL_FRONT, GL_AMBIENT, m_humanAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_humanDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_humanSpecular);

	m_textures[0]->bind();
	glColor3f(1.0f, 1.0f, 1.0f);
	m_arms[0].get()->draw();
	m_arms[1].get()->draw();
	m_legs[0].get()->draw();
	m_legs[1].get()->draw();
	this->drawTorso();
	glTranslatef(0.0f, 1.1f, 0.0f);
	this->drawHead();
	m_textures[0]->unbind();
	m_bee.draw();
	glPopMatrix();
}

void Human::update()
{
	Application& application = Application::instance();
	if (!m_bee.isAttacked() && application.getKeyStates()[GLFW_KEY_N])
		m_bee.setAttacked(true);
	else if (m_bee.isAttacked() && !application.getKeyStates()[GLFW_KEY_N])
		m_bee.setAttacked(false);
	

	application.setCameraTarget(getTranslation());
	updatePath();
	updateAnimation();
	
	m_bee.update();
}

void Human::setState(eHumanState state)
{
	if (m_state == eHumanState::IDLE || m_state == eHumanState::RUNNING)
	{
		m_armSwayRot = 0.0f;
		m_arms[0]->setRotation(0.0f, Vector3(1.0f, 0.0f, 0.0f));
		m_arms[1]->setRotation(0.0f, Vector3(1.0f, 0.0f, 0.0f));
	}
	
	if (m_state == eHumanState::RUNNING)
	{
		m_runningRot = 0.0f;
		m_legs[0]->setRotation(0.0f, Vector3(1.0f, 0.0f, 0.0f));
		m_legs[1]->setRotation(0.0f, Vector3(1.0f, 0.0f, 0.0f));
	}

	m_stateLast = m_state;
	m_state = state;
}

void Human::updateAnimation()
{
	GLboolean idle = m_state == eHumanState::IDLE;
	GLboolean running = m_state == eHumanState::RUNNING;

	if (idle || running)
	{
		if (m_bee.isAttacked())
		{
			if (m_armSwayDir)
				m_armSwayRot += m_runningSpeed * DELTA_TIME_SECONDS;
			else
				m_armSwayRot -= m_runningSpeed * DELTA_TIME_SECONDS;

			if (m_armSwayRot >= m_armSwayRotMax || m_armSwayRot <= -m_armSwayRotMax)
				m_armSwayDir = !m_armSwayDir;

			m_arms[0]->setRotation(-m_armSwayRot + 180.0f, Vector3(1.0f, 0.0f, 0.0f));
			m_arms[1]->setRotation(m_armSwayRot + 180.0f, Vector3(1.0f, 0.0f, 0.0f));
			m_arms[0]->setTranslation(Vector3(-m_armPosition.getX(), m_armPosition.getY() - 1.0f, m_armPosition.getZ()));
			m_arms[1]->setTranslation(Vector3( m_armPosition.getX(), m_armPosition.getY() - 1.0f, m_armPosition.getZ()));
		}
		else
		{
			if (m_armSwayDir)
				m_armSwayRot += ((idle * m_armSwaySpeed) + (running * m_runningSpeed)) * DELTA_TIME_SECONDS;
			else
				m_armSwayRot -= ((idle * m_armSwaySpeed) + (running * m_runningSpeed)) * DELTA_TIME_SECONDS;

			if (m_armSwayRot >= m_armSwayRotMax || m_armSwayRot <= -m_armSwayRotMax)
				m_armSwayDir = !m_armSwayDir;

			m_arms[0]->setRotation(-m_armSwayRot, Vector3(1.0f, 0.0f, 0.0f));
			m_arms[1]->setRotation(m_armSwayRot, Vector3(1.0f, 0.0f, 0.0f));
			m_arms[0]->setTranslation(Vector3(-m_armPosition.getX(), m_armPosition.getY(), m_armPosition.getZ()));
			m_arms[1]->setTranslation(Vector3(m_armPosition.getX(), m_armPosition.getY(), m_armPosition.getZ()));
		}
	}
	
	if (running)
	{
		if (m_runningDir)
			m_runningRot += m_runningSpeed * DELTA_TIME_SECONDS;
		else
			m_runningRot -= m_runningSpeed * DELTA_TIME_SECONDS;

		if (m_runningRot >= m_runningRotMax || m_runningRot <= -m_runningRotMax)
			m_runningDir = !m_runningDir;

		m_legs[0]->setRotation(-m_runningRot, Vector3(1.0f, 0.0f, 0.0f));
		m_legs[1]->setRotation( m_runningRot, Vector3(1.0f, 0.0f, 0.0f));
	}
}

void Human::updatePath()
{
	float distanceX = m_translation.getX() - m_path[m_pathNext].getX();
	float distanceZ = m_translation.getZ() - m_path[m_pathNext].getZ();

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

	if (m_pathNext == 0)
		m_rotation = 270.0f;
	else if (m_pathNext == 1)
		m_rotation = 0.0f;
	else if (m_pathNext == 2)
		m_rotation = 90.0f;
	else if (m_pathNext == 3)
		m_rotation = 180.0f;
}

void Human::jump()
{
	m_offsetInitial = m_translation;
	m_offsetLimit = m_translation + Vector3(0.0f, 0.5f, 0.0f);
	m_offset += Vector3(0.0f, 0.1f * DELTA_TIME_SECONDS, 0.0f);
	m_arms[0]->setRotation(90.0f, Vector3(1.0f, 0.0f, 0.0f));
	m_arms[1]->setRotation(90.0f, Vector3(1.0f, 0.0f, 0.0f));
	m_legs[0]->setRotation(-20.0f, Vector3(1.0f, 0.0f, 0.0f));
	m_legs[1]->setRotation( 20.0f, Vector3(1.0f, 0.0f, 0.0f));
	setTranslation(m_offsetInitial + m_offset);
	setState(eHumanState::JUMPING);
}

void Human::drawTorso()
{
	// Draw front face
	glBegin(GL_POLYGON);
	Normal( m_vertices[0], 
			m_vertices[1], 
			m_vertices[2], 
			m_vertices[3] ).assign();

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
	Normal( m_vertices[4], 
			m_vertices[5], 
			m_vertices[6], 
			m_vertices[7] ).assign();

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
	Normal( m_vertices[5], 
			m_vertices[4], 
			m_vertices[1], 
			m_vertices[0] ).assign();

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
	Normal( m_vertices[3], 
			m_vertices[2], 
			m_vertices[7], 
			m_vertices[6] ).assign();

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
	Normal( m_vertices[1], 
			m_vertices[4], 
			m_vertices[7], 
			m_vertices[2] ).assign();

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
	Normal( m_vertices[5], 
			m_vertices[0], 
			m_vertices[3], 
			m_vertices[6] ).assign();

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
	Normal( m_vertices[8], 
			m_vertices[9], 
			m_vertices[10], 
			m_vertices[11] ).assign();

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
	Normal( m_vertices[12], 
			m_vertices[13], 
			m_vertices[14], 
			m_vertices[15] ).assign();

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
	Normal( m_vertices[9], 
			m_vertices[12], 
			m_vertices[15], 
			m_vertices[10] ).assign();

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
	Normal( m_vertices[13], 
			m_vertices[8], 
			m_vertices[11], 
			m_vertices[14] ).assign();

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
	Normal( m_vertices[11], 
			m_vertices[10], 
			m_vertices[15], 
			m_vertices[14] ).assign();

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
	Normal( m_vertices[13], 
			m_vertices[12], 
			m_vertices[9], 
			m_vertices[8] ).assign();

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

	// Left arm
	uvs.push_back(Vector2(44.0f / 64.0f, 20.0f / 32.0f)); 
	uvs.push_back(Vector2(40.0f / 64.0f, 20.0f / 32.0f));
	uvs.push_back(Vector2(40.0f / 64.0f, 1.0f));
	uvs.push_back(Vector2(44.0f / 64.0f, 1.0f));

	// Front arm
	uvs.push_back(Vector2(48.0f / 64.0f, 20.0f / 32.0f)); 
	uvs.push_back(Vector2(44.0f / 64.0f, 20.0f / 32.0f));
	uvs.push_back(Vector2(44.0f / 64.0f, 1.0f));
	uvs.push_back(Vector2(48.0f / 64.0f, 1.0f));

	// Right arm
	uvs.push_back(Vector2(52.0f / 64.0f, 20.0f / 32.0f)); 
	uvs.push_back(Vector2(48.0f / 64.0f, 20.0f / 32.0f));
	uvs.push_back(Vector2(48.0f / 64.0f, 1.0f));
	uvs.push_back(Vector2(52.0f / 64.0f, 1.0f));

	// Back arm
	uvs.push_back(Vector2(56.0f / 64.0f, 20.0f / 32.0f)); 
	uvs.push_back(Vector2(52.0f / 64.0f, 20.0f / 32.0f));
	uvs.push_back(Vector2(52.0f / 64.0f, 1.0f));
	uvs.push_back(Vector2(56.0f / 64.0f, 1.0f));

	// Top arm
	uvs.push_back(Vector2(48.0f / 64.0f, 0.5f)); 
	uvs.push_back(Vector2(44.0f / 64.0f, 0.5f));
	uvs.push_back(Vector2(44.0f / 64.0f, 20.0f / 32.0f));
	uvs.push_back(Vector2(48.0f / 64.0f, 20.0f / 32.0f));

	// Bottom arm
	uvs.push_back(Vector2(52.0f / 64.0f, 0.5f)); 
	uvs.push_back(Vector2(48.0f / 64.0f, 0.5f));
	uvs.push_back(Vector2(48.0f / 64.0f, 20.0f / 32.0f));
	uvs.push_back(Vector2(52.0f / 64.0f, 20.0f / 32.0f));

	// Pass UVs
	m_arms[0].get()->setUVS(uvs);
	m_arms[1].get()->setUVS(uvs);
}

void Human::setupLegUVs()
{
	std::vector<Vector2> uvs;

	// Left leg
	uvs.push_back(Vector2(4.0f / 64.0f, 20.0f / 32.0f)); 
	uvs.push_back(Vector2(0.0f, 20.0f / 32.0f));
	uvs.push_back(Vector2(0.0f, 1.0f));
	uvs.push_back(Vector2(4.0f / 64.0f, 1.0f));

	// Front leg
	uvs.push_back(Vector2(8.0f / 64.0f, 20.0f / 32.0f)); 
	uvs.push_back(Vector2(4.0f / 64.0f, 20.0f / 32.0f));
	uvs.push_back(Vector2(4.0f / 64.0f, 1.0f));
	uvs.push_back(Vector2(8.0f / 64.0f, 1.0f));

	// Right leg
	uvs.push_back(Vector2(12.0f / 64.0f, 20.0f / 32.0f)); 
	uvs.push_back(Vector2(8.0f / 64.0f, 20.0f / 32.0f));
	uvs.push_back(Vector2(8.0f / 64.0f, 1.0f));
	uvs.push_back(Vector2(12.0f / 64.0f, 1.0f));

	// Back leg
	uvs.push_back(Vector2(16.0f / 64.0f, 20.0f / 32.0f)); 
	uvs.push_back(Vector2(12.0f / 64.0f, 20.0f / 32.0f));
	uvs.push_back(Vector2(12.0f / 64.0f, 1.0f));
	uvs.push_back(Vector2(16.0f / 64.0f, 1.0f));

	// Top leg
	uvs.push_back(Vector2(8.0f / 64.0f, 0.5f)); 
	uvs.push_back(Vector2(4.0f / 64.0f, 0.5f));
	uvs.push_back(Vector2(4.0f / 64.0f, 20.0f / 32.0f));
	uvs.push_back(Vector2(8.0f / 64.0f, 20.0f / 32.0f));

	// Bottom leg
	uvs.push_back(Vector2(12.0f / 64.0f, 0.5f)); 
	uvs.push_back(Vector2(8.0f / 64.0f, 0.5f));
	uvs.push_back(Vector2(8.0f / 64.0f, 20.0f / 32.0f));
	uvs.push_back(Vector2(12.0f / 64.0f, 20.0f / 32.0f));

	// Pass UVs
	m_legs[0].get()->setUVS(uvs);
	m_legs[1].get()->setUVS(uvs);
}

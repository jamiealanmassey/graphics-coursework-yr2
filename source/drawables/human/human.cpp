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
	m_armSwayDir = false;
	m_runningDir = false;
	m_offsetDir = true;
	m_offset = Vector3();
	m_offsetLimit = Vector3();
}

Human::~Human()
{
}

void Human::initialise()
{
	m_humanAmbient  = new GLfloat[4]{ 0.3f, 0.3f, 0.3f, 1.0f };
	m_humanDiffuse  = new GLfloat[4]{ 0.6f, 0.6f, 0.6f, 1.0f };
	m_humanSpecular = new GLfloat[4]{ 0.1f, 0.1f, 0.1f, 1.0f };

	m_textures.emplace_back(std::make_unique<Texture>());
	m_textures[0].get()->loadTexture("../textures/steve-player.png");

	m_arms[0] = std::make_unique<Limb>(0.4f, 1.3f, 0.4f);
	m_arms[1] = std::make_unique<Limb>(0.4f, 1.3f, 0.4f);
	m_arms[0].get()->initialise();
	m_arms[1].get()->initialise();
	m_arms[0]->setTranslation(Vector3(-0.65f, 0.0f, 0.0f));
	m_arms[1]->setTranslation(Vector3( 0.65f, 0.0f, 0.0f));

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

	m_bee.initialise();

	setupArmUVs();
	setupLegUVs();
}

void Human::draw()
{
	// Call down to Drawable::transform() to apply any pre-transformations on the object
	glPushMatrix();
	this->transform();

	glMaterialfv(GL_FRONT, GL_AMBIENT, m_humanAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_humanDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_humanSpecular);

	/*m_textures[0]->bind();
	glColor3f(1.0f, 1.0f, 1.0f);
	m_arms[0].get()->draw(application);
	m_arms[1].get()->draw(application);
	m_legs[0].get()->draw(application);
	m_legs[1].get()->draw(application);
	this->drawTorso();
	glTranslatef(0.0f, 1.1f, 0.0f);
	this->drawHead();
	m_textures[0]->unbind();*/
	m_bee.draw();
	glPopMatrix();
}

void Human::update()
{
	Application& application = Application::instance();

	if (application.getKeyStates()[GLFW_KEY_UP]) 
	{
		m_currentRot += 100.0f * DELTA_TIME_SECONDS;
		if (m_currentRot >= 360.0f)
			m_currentRot = 0.0f;
	}
	else if (application.getKeyStates()[GLFW_KEY_DOWN]) 
	{
		m_currentRot -= 100.0f * DELTA_TIME_SECONDS;
		if (m_currentRot <= 0.0f)
			m_currentRot = 360.0f;
	}

	Vector3 acceleration;
	if (application.getKeyStates()[GLFW_KEY_D])
		acceleration = Vector3(4.0f * DELTA_TIME_SECONDS, 0.0f, 0.0f);
	else if (application.getKeyStates()[GLFW_KEY_A])
		acceleration = Vector3(-4.0f * DELTA_TIME_SECONDS, 0.0f, 0.0f);
	
	if (application.getKeyStates()[GLFW_KEY_S])
		acceleration = Vector3(0.0f, 0.0f, 4.0f * DELTA_TIME_SECONDS);
	else if (application.getKeyStates()[GLFW_KEY_W])
		acceleration = Vector3(0.0f, 0.0f, -4.0f * DELTA_TIME_SECONDS);
	
	if (application.getKeyStates()[GLFW_KEY_O])
		acceleration = Vector3(0.0f, 4.0f * DELTA_TIME_SECONDS, 0.0f);
	else if (application.getKeyStates()[GLFW_KEY_L])
		acceleration = Vector3(0.0f, -4.0f * DELTA_TIME_SECONDS, 0.0f);
	
	/*if (application->getKeyStates()[GLFW_KEY_SPACE] && m_state != eHumanState::JUMPING)
		jump();*/

	if (!acceleration.isZero() && m_state != eHumanState::RUNNING && m_state != eHumanState::JUMPING)
		setState(eHumanState::RUNNING);
	else if (acceleration.isZero() && m_state != eHumanState::IDLE && m_state != eHumanState::JUMPING)
		setState(eHumanState::IDLE);

	setTranslation(getTranslation() + acceleration);
	setRotation(m_currentRot, Vector3(0.0f, 1.0f, 0.0f));
	application.setCameraTarget(getTranslation());
	updateAnimation();
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
	else if (m_state == eHumanState::JUMPING)
	{
		m_offsetDir = true;
		m_legs[0]->setRotation(0.0f, Vector3(1.0f, 0.0f, 0.0f));
		m_legs[1]->setRotation(0.0f, Vector3(1.0f, 0.0f, 0.0f));
		m_arms[0]->setRotation(0.0f, Vector3(1.0f, 0.0f, 0.0f));
		m_arms[1]->setRotation(0.0f, Vector3(1.0f, 0.0f, 0.0f));
	}

	m_stateLast = m_state;
	m_state = state;
}

void Human::updateAnimation()
{
	GLboolean idle = m_state == eHumanState::IDLE;
	GLboolean running = m_state == eHumanState::RUNNING;
	GLboolean jumping = m_state == eHumanState::JUMPING;

	if (idle || running)
	{
		if (m_armSwayDir)
			m_armSwayRot += ((idle * m_armSwaySpeed) + (running * m_runningSpeed)) * DELTA_TIME_SECONDS;
		else
			m_armSwayRot -= ((idle * m_armSwaySpeed) + (running * m_runningSpeed)) * DELTA_TIME_SECONDS;

		if (m_armSwayRot >= m_armSwayRotMax || m_armSwayRot <= -m_armSwayRotMax)
			m_armSwayDir = !m_armSwayDir;

		m_arms[0]->setRotation(-m_armSwayRot, Vector3(1.0f, 0.0f, 0.0f));
		m_arms[1]->setRotation( m_armSwayRot, Vector3(1.0f, 0.0f, 0.0f));
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

	if (jumping)
	{
		if (m_offsetDir)
			m_offset += Vector3(0.0f, 0.1f * DELTA_TIME_SECONDS, 0.0f);
		else
			m_offset -= Vector3(0.0f, 0.1f * DELTA_TIME_SECONDS, 0.0f);

		setTranslation(m_offsetInitial + m_offset);

		if (m_offset.getY() >= m_offsetLimit.getY() && m_offsetDir)
			m_offsetDir = false;

		if (m_offset.getY() <= 0.0f)
			setState(m_stateLast);
	}
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

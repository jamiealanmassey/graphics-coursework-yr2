#include "application.h"

Application* Application::instance;

Application::Application()
{
	m_keyStates['x'] = false;
	m_keyStates['y'] = false;
	m_keyStates['z'] = false;
	m_keyStates['w'] = false;
	m_keyStates['s'] = false;

	m_viewingX = false;
	m_viewingY = false;
	m_viewingZ = false;
	m_viewingAxis = false;
	m_viewingAxisDistance = 20.0f;
	m_viewingAxisDistanceMin = 0.1f;
	m_viewingAxisDistanceMax = 100.0f;
	m_animationScale = 1.0f;
	m_viewingMode = WINDOWED;
	m_windowTitle = "";
}

Application::~Application()
{
    // TODO
}

void Application::bind()
{
	instance = this;
	::glutIdleFunc(Application::updateCallback);
	::glutDisplayFunc(Application::renderCallback);
	::glutMouseFunc(Application::mouseCallback);
	::glutKeyboardFunc(Application::keyboardCallback);
	::glutKeyboardUpFunc(Application::keyboardUpCallback);
}

void Application::run(int viewingMode, std::string windowTitle, float animationScale)
{
    m_viewingMode = viewingMode;
    m_windowTitle = windowTitle;
    m_animationScale = animationScale;

    initialise();
	bind();
    glutMainLoop();
}

const bool Application::isViewingX() const
{
    return m_viewingX;
}

const bool Application::isViewingY() const
{
    return m_viewingY;
}

const bool Application::isViewingZ() const
{
    return m_viewingZ;
}

const bool Application::isViewingAxis() const
{
    return m_viewingAxis;
}

const float Application::getViewingAxisDistance() const
{
    return m_viewingAxisDistance;
}

const float Application::getViewingAxisDistanceMax() const
{
    return m_viewingAxisDistanceMax;
}

const float Application::getViewingAxisDistanceMin() const
{
    return m_viewingAxisDistanceMin;
}

const float Application::getAnimationScale() const
{
    return m_animationScale;
}

void Application::setViewingAxis(bool state)
{
    m_viewingAxis = state;
}

void Application::setViewingAxisDistance(float distance)
{
    m_viewingAxisDistance = distance;
}

void Application::setAnimationScale(float scale)
{
    m_animationScale = scale;
}

void Application::setSceneCamera()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, m_hwRatio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Application::drawAxisLines()
{
	Vertex origin(0.0f, 0.0f, 0.0f);
	Vertex xAxisLimit(m_viewingAxisDistance, 0.0f, 0.0f);
	Vertex yAxisLimit(0.0f, m_viewingAxisDistance, 0.0f);
	Vertex zAxisLimit(0.0f, 0.0f, m_viewingAxisDistance);

	glPushAttrib(GL_LIGHTING_BIT | GL_TEXTURE_BIT);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_LINES);
		COLOUR_RED.drawColour();
		origin.drawVertex();
		xAxisLimit.drawVertex();
		COLOUR_GREEN.drawColour();
		origin.drawVertex();
		yAxisLimit.drawVertex();
		COLOUR_BLUE.drawColour();
		origin.drawVertex();
		zAxisLimit.drawVertex();
	glEnd();
	glPopAttrib();
}

std::unique_ptr<int> Application::loadTexture(std::string path)
{
    return std::make_unique<int>(0);
}

std::unique_ptr<int> Application::loadTexture(std::string path, std::string imageType)
{
    return std::make_unique<int>(0);
}

void Application::initialise()
{
    createWindow();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

	if (funcInitScene != nullptr)
		funcInitScene(this);
}

void Application::createWindow()
{
    int argc = 1;
    char *argv[1] = {(char*)""};
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitContextVersion(1, 1);
    glutInitContextFlags(GLUT_CORE_PROFILE | GLUT_DEBUG);
    glutInitWindowSize(1200, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(m_windowTitle.c_str());
	m_hwRatio = 1200.0f / 800.0f;
	if (m_viewingMode == FULLSCREEN)
		glutFullScreen();
}

void Application::updateKeyboard(unsigned char key, int x, int y)
{
	if (key == 'x') m_keyStates['x'] = true;
	if (key == 'y') m_keyStates['y'] = true;
	if (key == 'z') m_keyStates['z'] = true;
	if (key == 'w') m_keyStates['w'] = true;
	if (key == 's') m_keyStates['s'] = true;

	if (funcUpdateSceneKeyboard != nullptr)
		funcUpdateSceneKeyboard(this, key, x, y);
}

void Application::updateKeyboardUp(unsigned char key, int x, int y)
{
	if (key == 'x') m_keyStates['x'] = false;
	if (key == 'y') m_keyStates['y'] = false;
	if (key == 'z') m_keyStates['z'] = false;
	if (key == 'w') m_keyStates['w'] = false;
	if (key == 's') m_keyStates['s'] = false;
}

void Application::updateMouse(int button, int state, int x, int y)
{
	if (funcUpdateSceneMouse != nullptr)
		funcUpdateSceneMouse(this, button, state, x, y);
}

void Application::update()
{
	m_viewingX = m_keyStates['x'];
	m_viewingY = m_keyStates['y'];
	m_viewingZ = m_keyStates['z'];
	m_viewingAxis = m_viewingX || m_viewingY || m_viewingZ;

	if (m_keyStates['w'])
		m_viewingAxisDistance += 1.0f * m_animationScale;

	if (m_keyStates['s'])
		m_viewingAxisDistance -= 1.0f * m_animationScale;

	m_viewingAxisDistance = max(m_viewingAxisDistance, m_viewingAxisDistanceMin);
	m_viewingAxisDistance = min(m_viewingAxisDistance, m_viewingAxisDistanceMax);
}

void Application::updateCamera()
{
	if (m_viewingAxis)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-m_viewingAxisDistance * m_hwRatio,
				 m_viewingAxisDistance * m_hwRatio,
				-m_viewingAxisDistance,
				 m_viewingAxisDistance,
				 0.1f,
				 100.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		if (m_viewingX)
			gluLookAt(m_viewingAxisDistance, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
		else if (m_viewingY)
			gluLookAt(0.0f, m_viewingAxisDistance, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f);
		else if (m_viewingZ)
			gluLookAt(0.0f, 0.0f, m_viewingAxisDistance, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	}
	else
		setSceneCamera();
}

void Application::renderFrame()
{
	updateCamera();
	if (funcUpdateScene != nullptr)
		funcUpdateScene(this);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (m_viewingAxis)
		drawAxisLines();

	glPushMatrix();
	if (funcRenderScene != nullptr)
		funcRenderScene(this);
		glBegin(GL_POLYGON);
			COLOUR_WHITE.drawColour();
			glVertex3f(-0.5f,   0.5f, 0.0f);
			glVertex3f( 0.5f,   0.5f, 0.0f);
			glVertex3f( 0.5f,  -0.5f, 0.0f);
			glVertex3f(-0.5f,  -0.5f, 0.0f);
		glEnd();
	glPopMatrix();
	glutSwapBuffers();

	glutPostRedisplay();
}

void Application::renderCallback()
{
	instance->renderFrame();
}

void Application::updateCallback()
{
	instance->update();
}

void Application::mouseCallback(int button, int state, int x, int y)
{
	instance->updateMouse(button, state, x, y);
}

void Application::keyboardCallback(unsigned char key, int x, int y)
{
	instance->updateKeyboard(key, x, y);
}

void Application::keyboardUpCallback(unsigned char key, int x, int y)
{
	instance->updateKeyboardUp(key, x, y);
}

#include "application.h"

Application* Application::instance;

Application::Application()
{
	m_keyStates['x'] = false;
	m_keyStates['y'] = false;
	m_keyStates['z'] = false;
	m_keyStates['w'] = false;
	m_keyStates['s'] = false;

	m_cameraLocX = 2.0f;
	m_cameraLocY = 0.0f;
	m_cameraLocZ = 0.0f;
	m_cameraTargetX = -2.0f;
	m_cameraTargetY = 0.0f;
	m_cameraTargetZ = 10.0f;

	m_viewingX = false;
	m_viewingY = false;
	m_viewingZ = false;
	m_viewingAxis = false;
	m_viewingAxisDistance = 20.0f;
	m_viewingAxisDistanceMin = 0.1f;
	m_viewingAxisDistanceMax = 100.0f;
	m_windowWidth = 800;
	m_windowWidthMin = 400;
	m_windowHeight = 600;
	m_windowHeightMin = 300;
	m_animationScale = 1.0f;
	m_viewingMode = WINDOWED;
	m_windowTitle = "";
}

Application::~Application()
{
}

void Application::bind()
{
	instance = this;
	::glutIdleFunc(Application::updateCallback);
	::glutDisplayFunc(Application::renderCallback);
	::glutReshapeFunc(Application::reshapeCallback);
	::glutMouseFunc(Application::mouseCallback);
	::glutKeyboardFunc(Application::keyboardCallback);
	::glutKeyboardUpFunc(Application::keyboardUpCallback);
}

void Application::run(GLint viewingMode, GLint width, GLint height, std::string windowTitle, GLfloat animationScale)
{
    m_viewingMode = viewingMode;
	m_windowWidth = width;
	m_windowHeight = height;
    m_windowTitle = windowTitle;
    m_animationScale = animationScale;

    initialise();
	bind();
    glutMainLoop();
}

const GLboolean Application::isViewingX() const
{
    return m_viewingX;
}

const GLboolean Application::isViewingY() const
{
    return m_viewingY;
}

const GLboolean Application::isViewingZ() const
{
    return m_viewingZ;
}

const GLboolean Application::isViewingAxis() const
{
    return m_viewingAxis;
}

const GLfloat Application::getViewingAxisDistance() const
{
    return m_viewingAxisDistance;
}

const GLfloat Application::getViewingAxisDistanceMax() const
{
    return m_viewingAxisDistanceMax;
}

const GLfloat Application::getViewingAxisDistanceMin() const
{
    return m_viewingAxisDistanceMin;
}

const GLfloat Application::getAnimationScale() const
{
    return m_animationScale;
}

void Application::setWindowMinWidth(GLint minWidth)
{
	m_windowWidthMin = minWidth;
	glutReshapeWindow(m_windowWidth, m_windowHeight);
}

void Application::setWindowMinHeight(GLint minHeight)
{
	m_windowHeightMin = minHeight;
	glutReshapeWindow(m_windowWidth, m_windowHeight);
}

void Application::setViewingAxis(GLboolean state)
{
    m_viewingAxis = state;
}

void Application::setViewingAxisDistance(GLfloat distance)
{
    m_viewingAxisDistance = distance;
}

void Application::setAnimationScale(GLfloat scale)
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
	gluLookAt(m_cameraTargetX, m_cameraTargetY, m_cameraTargetZ,
			  m_cameraLocX, m_cameraLocY, m_cameraLocZ,
			  0.0f, 1.0f, 0.0f);
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

void Application::initialise()
{
    createWindow();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	if (fp_initScene != nullptr)
		fp_initScene(this);
}

void Application::createWindow()
{
    GLint argc = 1;
    char* argv[1] = {(char*)""};
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitContextVersion(1, 1);
    glutInitContextFlags(GLUT_CORE_PROFILE | GLUT_DEBUG);
    glutInitWindowSize(m_windowWidth, m_windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(m_windowTitle.c_str());
	m_hwRatio = (GLfloat)m_windowWidth / (GLfloat)m_windowHeight;
	if (m_viewingMode == FULLSCREEN)
		glutFullScreen();
}

void Application::updateKeyboard(GLubyte key, GLint x, GLint y)
{
	if (key == 'x') m_keyStates['x'] = true;
	if (key == 'y') m_keyStates['y'] = true;
	if (key == 'z') m_keyStates['z'] = true;
	if (key == 'w') m_keyStates['w'] = true;
	if (key == 's') m_keyStates['s'] = true;

	if (fp_updateSceneKeyboard != nullptr)
		fp_updateSceneKeyboard(this, key, x, y);
}

void Application::updateKeyboardUp(GLubyte key, GLint x, GLint y)
{
	if (key == 'x') m_keyStates['x'] = false;
	if (key == 'y') m_keyStates['y'] = false;
	if (key == 'z') m_keyStates['z'] = false;
	if (key == 'w') m_keyStates['w'] = false;
	if (key == 's') m_keyStates['s'] = false;
}

void Application::updateMouse(GLint button, GLint state, GLint x, GLint y)
{
	if (fp_updateSceneMouse != nullptr)
		fp_updateSceneMouse(this, button, state, x, y);
}

void Application::update()
{
	updateCamera();
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

	if (fp_updateScene != nullptr)
		fp_updateScene(this);
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (m_viewingAxis)
		drawAxisLines();

	glPushMatrix();
	if (fp_renderScene != nullptr)
		fp_renderScene(this);

	glPopMatrix();
	glutSwapBuffers();
	glutPostRedisplay();
}

void Application::reshape(GLint width, GLint height)
{
	if (width < m_windowWidthMin)
		glutReshapeWindow(m_windowWidthMin, height);
	else if (height < m_windowHeightMin)
		glutReshapeWindow(width, m_windowHeightMin);
	else
	{
		m_windowWidth = width;
		m_windowHeight = height;
		m_hwRatio = (GLfloat)m_windowWidth / (GLfloat)m_windowHeight;
		updateCamera();
	}
}

void Application::renderCallback()
{
	instance->renderFrame();
}

void Application::reshapeCallback(GLint width, GLint height)
{
	instance->reshape(width, height);
}

void Application::updateCallback()
{
	instance->update();
}

void Application::mouseCallback(GLint button, GLint state, GLint x, GLint y)
{
	instance->updateMouse(button, state, x, y);
}

void Application::keyboardCallback(GLubyte key, GLint x, GLint y)
{
	instance->updateKeyboard(key, x, y);
}

void Application::keyboardUpCallback(GLubyte key, GLint x, GLint y)
{
	instance->updateKeyboardUp(key, x, y);
}

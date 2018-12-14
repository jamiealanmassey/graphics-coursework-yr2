#include "application.h"

Application::Application()
{
	m_keyStates['x'] = false;
	m_keyStates['y'] = false;
	m_keyStates['z'] = false;
	m_keyStates['w'] = false;
	m_keyStates['s'] = false;
	m_cameraLocX = 0.0f;
	m_cameraLocY = 0.0f;
	m_cameraLocZ = 0.0f;
	m_cameraTargetX = 0.0f;
	m_cameraTargetY = 0.0f;
	m_cameraTargetZ = 0.0f;
	m_running = true;
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
	m_viewingMode = WINDOWED;
	m_windowTitle = "";
}

Application::~Application()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Application::run(GLint viewingMode, GLint width, GLint height, std::string windowTitle)
{
	DeltaTime::instance().start();
    m_viewingMode = viewingMode;
	m_windowWidth = width;
	m_windowHeight = height;
    m_windowTitle = windowTitle;
    initialise();

	while (m_running)
	{
		DeltaTime::instance().tick();
		updateCamera();
		updateScene();
		renderFrame();
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
}

void Application::bindFuncs()
{
	glfwSetWindowCloseCallback(m_window, Application::instance().windowClose);
	glfwSetWindowSizeCallback(m_window, Application::instance().reshape);
	glfwSetKeyCallback(m_window, Application::instance().keyboard);
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

void Application::setWindowMinWidth(GLint minWidth)
{
	m_windowWidthMin = minWidth;
	glfwSetWindowSize(m_window, m_windowWidth, m_windowHeight);
}

void Application::setWindowMinHeight(GLint minHeight)
{
	m_windowHeightMin = minHeight;
	glfwSetWindowSize(m_window, m_windowWidth, m_windowHeight);
}

void Application::setViewingAxis(GLboolean state)
{
    m_viewingAxis = state;
}

void Application::setViewingAxisDistance(GLfloat distance)
{
    m_viewingAxisDistance = distance;
}

void Application::setCameraLocation(GLfloat x, GLfloat y, GLfloat z)
{
	setCameraLocation(Vector3(x, y, z));
}

void Application::setCameraLocation(Vector3 location)
{
	m_cameraLocX = location.getX();
	m_cameraLocY = location.getY();
	m_cameraLocZ = location.getZ();
}

void Application::setCameraTarget(GLfloat x, GLfloat y, GLfloat z)
{
	setCameraTarget(Vector3(x, y, z));
}

void Application::setCameraTarget(Vector3 target)
{
	m_cameraTargetX = target.getX();
	m_cameraTargetY = target.getY();
	m_cameraTargetZ = target.getZ();
}

std::map<GLubyte, GLboolean> Application::getKeyStates() const
{
	return m_keyStates;
}

Application& Application::instance()
{
	static Application instance;
	return instance;
}

void Application::setSceneCamera()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0f, m_hwRatio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(m_cameraLocX, m_cameraLocY, m_cameraLocZ,
			  m_cameraTargetX, m_cameraTargetY, m_cameraTargetZ,
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
		COLOUR_RED.assign();
		origin.assign();
		xAxisLimit.assign();
		COLOUR_GREEN.assign();
		origin.assign();
		yAxisLimit.assign();
		COLOUR_BLUE.assign();
		origin.assign();
		zAxisLimit.assign();
	glEnd();
	glPopAttrib();
}

void Application::initialise()
{
	if (!glfwInit())
		m_running = false;

    createWindow();
	bindFuncs();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	if (fp_initScene != nullptr)
		fp_initScene();
}

void Application::createWindow()
{
	GLint modesCount = 0;
	GLFWvidmode mode;
	const GLFWvidmode* modes = glfwGetVideoModes(glfwGetPrimaryMonitor(), &modesCount);

	for (int i = 0; i < modesCount; ++i)
		std::cout << "[" << std::setprecision(4) << std::fixed << glfwGetTime() << "] mode(" << i << ") - width: " << modes[i].width << ", height: " << modes[i].height << std::endl;

	for (int i = 0; i < modesCount; i++)
	{
		mode = modes[i];
		if (modes[i].width == m_windowWidth && modes[i].height == m_windowHeight)
			break;
	}

	std::cout << "[" << std::setprecision(4) << std::fixed << glfwGetTime() << "] mode - width: " << mode.width << ", height: " << mode.height << " is selected." << std::endl;
	m_windowWidth = mode.width;
	m_windowHeight = mode.height;
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	m_hwRatio = (GLfloat)m_windowWidth / (GLfloat)m_windowHeight;
	m_window =
		glfwCreateWindow(m_windowWidth,
			m_windowHeight,
			m_windowTitle.c_str(),
			m_viewingMode == FULLSCREEN ? glfwGetPrimaryMonitor() : nullptr,
			nullptr);

	if (m_window != nullptr)
	{
		glfwMakeContextCurrent(m_window);
		glfwSwapInterval(1);
	}
	else
	{
		glfwTerminate();
		m_running = false;
	}
}

void Application::updateMouse(GLint button, GLint state, GLint x, GLint y)
{
	if (fp_updateSceneMouse != nullptr)
		fp_updateSceneMouse(button, state, x, y);
}

void Application::updateScene()
{
	m_viewingX = m_keyStates[GLFW_KEY_X];
	m_viewingY = m_keyStates[GLFW_KEY_Y];
	m_viewingZ = m_keyStates[GLFW_KEY_Z];
	m_viewingAxis = m_viewingX || m_viewingY || m_viewingZ;
	if (m_keyStates[GLFW_KEY_LEFT])
		m_viewingAxisDistance += 1.0f * DELTA_TIME_SECONDS;

	if (m_keyStates[GLFW_KEY_RIGHT])
		m_viewingAxisDistance -= 1.0f * DELTA_TIME_SECONDS;

	m_viewingAxisDistance = max(m_viewingAxisDistance, m_viewingAxisDistanceMin);
	m_viewingAxisDistance = min(m_viewingAxisDistance, m_viewingAxisDistanceMax);
	if (fp_updateScene != nullptr)
		fp_updateScene();
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
	glClearColor(0.53f, 0.807f, 0.922f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (m_viewingAxis)
		drawAxisLines();

	glPushMatrix();
	if (fp_renderScene != nullptr)
		fp_renderScene();

	glPopMatrix();
}

void Application::windowClose(GLFWwindow* window)
{
	Application::instance().m_running = false;
}

void Application::keyboard(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mods)
{
	Application& application = Application::instance();
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		application.m_running = false;
	else
	{
		application.m_keyStates[key] = (action == GLFW_PRESS || action == GLFW_REPEAT);
		if (application.fp_updateSceneKeyboard != nullptr)
			application.fp_updateSceneKeyboard(key, scancode, action, mods);
	}
}

void Application::reshape(GLFWwindow* window, int width, int height)
{
	Application& application = Application::instance();
	if (width < application.m_windowWidthMin)
		glfwSetWindowSize(window, application.m_windowWidthMin, height);
	else if (height < application.m_windowHeightMin)
		glfwSetWindowSize(window, width, application.m_windowHeightMin);
	else
	{
		application.m_windowWidth = width;
		application.m_windowHeight = height;
		application.m_hwRatio = (GLfloat)application.m_windowWidth / (GLfloat)application.m_windowHeight;
		application.updateCamera();
	}
}

#include "application.h"

Application* Application::instance;

Application::Application()
{
	mViewingX = false;
	mViewingY = false;
	mViewingZ = false;
	mViewingAxis = false;
	mViewingAxisDistance = 20.0f;
	mViewingAxisDistanceMin = 0.1f;
	mViewingAxisDistanceMax = 100.0f;
	mAnimationScale = 1.0f;
	mViewingMode = WINDOWED;
	mWindowTitle = "";
}

Application::~Application()
{
    // TODO
}

void Application::bind()
{
	instance = this;
	::glutDisplayFunc(Application::renderCallback);
	::glutMouseFunc(Application::mouseCallback);
	::glutKeyboardFunc(Application::keyboardCallback);
}

void Application::run(int viewingMode, std::string windowTitle, float animationScale)
{
    mViewingMode = viewingMode;
    mWindowTitle = windowTitle;
    mAnimationScale = animationScale;

    initialise();
	bind();
    glutMainLoop();
}

const bool Application::isViewingX() const
{
    return mViewingX;
}

const bool Application::isViewingY() const
{
    return mViewingY;
}

const bool Application::isViewingZ() const
{
    return mViewingZ;
}

const bool Application::isViewingAxis() const
{
    return mViewingAxis;
}

const float Application::getViewingAxisDistance() const
{
    return mViewingAxisDistance;
}

const float Application::getViewingAxisDistanceMax() const
{
    return mViewingAxisDistanceMax;
}

const float Application::getViewingAxisDistanceMin() const
{
    return mViewingAxisDistanceMin;
}

const float Application::getAnimationScale() const
{
    return mAnimationScale;
}

void Application::setViewingAxis(bool state)
{
    mViewingAxis = state;
}

void Application::setViewingAxisDistance(float distance)
{
    mViewingAxisDistance = distance;
}

void Application::setAnimationScale(float scale)
{
    mAnimationScale = scale;
}

void Application::setSceneCamera()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, mHWRatio, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Application::drawAxisLines()
{
    // TODO
}

std::unique_ptr<Texture> Application::loadTexture(std::string path)
{
    return nullptr;
}

std::unique_ptr<Texture> Application::loadTexture(std::string path, std::string imageType)
{
    return nullptr;
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
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitContextVersion(1, 1);
    glutInitContextFlags(GLUT_CORE_PROFILE | GLUT_DEBUG);
    glutInitWindowSize(1200, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(mWindowTitle.c_str());
}

void Application::updateKeyboard(unsigned char key, int x, int y)
{
	if (funcUpdateSceneKeyboard != nullptr)
		funcUpdateSceneKeyboard(this, key, x, y);
}

void Application::updateMouse(int button, int state, int x, int y)
{
	if (funcUpdateSceneMouse != nullptr)
		funcUpdateSceneMouse(this, button, state, x, y);
}

void Application::updateCamera()
{
	if (mViewingAxis)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-mViewingAxisDistance * mHWRatio,
				 mViewingAxisDistance * mHWRatio,
				-mViewingAxisDistance,
				 mViewingAxisDistance,
				 0.1f,
				 100.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		if (mViewingX)
			gluLookAt(mViewingAxisDistance, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
		else if (mViewingY)
			gluLookAt(0.0f, mViewingAxisDistance, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f);
		else if (mViewingZ)
			gluLookAt(0.0f, 0.0f, mViewingAxisDistance, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	}
	else
		setSceneCamera();
}

void Application::renderFrame()
{
	if (funcUpdateScene != nullptr)
		funcUpdateScene(this);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (mViewingAxis)
		drawAxisLines();

	glPushMatrix();
	if (funcRenderScene != nullptr)
		funcRenderScene(this);

	glPopMatrix();
	glutSwapBuffers();

    /*glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex3f(0.25, 0.25, 0.0);
        glVertex3f(0.75, 0.25, 0.0);
        glVertex3f(0.75, 0.75, 0.0);
        glVertex3f(0.25, 0.75, 0.0);
    glEnd();
    glFlush();*/
}

void Application::renderCallback()
{
	instance->renderFrame();
}

void Application::mouseCallback(int button, int state, int x, int y)
{
	instance->updateMouse(button, state, x, y);
}

void Application::keyboardCallback(unsigned char key, int x, int y)
{
	instance->updateKeyboard(key, x, y);
}

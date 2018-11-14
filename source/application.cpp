#include "application.h"

Application::Application()
{
    // TODO
}

Application::~Application()
{
    // TODO
}

void Application::run(int viewingMode, std::string windowTitle, float animationScale)
{
    mViewingMode = viewingMode;
    mWindowTitle = windowTitle;
    mAnimationScale = animationScale;

    initialise();
    glutDisplayFunc(Application::renderFrame);
    glutMainLoop();

    /*while (mRunning)
    {
        checkInput();
        updateCamera();
        updateScene();
        renderFrame();
    }*/
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
    // TODO
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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    //glDepthFunc(GL_LEQUAL);
    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
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

void Application::checkInput()
{
    // TODO
}

void Application::updateCamera()
{
    // TODO
}

void Application::Application::renderFrame()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex3f(0.25, 0.25, 0.0);
        glVertex3f(0.75, 0.25, 0.0);
        glVertex3f(0.75, 0.75, 0.0);
        glVertex3f(0.25, 0.75, 0.0);
    glEnd();
    glFlush();
}

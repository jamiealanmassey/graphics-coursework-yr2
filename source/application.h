#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <string>
#include <memory>
#include <iostream>
#include <iomanip>
#include <functional>
#include <map>

#include "vector3.h"
#include "vertex.h"
#include "colour.h"
#include "delta_time.h"

class Application
{
public:
	static Application& instance();

public:
	Application(Application const&) = delete;
	void operator=(Application const&) = delete;

private:
    Application();
    ~Application();

public:
    void run(GLint viewingMode, GLint width, GLint height, std::string windowTitle, GLfloat animationScale);
	void bindFuncs();

    const GLboolean isViewingX() const;
    const GLboolean isViewingY() const;
    const GLboolean isViewingZ() const;
    const GLboolean isViewingAxis() const;

    const GLfloat getViewingAxisDistance() const;
    const GLfloat getViewingAxisDistanceMax() const;
    const GLfloat getViewingAxisDistanceMin() const;

	void setWindowMinWidth(GLint minWidth);
	void setWindowMinHeight(GLint minHeight);
	
    void setViewingAxis(GLboolean state);
    void setViewingAxisDistance(GLfloat distance);

	void setCameraLocation(GLfloat x, GLfloat y, GLfloat z);
	void setCameraLocation(Vector3 location);
	void setCameraTarget(GLfloat x, GLfloat y, GLfloat z);
	void setCameraTarget(Vector3 target);

protected:
    void setSceneCamera();
    void drawAxisLines();

private:
    void initialise();
    void createWindow();
	void updateMouse(GLint button, GLint state, GLint x, GLint y);
	void updateScene();
    void updateCamera();
	void renderFrame();
	
	static void windowClose(GLFWwindow* window);
	static void keyboard(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mods);
	static void reshape(GLFWwindow* window, int width, int height);

public:
    static const GLenum FULLSCREEN = 0;
    static const GLenum WINDOWED = 1;

public:
	std::function<void(Application*)>							  fp_initScene;
	std::function<void(Application*)>							  fp_updateScene;
	std::function<void(Application*)>							  fp_renderScene;
	std::function<void(Application*, GLint, GLint, GLint, GLint)> fp_updateSceneKeyboard;
	std::function<void(Application*, GLint, GLint, GLint, GLint)> fp_updateSceneMouse;

protected:
	std::map<GLubyte, GLboolean> m_keyStates;

protected:
	GLfloat m_cameraLocX;
	GLfloat m_cameraLocY;
	GLfloat m_cameraLocZ;
	GLfloat m_cameraTargetX;
	GLfloat m_cameraTargetY;
	GLfloat m_cameraTargetZ;

private:
	GLboolean   m_running;
	GLboolean   m_viewingX;
	GLboolean   m_viewingY;
	GLboolean   m_viewingZ;
	GLboolean   m_viewingAxis;
    GLfloat     m_viewingAxisDistance;
	GLfloat     m_viewingAxisDistanceMin;
	GLfloat     m_viewingAxisDistanceMax;
	GLfloat     m_hwRatio;
    GLint       m_viewingMode;
	GLint		m_windowWidth;
	GLint		m_windowWidthMin;
	GLint		m_windowHeight;
	GLint		m_windowHeightMin;
	GLFWwindow* m_window;
    std::string m_windowTitle;
};

#endif // _APPLICATION_H

#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <string>
#include <memory>
#include <iostream>
#include <functional>
#include <map>

struct IUnknown;
#include <Windows.h>
#include <GL/GL.h>
#include <GL/freeglut.h>

#include "vertex.h"
#include "colour.h"

class Application
{
private:
	static Application* instance;

public:
    Application();
    ~Application();

	void bind();
    void run(GLint viewingMode, GLint width, GLint height, std::string windowTitle, GLfloat animationScale);

    const GLboolean isViewingX() const;
    const GLboolean isViewingY() const;
    const GLboolean isViewingZ() const;
    const GLboolean isViewingAxis() const;

	//const GLboolean isKeyPressed(GLubyte key) const;

    const GLfloat getViewingAxisDistance() const;
    const GLfloat getViewingAxisDistanceMax() const;
    const GLfloat getViewingAxisDistanceMin() const;
    const GLfloat getAnimationScale() const;

    void setViewingAxis(GLboolean state);
    void setViewingAxisDistance(GLfloat distance);
    void setAnimationScale(GLfloat scale);

protected:
    void setSceneCamera();
    void drawAxisLines();

private:
    void initialise();
    void createWindow();
	void updateMouse(GLint button, GLint state, GLint x, GLint y);
	void updateKeyboardUp(GLubyte key, GLint x, GLint y);
    void updateKeyboard(GLubyte key, GLint x, GLint y);
	void update();
    void updateCamera();
	void renderFrame();
	void reshape(GLint width, GLint height);

	static void renderCallback();
	static void reshapeCallback(GLint, GLint);
	static void updateCallback();
	static void mouseCallback(GLint, GLint, GLint, GLint);
	static void keyboardCallback(GLubyte, GLint, GLint);
	static void keyboardUpCallback(GLubyte, GLint, GLint);

public:
    static const GLenum FULLSCREEN = 0;
    static const GLenum WINDOWED = 1;

public:
	std::function<void(Application*)>							  fp_initScene;
	std::function<void(Application*)>							  fp_updateScene;
	std::function<void(Application*)>							  fp_renderScene;
	std::function<void(Application*, GLubyte, GLint, GLint)>	  fp_updateSceneKeyboard;
	std::function<void(Application*, GLint, GLint, GLint, GLint)> fp_updateSceneMouse;

private:
	std::map<GLubyte, GLboolean> m_keyStates;

protected:
	GLfloat m_cameraLocX;
	GLfloat m_cameraLocY;
	GLfloat m_cameraLocZ;
	GLfloat m_cameraTargetX;
	GLfloat m_cameraTargetY;
	GLfloat m_cameraTargetZ;

private:
	GLboolean   m_viewingX;
	GLboolean   m_viewingY;
	GLboolean   m_viewingZ;
	GLboolean   m_viewingAxis;
    GLfloat     m_viewingAxisDistance;
	GLfloat     m_viewingAxisDistanceMin;
	GLfloat     m_viewingAxisDistanceMax;
	GLfloat     m_animationScale;
	GLfloat     m_hwRatio;
    GLint       m_viewingMode;
	GLint		m_windowWidth;
	GLint		m_windowHeight;
    std::string m_windowTitle;
};

#endif // _APPLICATION_H

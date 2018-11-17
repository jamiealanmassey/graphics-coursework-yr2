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

    const GLfloat getViewingAxisDistance() const;
    const GLfloat getViewingAxisDistanceMax() const;
    const GLfloat getViewingAxisDistanceMin() const;
    const GLfloat getAnimationScale() const;

    void setViewingAxis(GLboolean state);
    void setViewingAxisDistance(GLfloat distance);
    void setAnimationScale(GLfloat scale);

public:
	std::function<void(Application*)> funcInitScene;
	std::function<void(Application*, unsigned char, GLint, GLint)> funcUpdateSceneKeyboard;
	std::function<void(Application*, GLint, GLint, GLint, GLint)> funcUpdateSceneMouse;
	std::function<void(Application*)> funcUpdateScene;
	std::function<void(Application*)> funcRenderScene;

protected:
    void setSceneCamera();
    void drawAxisLines();

    std::unique_ptr<GLint> loadTexture(std::string path);
    std::unique_ptr<GLint> loadTexture(std::string path, std::string imageType);

private:
    void initialise();
    void createWindow();
	void updateMouse(GLint button, GLint state, GLint x, GLint y);
	void updateKeyboardUp(unsigned char key, GLint x, GLint y);
    void updateKeyboard(unsigned char key, GLint x, GLint y);
	void update();
    void updateCamera();
	void renderFrame();
	void reshape(GLint width, GLint height);

	static void renderCallback();
	static void reshapeCallback(GLint, GLint);
	static void updateCallback();
	static void mouseCallback(GLint, GLint, GLint, GLint);
	static void keyboardCallback(unsigned char, GLint, GLint);
	static void keyboardUpCallback(unsigned char, GLint, GLint);

public:
    static const GLenum FULLSCREEN = 0;
    static const GLenum WINDOWED = 1;

private:
	std::map<unsigned char, GLboolean> m_keyStates;

protected:

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

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
    void run(int viewingMode, std::string windowTitle, float animationScale);

    const bool isViewingX() const;
    const bool isViewingY() const;
    const bool isViewingZ() const;
    const bool isViewingAxis() const;

    const float getViewingAxisDistance() const;
    const float getViewingAxisDistanceMax() const;
    const float getViewingAxisDistanceMin() const;
    const float getAnimationScale() const;

    void setViewingAxis(bool state);
    void setViewingAxisDistance(float distance);
    void setAnimationScale(float scale);

public:
	std::function<void(Application*)> funcInitScene;
	std::function<void(Application*, unsigned char, int, int)> funcUpdateSceneKeyboard;
	std::function<void(Application*, int, int, int, int)> funcUpdateSceneMouse;
	std::function<void(Application*)> funcUpdateScene;
	std::function<void(Application*)> funcRenderScene;

protected:
    void setSceneCamera();
    void drawAxisLines();

    std::unique_ptr<int> loadTexture(std::string path);
    std::unique_ptr<int> loadTexture(std::string path, std::string imageType);

private:
    void initialise();
    void createWindow();
	void updateMouse(int button, int state, int x, int y);
	void updateKeyboardUp(unsigned char key, int x, int y);
    void updateKeyboard(unsigned char key, int x, int y);
	void update();
    void updateCamera();
	void renderFrame();

	static void renderCallback();
	static void updateCallback();
	static void mouseCallback(int, int, int, int);
	static void keyboardCallback(unsigned char, int, int);
	static void keyboardUpCallback(unsigned char, int, int);

public:
    static const int FULLSCREEN = 0;
    static const int WINDOWED = 1;

private:
	std::map<unsigned char, bool> m_keyStates;

private:
    bool        m_viewingX;
    bool        m_viewingY;
    bool        m_viewingZ;
    bool        m_viewingAxis;
    float       m_viewingAxisDistance;
    float       m_viewingAxisDistanceMin;
    float       m_viewingAxisDistanceMax;
    float       m_animationScale;
    float       m_hwRatio;
    int         m_viewingMode;
    std::string m_windowTitle;
};

#endif // _APPLICATION_H

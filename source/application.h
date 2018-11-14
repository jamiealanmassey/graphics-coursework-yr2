#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <string>
#include <memory>
#include <iostream>

#include <GL/gl.h>
#include <GL/freeglut.h>

class Texture
{
public:
    Texture();
    ~Texture();
};

class Application
{
public:
    Application();
    ~Application();

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

protected:
    virtual void initScene() {};
    virtual void checkSceneInput() {};
    virtual void updateScene() {};
    virtual void renderScene() {};

protected:
    void setSceneCamera();
    void drawAxisLines();

    std::unique_ptr<Texture> loadTexture(std::string path);
    std::unique_ptr<Texture> loadTexture(std::string path, std::string imageType);

private:
    void initialise();
    void createWindow();
    void checkInput();
    void updateCamera();
    
    static void renderFrame();

public:
    static const int FULLSCREEN = 0;
    static const int WINDOWED = 1;

private:
    bool        mRunning;
    bool        mViewingX;
    bool        mViewingY;
    bool        mViewingZ;
    bool        mViewingAxis;
    float       mViewingAxisDistance;
    float       mViewingAxisDistanceMin;
    float       mViewingAxisDistanceMax;
    float       mAnimationScale;
    float       mHWRatio;
    int         mViewingMode;
    std::string mWindowTitle;
};

#endif // _APPLICATION_H

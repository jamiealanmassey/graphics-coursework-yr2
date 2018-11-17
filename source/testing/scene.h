#ifndef _SCENE_H
#define _SCENE_H

#include <GL/freeglut.h>
#include <GL/GL.h>

#include "../application.h"

class Scene
{
public:
	static void renderScene(Application* application);

private:
	Scene() { }
};

#endif // _SCENE_H

#ifndef _SCENE_H
#define _SCENE_H

#include <GL/freeglut.h>
#include <GL/GL.h>

#include "../application.h"
#include "../texture.h"

class Scene
{
public:
	Scene();
	~Scene();

public:
	static void renderScene(Application* application);

private:
	std::unique_ptr<Texture> m_texture0;
};

#endif // _SCENE_H

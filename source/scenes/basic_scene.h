#ifndef _BASIC_SCENE_H
#define _BASIC_SCENE_H

#include <GL/freeglut.h>
#include <GL/GL.h>

#include "../application.h"
#include "../texture.h"

class BasicScene
{
public:
	BasicScene();
	~BasicScene();

public:
	void initScene(Application* application);
	void renderScene(Application* application);

private:
	std::unique_ptr<Texture> m_texture0;
};

#endif // _BASIC_SCENE_H

#ifndef _BASIC_SCENE_H
#define _BASIC_SCENE_H

#include "../application.h"
#include "../drawables/grass_block.h"
#include "scene_parser.h"

class BasicScene
{
public:
	BasicScene();
	~BasicScene();

public:
	void initScene(Application* application);
	void renderScene(Application* application);
	void updateScene(Application* application);

private:
	std::unique_ptr<SceneParser> m_sceneParser;
};

#endif // _BASIC_SCENE_H

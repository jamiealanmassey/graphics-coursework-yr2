#ifndef _BASIC_SCENE_H
#define _BASIC_SCENE_H

#include "../application.h"
#include "../drawables/grass_block.h"
#include "../drawables/human/human.h"
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
	std::unique_ptr<Human> m_human;
};

#endif // _BASIC_SCENE_H

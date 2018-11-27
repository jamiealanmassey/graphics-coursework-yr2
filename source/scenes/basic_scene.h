#ifndef _BASIC_SCENE_H
#define _BASIC_SCENE_H

#include "../application.h"
#include "../drawables/grass_block.h"
#include "../processing/world_parser.h"

#define BLOCK_EMPTY 0
#define BLOCK_GRASS 1

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
	std::unique_ptr<GrassBlock>  m_grassBlock;
	std::unique_ptr<WorldParser> m_worldParser;
};

#endif // _BASIC_SCENE_H

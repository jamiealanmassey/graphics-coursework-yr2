#ifndef _BASIC_SCENE_H
#define _BASIC_SCENE_H

#include "../application.h"
#include "../drawables/grass_block.h"

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
	std::unique_ptr<GrassBlock> m_grassBlock;
	std::unique_ptr<Texture> m_texture0;
};

#endif // _BASIC_SCENE_H

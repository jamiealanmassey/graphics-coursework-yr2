#include "basic_scene.h"

BasicScene::BasicScene()
{
}

BasicScene::~BasicScene()
{
}

void BasicScene::initScene(Application* application)
{
	application->setCameraLocation(-5.0f, 8.0f, -10.0f);
	application->setCameraTarget(8.0f, 0.0f, 8.0f);

	m_grassBlock = std::make_unique<GrassBlock>();
	m_grassBlock->initialise(application);

	m_worldParser = std::make_unique<WorldParser>("../data/", "world.chunk.dat");
	m_worldParser.get()->parse();
}

void BasicScene::renderScene(Application* application) 
{
	auto chunk = m_worldParser.get()->getWorldChunk();
	for (auto y = 0; y < chunk.size(); y++) 
	{
		for (auto x = 0; x < chunk[y].size(); x++) 
		{
			for (auto z = 0; z < chunk[y][x].size(); z++) 
			{
				if (chunk[y][x][z] == BLOCK_GRASS)
				{
					m_grassBlock.get()->setTranslation(Vector3(x, y, z));
					m_grassBlock.get()->draw(application);
				}
			}
		}
	}
}

void BasicScene::updateScene(Application * application)
{
}

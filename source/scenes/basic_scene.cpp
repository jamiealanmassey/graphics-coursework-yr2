#include "basic_scene.h"

BasicScene::BasicScene()
{
}

BasicScene::~BasicScene()
{
}

void BasicScene::initScene(Application* application)
{
	application->setCameraLocation(12.0f, 10.0f, 18.0f);
	application->setCameraTarget(0.0f, 0.0f, 0.0f);

	m_human = std::make_unique<Human>();
	m_human.get()->initialise(application);
	m_human.get()->setTranslation(Vector3(6.0f, 3.0f, 6.0f));
	m_human.get()->setScale(Vector3(0.5f, 0.5f, 0.5f));

	m_sceneParser = std::make_unique<SceneParser>("../data/", "world.chunk.dat");
	m_sceneParser.get()->parse();

	for (const auto& drawable : m_sceneParser.get()->getDrawables())
		drawable->initialise(application);
}

void BasicScene::renderScene(Application* application) 
{
	m_human.get()->draw(application);
	for (auto drawable : m_sceneParser.get()->getDrawables())
		drawable->draw(application);
}

void BasicScene::updateScene(Application* application)
{
	m_human.get()->update(application);
	for (auto drawable : m_sceneParser.get()->getDrawables())
		drawable->update(application);
}

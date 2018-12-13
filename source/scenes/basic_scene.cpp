#include "basic_scene.h"

BasicScene::BasicScene()
{
}

BasicScene::~BasicScene()
{
}

void BasicScene::initScene()
{
	Application& application = Application::instance();
	application.setCameraLocation(12.0f, 10.0f, 18.0f);
	application.setCameraTarget(0.0f, 0.0f, 0.0f);

	m_human = std::make_unique<Human>();
	m_human->initialise();
	m_human->setTranslation(Vector3(6.0f, 4.0f, 6.0f));
	m_human->setScale(Vector3(0.5f, 0.5f, 0.5f));

	/*m_sceneParser = std::make_unique<SceneParser>("../data/", "world.chunk.dat");
	m_sceneParser.get()->parse();

	for (const auto& drawable : m_sceneParser.get()->getDrawables())
		drawable->initialise(application);*/
}

void BasicScene::renderScene() 
{
	m_human.get()->draw();
	/*for (auto drawable : m_sceneParser.get()->getDrawables())
		drawable->draw(application);*/
}

void BasicScene::updateScene()
{
	m_human.get()->update();
	/*for (auto drawable : m_sceneParser.get()->getDrawables())
		drawable->update(application);*/
}

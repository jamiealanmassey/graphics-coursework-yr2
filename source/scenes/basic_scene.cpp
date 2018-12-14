#include "basic_scene.h"

BasicScene::BasicScene()
{
}

BasicScene::~BasicScene()
{
}

void BasicScene::initScene()
{
	// Setup application camera for the scene
	Application& application = Application::instance();
	application.setCameraLocation(12.0f, 10.0f, 18.0f);
	application.setCameraTarget(0.0f, 0.0f, 0.0f);

	// Setup scene lighting
	const GLfloat globalAmbient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	const GLfloat diffuse0[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	const GLfloat ambient0[] = { 0.7f, 0.7f, 0.6f, 1.0f };
	const GLfloat position0[] = { 10.0f, 20.0f, 10.0f, 1.0f };

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, diffuse0);
	glLightfv(GL_LIGHT0, GL_POSITION, position0);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#ifdef _WINDOWS_
	PlaySound("..\\data\\calm.wav", 0, SND_ASYNC | SND_FILENAME | SND_LOOP);
#endif

	// Create Human custom object
	m_human = std::make_unique<Human>();
	m_human->initialise();
	m_human->setTranslation(Vector3(5.0f, 3.5f, 5.0f));
	m_human->setScale(Vector3(0.5f, 0.5f, 0.5f));

	m_sceneParser = std::make_unique<SceneParser>("../data/", "world.chunk.dat");
	m_sceneParser.get()->parse();

	for (const auto& drawable : m_sceneParser.get()->getDrawables())
		drawable->initialise();
}

void BasicScene::renderScene() 
{
	m_human.get()->draw();
	for (auto drawable : m_sceneParser.get()->getDrawables())
		drawable->draw();
}

void BasicScene::updateScene()
{
	m_human.get()->update();
	for (auto drawable : m_sceneParser.get()->getDrawables())
		drawable->update();
}

#include "application.h"
#include "scenes/basic_scene.h"

GLint main(GLint argc, char** argv)
{
	std::unique_ptr<BasicScene> scene = std::make_unique<BasicScene>();
	Application::instance().fp_initScene = std::bind(&BasicScene::initScene, scene.get());
	Application::instance().fp_renderScene = std::bind(&BasicScene::renderScene, scene.get());
	Application::instance().fp_updateScene = std::bind(&BasicScene::updateScene, scene.get());
	Application::instance().run(Application::instance().WINDOWED, 1280, 720, "CS2150 Graphics Coursework");
    return 0;
}

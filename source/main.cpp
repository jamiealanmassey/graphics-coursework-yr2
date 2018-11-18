#include "application.h"
#include "scenes/basic_scene.h"

GLint main(GLint argc, char** argv)
{
	std::unique_ptr<BasicScene> scene = std::make_unique<BasicScene>();
	Application::instance().fp_initScene = std::bind(&BasicScene::initScene, scene.get(), std::placeholders::_1);
	Application::instance().fp_renderScene = std::bind(&BasicScene::renderScene, scene.get(), std::placeholders::_1);
	Application::instance().run(Application::instance().WINDOWED, 1280, 720, "CS2150 Graphics Coursework", 1.0f);
    return 0;
}

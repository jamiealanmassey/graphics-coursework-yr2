#include "application.h"
#include "scenes/basic_scene.h"

GLint main(GLint argc, char** argv)
{
	std::unique_ptr<BasicScene> scene = std::make_unique<BasicScene>();
	Application application;
	application.fp_initScene = std::bind(&BasicScene::initScene, scene.get(), std::placeholders::_1);
	application.fp_renderScene = std::bind(&BasicScene::renderScene, scene.get(), std::placeholders::_1);
    application.run(application.WINDOWED, 800, 600, "CS2150 Graphics Coursework", 1.0f);
    return 0;
}

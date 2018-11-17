#include "application.h"
#include "testing/scene.h"

GLint main(GLint argc, char** argv)
{
	Application application;
	application.fp_renderScene = std::bind(&Scene::renderScene, std::placeholders::_1);
    application.run(application.WINDOWED, 800, 600, "Hello World", 1.0f);
    return 0;
}

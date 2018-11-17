#include "application.h"

GLint main(GLint argc, char** argv)
{
    std::unique_ptr<Application> application = std::make_unique<Application>();
    application.get()->run(application.get()->WINDOWED, 800, 600, "Hello World", 1.0f);
    return 0;
}

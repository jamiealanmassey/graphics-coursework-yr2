#include "application.h"

int main(int argc, char** argv)
{
    std::unique_ptr<Application> application = std::make_unique<Application>();
    application.get()->run(application.get()->WINDOWED, "Hello World", 1.0f);
    return 0;
}

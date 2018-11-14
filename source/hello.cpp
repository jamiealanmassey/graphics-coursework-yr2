#include "application.h"

int main(int argc, char** argv)
{
    std::unique_ptr<Application> application = std::make_unique<Application>();
    application.get()->run(0, "Hello World", 1.0f);
    return 0;
}

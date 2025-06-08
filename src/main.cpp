#include "application.hpp"

int main(int argc, char* argv[])
{
    ps::Application app;
    if (!app.init())
        return SDL_APP_FAILURE;
    app.setupScene();
    app.run();
    return 0;
}
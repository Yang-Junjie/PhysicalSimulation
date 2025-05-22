#include "render.hpp"
#include "ps.hpp"
#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <chrono>
#include <SDL3/SDL.h>
#include "scenes/scenes.hpp"
#include "scenes/heap.hpp"
#include "scenes/sleep.hpp"
#include "camera.hpp"
using namespace ps;
static SDL_Window *window = nullptr;
static SDL_Renderer *renderer = nullptr;

Scene *scene = nullptr;
SceneHeap heap;
SceneSleep sleep;


int main(int argc, char *argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("PhysicalSimulation", 1080, 680, 0, &window, &renderer))
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    //scene = &heap;
    scene = &sleep;
    scene->setBody();
    //scene->getCamera().setWorld(&heap.getSystem().world());
    scene->getCamera().setWorld(&sleep.getSystem().world());

    SDL_Event event;
    bool keep_going = true;
    while (keep_going)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                keep_going = false;
        }
        const real dt = 1.0f / 60.0f;
        scene->getSystem().step(dt);
        scene->getCamera().render(window, renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(0.5f);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
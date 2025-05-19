#include "render.hpp"
#include "ps.hpp"
#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <chrono>
#include <SDL3/SDL.h>
#include "camera.hpp"
using namespace ps;
static SDL_Window *window = nullptr;
static SDL_Renderer *renderer = nullptr;
// TODO : Add preformance test
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
    PhysicsSystem m_system;
    

    Edge edge;
    Circle circle;
    edge.set(Vector2{10.0f, 580.0f}, Vector2{1070.0f, 580.0f});
    circle.setRadius(10.0f);
    uint32_t mask = 0x01;
    real max = 2.0f;
    mask = 0x01;
    Vector2 pos[3];
    pos[0].set({30.0f, 100.0f});
    for (real i = 0; i < 1; i += 1.0f)
    {
        Body *body = m_system.world().createBody();
        body->setShape(&circle);
        body->position().set(pos[int(i)]);
        body->setFriction(1.0f);
        body->setBitmask(mask);
        body->setRestitution(0);
        body->setMass(1.0f);
        body->setType(Body::BodyType::Dynamic);
        // mask = mask << 1;
        m_system.tree().insert(body);
    }
    for (real i = 0; i < 1.0f; i += 1.0f)
    {
        Body *ground = m_system.world().createBody();
        ground->setShape(&edge);
        ground->position().set({0, -circle.radius()});
        ground->setFriction(1.0f);
        ground->setBitmask(mask);
        ground->setRestitution(0);
        ground->setMass(Constant::Max);
        ground->setType(Body::BodyType::Static);
        mask = mask << 1;
        m_system.tree().insert(ground);
    }
    m_system.world().setGravity(Vector2(0.0f, 9.8f));
    
    Camera m_camera;
    m_camera.setWorld(&m_system.world());

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
        m_system.step(dt);
        m_camera.render(window, renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
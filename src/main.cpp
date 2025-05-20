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

    m_system.world().setEnableGravity(true);
    m_system.world().setGravity({0.0f, 10.0f});
    m_system.world().setLinearVelocityDamping(0.0f);
    m_system.world().setAirFrictionCoefficient(0.0f);
    m_system.world().setAngularVelocityDamping(0.0f);
    m_system.world().setEnableDamping(true);
    m_system.positionIteration() = 4;
    m_system.velocityIteration() = 6;
    Edge edge;
    Circle circle;
    Polygon polygon;
    polygon.append({{0, 0}, {50, 0}, {50, 50}, {0, 50}});
    edge.set(Vector2{10.0f, 580.0f}, Vector2{1070.0f, 580.0f});
    circle.setRadius(10.0f);
    uint32_t mask = 0x01;
    real max = 2.0f;
    mask = 0x01;
    Vector2 pos[10];
    pos[0].set({300.0f, 100.0f});
    pos[1].set({350.0f, 100.0f});
    pos[2].set({400.0f, 100.0f});
    pos[3].set({450.0f, 100.0f});
    pos[4].set({500.0f, 100.0f});
    pos[5].set({550.0f, 100.0f});
    pos[6].set({600.0f, 100.0f});
    pos[7].set({650.0f, 100.0f});
    pos[8].set({700.0f, 100.0f});
    pos[9].set({750.0f, 100.0f});
    for (real j = 0; j < 10; j += 1.0f)
    {
        for (real i = 0; i < 10; i += 1.0f)
        {

            Body *polygonBody = m_system.world().createBody();
            polygonBody->setShape(&polygon);
            polygonBody->setFriction(1.0f);
            polygonBody->position().set(pos[int(i)] + Vector2(0, j * 50));
            polygonBody->setBitmask(mask);
            polygonBody->setRestitution(0);
            polygonBody->setMass(1);
            polygonBody->setType(Body::BodyType::Dynamic);
            m_system.tree().insert(polygonBody);
        }
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
        SDL_Delay(0.5f);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}